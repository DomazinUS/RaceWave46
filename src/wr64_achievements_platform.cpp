#include "wr64_achievements_platform.hpp"
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <string_view>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <wincrypt.h>
#include <winhttp.h>
#elif defined(__linux__)
#include <cctype>
#include <memory>
#include <mutex>
#include <curl/curl.h>
#include <libsecret/secret.h>
#endif

namespace wr64::achievements::platform {
void erase_secret(std::string& value) {
#ifdef _WIN32
    if (!value.empty()) SecureZeroMemory(value.data(), value.size());
#else
    volatile char* data = value.data();
    for (std::size_t i = 0; i < value.size(); ++i) data[i] = 0;
#endif
    value.clear();
}

namespace {
constexpr std::size_t response_limit = 8 * 1024 * 1024;
constexpr std::size_t credential_limit = 65536;
constexpr const char* credential_filename = "retroachievements.credentials";
constexpr std::string_view credential_magic = "WR64RA1";
bool plain_field(std::string_view value, std::size_t limit, bool empty = false) {
    return (empty || !value.empty()) && value.size() <= limit &&
        std::none_of(value.begin(), value.end(), [](unsigned char c) { return c < 32 || c == 127; });
}
struct SensitiveString {
    std::string value;
    ~SensitiveString() { erase_secret(value); }
};
#ifdef _WIN32
std::wstring wide(const std::string& value) {
    if (value.empty()) return {};
    const int length = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, value.data(), int(value.size()), nullptr, 0);
    if (!length) return {};
    std::wstring result(length, L'\0');
    if (!MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, value.data(), int(value.size()), result.data(), length)) return {};
    return result;
}
struct InternetHandle {
    HINTERNET value = nullptr;
    explicit InternetHandle(HINTERNET handle) : value(handle) {}
    ~InternetHandle() { if (value) WinHttpCloseHandle(value); }
    InternetHandle(const InternetHandle&) = delete;
    operator HINTERNET() const { return value; }
};
struct ProtectedBlob {
    DATA_BLOB data{};
    ~ProtectedBlob() {
        if (data.pbData) { SecureZeroMemory(data.pbData, data.cbData); LocalFree(data.pbData); }
    }
};
void append_size(std::string& output, std::size_t value) {
    for (unsigned i = 0; i < 4; ++i) output.push_back(char((value >> (8 * i)) & 255));
}
std::uint32_t read_size(const unsigned char* bytes) {
    return std::uint32_t(bytes[0]) | (std::uint32_t(bytes[1]) << 8) |
        (std::uint32_t(bytes[2]) << 16) | (std::uint32_t(bytes[3]) << 24);
}
#elif defined(__linux__)
struct CurlDeleter { void operator()(CURL* handle) const { curl_easy_cleanup(handle); } };
struct CurlUrlDeleter { void operator()(CURLU* handle) const { curl_url_cleanup(handle); } };
struct CurlListDeleter { void operator()(curl_slist* list) const { curl_slist_free_all(list); } };
struct CurlString {
    char* value = nullptr;
    ~CurlString() { curl_free(value); }
};
void initialize_curl() {
    static std::once_flag once;
    std::call_once(once, [] { curl_global_init(CURL_GLOBAL_DEFAULT); });
}
std::size_t receive_body(char* data, std::size_t size, std::size_t count, void* user) {
    auto& body = *static_cast<std::string*>(user);
    const std::size_t bytes = size * count;
    if (bytes > response_limit - body.size()) return 0;
    body.append(data, bytes);
    return bytes;
}
// WinHTTP rejects these through its UTF-16 conversion; curl would send the
// bytes unchanged, so reject malformed UTF-8 explicitly.
bool valid_utf8(std::string_view value) {
    for (std::size_t i = 0; i < value.size();) {
        const auto lead = static_cast<unsigned char>(value[i]);
        const std::size_t length = lead < 0x80 ? 1 : (lead >> 5) == 6 ? 2 : (lead >> 4) == 14 ? 3 : (lead >> 3) == 30 ? 4 : 0;
        if (length == 0 || length > value.size() - i) return false;
        std::uint32_t code = length == 1 ? lead : lead & (0x7F >> length);
        for (std::size_t j = 1; j < length; ++j) {
            const auto next = static_cast<unsigned char>(value[i + j]);
            if ((next & 0xC0) != 0x80) return false;
            code = (code << 6) | (next & 0x3F);
        }
        constexpr std::uint32_t minimum[] = {0, 0, 0x80, 0x800, 0x10000};
        if (code < minimum[length] || code > 0x10FFFF || (code >= 0xD800 && code <= 0xDFFF)) return false;
        i += length;
    }
    return true;
}
bool equal_ignoring_case(std::string_view left, std::string_view right) {
    return left.size() == right.size() && std::equal(left.begin(), left.end(), right.begin(),
        [](unsigned char a, unsigned char b) { return std::tolower(a) == std::tolower(b); });
}
// The login is kept in the desktop keyring (the Secret portal inside Flatpak),
// keyed by the profile directory so separate --runtime-dir profiles stay apart.
const SecretSchema* credential_schema() {
    static const SecretSchema schema = {
        "RaceWave46.RetroAchievements", SECRET_SCHEMA_NONE,
        {{"profile", SECRET_SCHEMA_ATTRIBUTE_STRING}, {nullptr, SECRET_SCHEMA_ATTRIBUTE_STRING}},
    };
    return &schema;
}
std::string profile_key(const std::filesystem::path& directory) {
    std::error_code error;
    const auto absolute = std::filesystem::weakly_canonical(directory, error);
    return (error ? directory : absolute).string();
}
#endif
}

