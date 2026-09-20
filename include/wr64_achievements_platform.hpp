#pragma once
#include <filesystem>
#include <optional>
#include <string>

namespace wr64::achievements::platform {
struct HttpResponse { int status = -2; std::string body; };
HttpResponse http_request(const std::string& url, const std::string& post,
    const std::string& content_type, const std::string& user_agent);
struct Credentials { std::string username, token; };
std::optional<Credentials> load_credentials(const std::filesystem::path& directory);
bool save_credentials(const std::filesystem::path& directory, const Credentials& credentials);
void remove_credentials(const std::filesystem::path& directory);
void erase_secret(std::string& value);
}
