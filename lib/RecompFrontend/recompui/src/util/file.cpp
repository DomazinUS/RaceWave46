#include "file.h"

#include <SDL.h>
#include "nfd.h"
#include "RmlUi/Core.h"

#include "recompui/program_config.h"

#include <filesystem>
#include <fstream>
#include <iomanip>

#if defined(_WIN32)
#include <Shlobj.h>
#elif defined(__linux__)
#include <unistd.h>
#include <pwd.h>
#elif defined(__APPLE__)
#include "apple/rt64_apple.h"
#endif

namespace recompui {
    static void perform_file_dialog_operation(const std::function<void(bool, const std::filesystem::path&)>& callback) {
        nfdnchar_t* native_path = nullptr;
        nfdresult_t result = NFD_OpenDialogN(&native_path, nullptr, 0, nullptr);

        bool success = (result == NFD_OKAY);
        std::filesystem::path path;

        if (success) {
            path = std::filesystem::path{native_path};
            NFD_FreePathN(native_path);
        }

        callback(success, path);
    }

    static void perform_file_dialog_operation_multiple(const std::function<void(bool, const std::list<std::filesystem::path>&)>& callback) {
        const nfdpathset_t* native_paths = nullptr;
        nfdresult_t result = NFD_OpenDialogMultipleN(&native_paths, nullptr, 0, nullptr);

        bool success = (result == NFD_OKAY);
        std::list<std::filesystem::path> paths;
        nfdpathsetsize_t count = 0;

        if (success) {
            NFD_PathSet_GetCount(native_paths, &count);
            for (nfdpathsetsize_t i = 0; i < count; i++) {
                nfdnchar_t* cur_path = nullptr;
                nfdresult_t cur_result = NFD_PathSet_GetPathN(native_paths, i, &cur_path);
                if (cur_result == NFD_OKAY) {
                    paths.emplace_back(std::filesystem::path{cur_path});
                }
            }
            NFD_PathSet_Free(native_paths);
        }

        callback(success, paths);
    }

    std::filesystem::path file::get_app_folder_path() {
        // directly check for portable.txt (windows and native linux binary)
        if (std::filesystem::exists("portable.txt")) {
            return std::filesystem::current_path();
        }

#if defined(__APPLE__)
        // Check for portable file in the directory containing the app bundle.
        const auto app_bundle_path = file::apple::get_bundle_directory().parent_path();
        if (std::filesystem::exists(app_bundle_path / "portable.txt")) {
            return app_bundle_path;
        }
#endif

        std::filesystem::path recomp_dir{};

#if defined(_WIN32)
        // Deduce local app data path.
        PWSTR known_path = NULL;
        HRESULT result = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &known_path);
        if (result == S_OK) {
            recomp_dir = std::filesystem::path{known_path} / programconfig::get_program_id();
        }

        CoTaskMemFree(known_path);
#elif defined(__linux__) || defined(__APPLE__)
        // check for APP_FOLDER_PATH env var
        if (getenv("APP_FOLDER_PATH") != nullptr) {
            return std::filesystem::path{getenv("APP_FOLDER_PATH")};
        }

#if defined(__APPLE__)
        const auto supportdir = file::apple::get_application_support_directory();
        if (supportdir) {
            return *supportdir / programconfig::get_program_id();
        }
#endif

        const char *homedir;

        if ((homedir = getenv("HOME")) == nullptr) {
            #if defined(__linux__)
            homedir = getpwuid(getuid())->pw_dir;
            #elif defined(__APPLE__)
                homedir = GetHomeDirectory();
            #endif
        }

        if (homedir != nullptr) {
            recomp_dir = std::filesystem::path{homedir} / (std::u8string{u8".config/"} + programconfig::get_program_id());
        }
#endif

        return recomp_dir;
    }

    std::filesystem::path file::get_program_path() {
#if defined(__APPLE__)
        return file::apple::get_bundle_resource_directory();
#elif defined(__linux__) && defined(RECOMP_FLATPAK)
        return "/app/bin";
#elif defined(_WIN32)
        // Absolute executable launches must find bundled fonts and styling
        // even when the caller's current directory is another repository.
        std::wstring executable(32768, L'\0');
        const DWORD length = GetModuleFileNameW(nullptr, executable.data(), DWORD(executable.size()));
        if (length == 0 || length >= executable.size()) return "";
        executable.resize(length);
        return std::filesystem::path(executable).parent_path();
#else
        return "";
#endif
    }

    std::filesystem::path file::get_asset_path(const char* asset) {
        return file::get_program_path() / "assets" / asset;
    }

    void file::open_file_dialog(std::function<void(bool success, const std::filesystem::path& path)> callback) {
#ifdef __APPLE__
        file::apple::dispatch_on_ui_thread([callback]() {
            perform_file_dialog_operation(callback);
        });
#else
        perform_file_dialog_operation(callback);
#endif
    }

    void file::open_file_dialog_multiple(std::function<void(bool success, const std::list<std::filesystem::path>& paths)> callback) {
#ifdef __APPLE__
        file::apple::dispatch_on_ui_thread([callback]() {
            perform_file_dialog_operation_multiple(callback);
        });
#else
        perform_file_dialog_operation_multiple(callback);
#endif
    }

    void file::show_error_message_box(const char *title, const char *message) {
#ifdef __APPLE__
    std::string title_copy(title);
    std::string message_copy(message);

    file::apple::dispatch_on_ui_thread([title_copy, message_copy] {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title_copy.c_str(), message_copy.c_str(), nullptr);
    });
#else
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, nullptr);
#endif
    }
}