HttpResponse http_request(const std::string& url, const std::string& post,
    const std::string& content_type, const std::string& user_agent) {
#ifdef _WIN32
    // Never let a request containing a login/session token move to another
    // origin, a plaintext endpoint, URL credentials, or an automatic redirect.
    if (!plain_field(url, 8192) || url.find('#') != std::string::npos ||
        !plain_field(user_agent, 512) || !plain_field(content_type, 128, true) || post.size() > 1024 * 1024)
        return {-1, "Invalid achievement service request."};
    const auto request_url = wide(url), agent = wide(user_agent), type = wide(content_type);
    if (request_url.empty() || agent.empty() || (!content_type.empty() && type.empty()))
        return {-1, "Invalid achievement service URL or header."};
    URL_COMPONENTS parts{}; parts.dwStructSize = sizeof(parts);
    parts.dwHostNameLength = parts.dwUserNameLength = parts.dwPasswordLength =
        parts.dwUrlPathLength = parts.dwExtraInfoLength = DWORD(-1);
    if (!WinHttpCrackUrl(request_url.c_str(), DWORD(request_url.size()), 0, &parts) ||
        parts.nScheme != INTERNET_SCHEME_HTTPS || parts.nPort != INTERNET_DEFAULT_HTTPS_PORT ||
        parts.dwUserNameLength || parts.dwPasswordLength || parts.dwHostNameLength != 21 ||
        _wcsnicmp(parts.lpszHostName, L"retroachievements.org", parts.dwHostNameLength) != 0)
        return {-1, "Only the official HTTPS achievement service is supported."};
    const std::wstring host(parts.lpszHostName, parts.dwHostNameLength);
    std::wstring resource;
    if (parts.dwUrlPathLength) resource.assign(parts.lpszUrlPath, parts.dwUrlPathLength);
    if (resource.empty()) resource = L"/";
    if (parts.dwExtraInfoLength) resource.append(parts.lpszExtraInfo, parts.dwExtraInfoLength);
    InternetHandle session(WinHttpOpen(agent.c_str(), WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
        WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0));
    if (!session || !WinHttpSetTimeouts(session, 10000, 10000, 15000, 20000))
        return {-2, "Unable to initialize the achievement connection."};
    DWORD retries = 1;
    if (!WinHttpSetOption(session, WINHTTP_OPTION_CONNECT_RETRIES, &retries, sizeof(retries)))
        return {-2, "Unable to configure the achievement connection."};
    InternetHandle connection(WinHttpConnect(session, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0));
    if (!connection) return {-2, "Unable to connect to the achievement service."};
    InternetHandle request(WinHttpOpenRequest(connection, post.empty() ? L"GET" : L"POST", resource.c_str(),
        nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE));
    if (!request) return {-2, "Unable to create the achievement request."};
    DWORD disabled = WINHTTP_DISABLE_REDIRECTS | WINHTTP_DISABLE_COOKIES | WINHTTP_DISABLE_AUTHENTICATION;
    if (!WinHttpSetOption(request, WINHTTP_OPTION_DISABLE_FEATURE, &disabled, sizeof(disabled)))
        return {-1, "Unable to enforce achievement connection policy."};
    std::wstring headers;
    if (!post.empty()) headers = L"Content-Type: " + (type.empty() ? std::wstring(L"application/x-www-form-urlencoded") : type) + L"\r\n";
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(45);
    if (!WinHttpSendRequest(request, headers.empty() ? WINHTTP_NO_ADDITIONAL_HEADERS : headers.c_str(),
        DWORD(headers.size()), post.empty() ? WINHTTP_NO_REQUEST_DATA : const_cast<char*>(post.data()),
        DWORD(post.size()), DWORD(post.size()), 0) || !WinHttpReceiveResponse(request, nullptr))
        return {-2, "The achievement service connection failed or timed out."};
    DWORD status = 0, size = sizeof(status);
    if (!WinHttpQueryHeaders(request, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
        WINHTTP_HEADER_NAME_BY_INDEX, &status, &size, WINHTTP_NO_HEADER_INDEX))
        return {-2, "The achievement service returned an invalid response."};
    HttpResponse response{int(status), {}};
    std::array<char, 16384> buffer{};
    for (;;) {
        const auto remaining = std::chrono::duration_cast<std::chrono::milliseconds>(deadline - std::chrono::steady_clock::now()).count();
        if (remaining <= 0) return {-2, "The achievement response timed out."};
        DWORD timeout = DWORD(std::min<std::int64_t>(remaining, 15000));
        if (!WinHttpSetOption(request, WINHTTP_OPTION_RECEIVE_TIMEOUT, &timeout, sizeof(timeout)))
            return {-2, "Unable to configure the achievement response timeout."};
        DWORD received = 0;
        if (!WinHttpReadData(request, buffer.data(), DWORD(buffer.size()), &received))
            return {-2, "The achievement response could not be read."};
        if (!received) return response;
        if (received > response_limit - response.body.size())
            return {-1, "The achievement service response exceeds its size limit."};
        response.body.append(buffer.data(), received);
    }
#elif defined(__linux__)
    // Same policy as the WinHTTP path: official HTTPS origin only, no URL
    // credentials, cookies, authentication or redirects.
    if (!plain_field(url, 8192) || url.find('#') != std::string::npos ||
        !plain_field(user_agent, 512) || !plain_field(content_type, 128, true) || post.size() > 1024 * 1024 ||
        !valid_utf8(url) || !valid_utf8(user_agent) || !valid_utf8(content_type))
        return {-1, "Invalid achievement service request."};
    initialize_curl();
    std::unique_ptr<CURLU, CurlUrlDeleter> parsed(curl_url());
    if (!parsed || curl_url_set(parsed.get(), CURLUPART_URL, url.c_str(), 0) != CURLUE_OK)
        return {-1, "Invalid achievement service URL or header."};
    CurlString scheme, host, port, user, password;
    curl_url_get(parsed.get(), CURLUPART_SCHEME, &scheme.value, 0);
    curl_url_get(parsed.get(), CURLUPART_HOST, &host.value, 0);
    curl_url_get(parsed.get(), CURLUPART_PORT, &port.value, 0);
    curl_url_get(parsed.get(), CURLUPART_USER, &user.value, 0);
    curl_url_get(parsed.get(), CURLUPART_PASSWORD, &password.value, 0);
    if (!scheme.value || std::string_view(scheme.value) != "https" || !host.value ||
        !equal_ignoring_case(host.value, "retroachievements.org") ||
        (port.value && std::string_view(port.value) != "443") || user.value || password.value)
        return {-1, "Only the official HTTPS achievement service is supported."};
    std::unique_ptr<CURL, CurlDeleter> request(curl_easy_init());
    if (!request) return {-2, "Unable to initialize the achievement connection."};
    CURL* handle = request.get();
    std::unique_ptr<curl_slist, CurlListDeleter> headers;
    if (!post.empty()) {
        const std::string header = "Content-Type: " +
            (content_type.empty() ? std::string("application/x-www-form-urlencoded") : content_type);
        headers.reset(curl_slist_append(nullptr, header.c_str()));
        if (!headers) return {-2, "Unable to create the achievement request."};
    }
    HttpResponse response{0, {}};
    const bool configured =
        curl_easy_setopt(handle, CURLOPT_CURLU, parsed.get()) == CURLE_OK &&
        curl_easy_setopt(handle, CURLOPT_PROTOCOLS_STR, "https") == CURLE_OK &&
        curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 0L) == CURLE_OK &&
        curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1L) == CURLE_OK &&
        curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT_MS, 10000L) == CURLE_OK &&
        curl_easy_setopt(handle, CURLOPT_TIMEOUT_MS, 45000L) == CURLE_OK &&
        curl_easy_setopt(handle, CURLOPT_USERAGENT, user_agent.c_str()) == CURLE_OK &&
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, receive_body) == CURLE_OK &&
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response.body) == CURLE_OK &&
        (post.empty() || (
            curl_easy_setopt(handle, CURLOPT_POST, 1L) == CURLE_OK &&
            curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE_LARGE, curl_off_t(post.size())) == CURLE_OK &&
            curl_easy_setopt(handle, CURLOPT_POSTFIELDS, post.data()) == CURLE_OK &&
            curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers.get()) == CURLE_OK));
    if (!configured) return {-1, "Unable to enforce achievement connection policy."};
    const CURLcode result = curl_easy_perform(handle);
    if (result == CURLE_WRITE_ERROR) return {-1, "The achievement service response exceeds its size limit."};
    if (result == CURLE_OPERATION_TIMEDOUT) return {-2, "The achievement service connection failed or timed out."};
    if (result != CURLE_OK) return {-2, "The achievement service connection failed or timed out."};
    long status = 0;
    if (curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &status) != CURLE_OK || status <= 0)
        return {-2, "The achievement service returned an invalid response."};
    response.status = int(status);
    return response;
#else
    (void)url; (void)post; (void)content_type; (void)user_agent;
    return {-1, "Achievement networking is unavailable on this platform."};
#endif
}

bool save_credentials(const std::filesystem::path& directory, const Credentials& credentials) {
#ifdef _WIN32
    if (directory.empty() || !plain_field(credentials.username, 256) || !plain_field(credentials.token, 8192)) return false;
    SensitiveString plaintext;
    plaintext.value.assign(credential_magic);
    append_size(plaintext.value, credentials.username.size()); append_size(plaintext.value, credentials.token.size());
    plaintext.value.append(credentials.username); plaintext.value.append(credentials.token);
    DATA_BLOB input{DWORD(plaintext.value.size()), reinterpret_cast<BYTE*>(plaintext.value.data())};
    ProtectedBlob encrypted;
    if (!CryptProtectData(&input, L"Wave Race 64 RetroAchievements login", nullptr, nullptr, nullptr,
        CRYPTPROTECT_UI_FORBIDDEN, &encrypted.data) || encrypted.data.cbData > credential_limit) return false;
    std::error_code error;
    std::filesystem::create_directories(directory, error);
    if (error) return false;
    static std::atomic_uint64_t sequence{0};
    const auto target = directory / credential_filename;
    auto temporary = target;
    temporary += L".tmp-" + std::to_wstring(GetCurrentProcessId()) + L"-" +
        std::to_wstring(GetTickCount64()) + L"-" + std::to_wstring(++sequence);
    HANDLE file = CreateFileW(temporary.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_NEW,
        FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_TEMPORARY, nullptr);
    if (file == INVALID_HANDLE_VALUE) return false;
    DWORD written = 0;
    const bool complete = WriteFile(file, encrypted.data.pbData, encrypted.data.cbData, &written, nullptr) &&
        written == encrypted.data.cbData && FlushFileBuffers(file);
    CloseHandle(file);
    const bool saved = complete && MoveFileExW(temporary.c_str(), target.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH);
    if (!saved) DeleteFileW(temporary.c_str());
    return saved;
#elif defined(__linux__)
    if (directory.empty() || !plain_field(credentials.username, 256) || !plain_field(credentials.token, 8192)) return false;
    // Both fields exclude control characters, so a newline separates them.
    SensitiveString secret;
    secret.value = credentials.username + "\n" + credentials.token;
    const std::string profile = profile_key(directory);
    GError* error = nullptr;
    const gboolean stored = secret_password_store_sync(credential_schema(), SECRET_COLLECTION_DEFAULT,
        "Wave Race 64 RetroAchievements login", secret.value.c_str(), nullptr, &error,
        "profile", profile.c_str(), nullptr);
    if (error) g_error_free(error);
    return stored != FALSE;
#else
    (void)directory; (void)credentials; return false;
#endif
}

std::optional<Credentials> load_credentials(const std::filesystem::path& directory) {
#ifdef _WIN32
    if (directory.empty()) return {};
    const auto path = directory / credential_filename;
    std::error_code error;
    const auto size = std::filesystem::file_size(path, error);
    if (error || size == 0 || size > credential_limit) return {};
    std::string ciphertext(static_cast<std::size_t>(size), '\0');
    std::ifstream stream(path, std::ios::binary);
    if (!stream.read(ciphertext.data(), std::streamsize(ciphertext.size()))) return {};
    DATA_BLOB input{DWORD(ciphertext.size()), reinterpret_cast<BYTE*>(ciphertext.data())};
    ProtectedBlob plaintext;
    if (!CryptUnprotectData(&input, nullptr, nullptr, nullptr, nullptr, CRYPTPROTECT_UI_FORBIDDEN, &plaintext.data)) return {};
    const auto* bytes = plaintext.data.pbData;
    const std::size_t length = plaintext.data.cbData;
    if (length < credential_magic.size() + 8 || length > credential_limit ||
        std::memcmp(bytes, credential_magic.data(), credential_magic.size()) != 0) return {};
    const std::size_t username_length = read_size(bytes + credential_magic.size());
    const std::size_t token_length = read_size(bytes + credential_magic.size() + 4);
    const std::size_t header = credential_magic.size() + 8;
    if (!username_length || username_length > 256 || !token_length || token_length > 8192 ||
        username_length + token_length != length - header) return {};
    Credentials credentials{
        std::string(reinterpret_cast<const char*>(bytes + header), username_length),
        std::string(reinterpret_cast<const char*>(bytes + header + username_length), token_length)};
    if (!plain_field(credentials.username, 256) || !plain_field(credentials.token, 8192)) {
        erase_secret(credentials.token); return {};
    }
    return credentials;
#elif defined(__linux__)
    if (directory.empty()) return {};
    const std::string profile = profile_key(directory);
    GError* error = nullptr;
    gchar* stored = secret_password_lookup_sync(credential_schema(), nullptr, &error,
        "profile", profile.c_str(), nullptr);
    if (error) g_error_free(error);
    if (!stored) return {};
    SensitiveString secret;
    secret.value.assign(stored);
    secret_password_free(stored);
    const auto separator = secret.value.find('\n');
    if (separator == std::string::npos) return {};
    Credentials credentials{secret.value.substr(0, separator), secret.value.substr(separator + 1)};
    if (!plain_field(credentials.username, 256) || !plain_field(credentials.token, 8192)) {
        erase_secret(credentials.token); return {};
    }
    return credentials;
#else
    (void)directory; return {};
#endif
}

void remove_credentials(const std::filesystem::path& directory) {
    if (directory.empty()) return;
#if defined(__linux__)
    const std::string profile = profile_key(directory);
    GError* error = nullptr;
    secret_password_clear_sync(credential_schema(), nullptr, &error, "profile", profile.c_str(), nullptr);
    if (error) g_error_free(error);
#endif
    std::error_code ignored;
    std::filesystem::remove(directory / credential_filename, ignored);
}
} // namespace wr64::achievements::platform
