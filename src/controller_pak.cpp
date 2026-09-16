#include "wr64_diagnostic_policy.h"
#include "wr64_controller_pak.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <fstream>
#include <mutex>
#include <optional>
#include <vector>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#endif

#include "librecomp/files.hpp"
#include "ultramodern/ultramodern.hpp"

namespace wr64::controller_pak {
namespace {

constexpr std::array<std::uint8_t, 8> kMagic = {'W', 'R', '6', '4', 'P', 'A', 'K', '1'};
constexpr std::uint32_t kFormatVersion = 1;

template <typename T>
bool read_scalar(std::istream& stream, T& value) {
    stream.read(reinterpret_cast<char*>(&value), sizeof(value));
    return stream.good();
}

template <typename T>
void write_scalar(std::ostream& stream, T value) {
    stream.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

std::size_t allocated_size(std::size_t size) {
    return (size + kPageSize - 1) & ~(kPageSize - 1);
}

} // namespace

struct Store::Impl {
    struct Entry {
        bool occupied = false;
        Key key{};
        std::vector<std::uint8_t> data{};
    };

    struct Pak {
        bool loaded = false;
        Result load_result = Result::Ok;
        std::array<Entry, kDirectoryEntryCount> entries{};
    };

    std::mutex mutex{};
    std::array<Pak, kPortCount> paks{};
    std::optional<std::filesystem::path> test_base_path{};

    std::filesystem::path path_for_port(int port) const {
        std::filesystem::path path = test_base_path.value_or(ultramodern::get_save_file_path());
        path.replace_extension();
        path += ".controller-pak-" + std::to_string(port + 1) + ".bin";
        return path;
    }

    bool valid_port(int port) const {
        return port >= 0 && port < kPortCount;
    }

    Result load(int port) {
        Pak& pak = paks[port];
        if (pak.loaded) {
            return pak.load_result;
        }
        pak.loaded = true;

        const std::filesystem::path path = path_for_port(port);
        std::error_code ec;
        std::filesystem::create_directories(path.parent_path(), ec);
        if (ec) return pak.load_result = Result::ControllerFailure;
        std::ifstream input = recomp::open_input_file_with_backup(path, std::ios::binary);
        if (!input.good()) {
            auto backup_path = path;
            backup_path += ".bak";
            const bool primary_exists = std::filesystem::exists(path, ec);
            if (ec) return pak.load_result = Result::ControllerFailure;
            const bool backup_exists = std::filesystem::exists(backup_path, ec);
            if (ec || primary_exists || backup_exists) {
                return pak.load_result = Result::ControllerFailure;
            }
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[controller-pak] port %d formatted (new persistent Pak)\n", port + 1));
            return Result::Ok;
        }

        // Decode into a candidate. A damaged image remains on disk and cannot
        // become a writable empty Pak through a later allocation.
        Pak candidate{};
        candidate.loaded = true;
        const auto invalid_image = [&]() {
            std::fprintf(stderr, "[controller-pak] port %d image is inconsistent\n", port + 1);
            return pak.load_result = Result::Inconsistent;
        };

        std::array<std::uint8_t, kMagic.size()> magic{};
        std::uint32_t version = 0;
        input.read(reinterpret_cast<char*>(magic.data()), magic.size());
        if (!input.good() || magic != kMagic || !read_scalar(input, version) ||
            version != kFormatVersion) {
            return invalid_image();
        }

        std::size_t used = 0;
        for (Entry& entry : candidate.entries) {
            std::uint8_t occupied = 0;
            std::uint32_t size = 0;
            if (!read_scalar(input, occupied) || !read_scalar(input, entry.key.company_code) ||
                !read_scalar(input, entry.key.game_code)) {
                return invalid_image();
            }
            input.read(reinterpret_cast<char*>(entry.key.game_name.data()), entry.key.game_name.size());
            input.read(reinterpret_cast<char*>(entry.key.extension_name.data()), entry.key.extension_name.size());
            if (!input.good() || !read_scalar(input, size) || size > kCapacityBytes ||
                occupied > 1 || (occupied == 0 && size != 0) ||
                (occupied == 1 && size == 0)) {
                return invalid_image();
            }
            const std::size_t pages_used = allocated_size(size);
            if (pages_used > kCapacityBytes - used) return invalid_image();
            used += pages_used;
            if (occupied != 0) {
                for (const Entry& previous : candidate.entries) {
                    if (&previous == &entry) break;
                    if (previous.occupied && previous.key == entry.key) return invalid_image();
                }
            }
            entry.occupied = occupied != 0;
            entry.data.resize(entry.occupied ? size : 0);
            if (entry.occupied && size != 0) {
                input.read(reinterpret_cast<char*>(entry.data.data()), size);
                if (!input.good()) {
                    return invalid_image();
                }
            }
        }
        if (input.peek() != std::char_traits<char>::eof() || input.bad()) return invalid_image();
        pak = std::move(candidate);

        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[controller-pak] port %d loaded from %s\n",
                     port + 1, path.string().c_str()));
        return Result::Ok;
    }

    bool save(int port, const Pak& candidate) {
        const std::filesystem::path path = path_for_port(port);
        std::ofstream output = recomp::open_output_file_with_backup(path, std::ios::binary);
        if (!output.good()) {
            return false;
        }
        output.write(reinterpret_cast<const char*>(kMagic.data()), kMagic.size());
        write_scalar(output, kFormatVersion);
        for (const Entry& entry : candidate.entries) {
            write_scalar(output, static_cast<std::uint8_t>(entry.occupied ? 1 : 0));
            write_scalar(output, entry.key.company_code);
            write_scalar(output, entry.key.game_code);
            output.write(reinterpret_cast<const char*>(entry.key.game_name.data()), entry.key.game_name.size());
            output.write(reinterpret_cast<const char*>(entry.key.extension_name.data()), entry.key.extension_name.size());
            write_scalar(output, static_cast<std::uint32_t>(entry.data.size()));
            if (!entry.data.empty()) {
                output.write(reinterpret_cast<const char*>(entry.data.data()), entry.data.size());
            }
        }
        output.flush();
        if (!output.good()) return false;
        output.close();
        if (!output.good()) return false;

        // Preserve the last complete image until an atomic replacement succeeds.
        // The generic helper copies over the primary and can truncate it on a
        // failed write, so keep its filenames but finalize this small store here.
        auto temporary = path;
        temporary += ".temp";
        auto backup = path;
        backup += ".bak";
        std::error_code ec;
        const bool primary_exists = std::filesystem::exists(path, ec);
        if (ec) return false;
        if (primary_exists) {
            std::filesystem::copy_file(path, backup,
                std::filesystem::copy_options::overwrite_existing, ec);
            if (ec) return false;
        }
#ifdef _WIN32
        return MoveFileExW(temporary.c_str(), path.c_str(),
            MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != 0;
#else
        std::filesystem::rename(temporary, path, ec);
        return !ec;
#endif
    }

    std::size_t used_bytes(int port) const {
        std::size_t used = 0;
        for (const Entry& entry : paks[port].entries) {
            if (entry.occupied) {
                used += allocated_size(entry.data.size());
            }
        }
        return used;
    }
};

Store::Store() : impl_(new Impl{}) {}
Store::~Store() { delete impl_; }

Store& Store::instance() {
    static Store store{};
    return store;
}

void Store::set_base_save_path_for_tests(std::filesystem::path path) {
    std::lock_guard lock{impl_->mutex};
    impl_->test_base_path = std::move(path);
    impl_->paks = {};
}

void Store::reset_for_tests() {
    std::lock_guard lock{impl_->mutex};
    impl_->paks = {};
}

Result Store::initialize(int port) {
    std::lock_guard lock{impl_->mutex};
    if (!impl_->valid_port(port)) return Result::NoPack;
    return impl_->load(port);
}

Result Store::find_file(int port, const Key& key, int& file_number) {
    std::lock_guard lock{impl_->mutex};
    if (!impl_->valid_port(port)) return Result::NoPack;
    const Result load_result = impl_->load(port);
    if (load_result != Result::Ok) return load_result;
    for (int i = 0; i < kDirectoryEntryCount; ++i) {
        const Impl::Entry& entry = impl_->paks[port].entries[i];
        if (entry.occupied && entry.key == key) {
            file_number = i;
            return Result::Ok;
        }
    }
    return Result::Invalid;
}

Result Store::free_blocks(int port, std::int32_t& bytes_free) {
    std::lock_guard lock{impl_->mutex};
    if (!impl_->valid_port(port)) return Result::NoPack;
    const Result load_result = impl_->load(port);
    if (load_result != Result::Ok) return load_result;
    bytes_free = static_cast<std::int32_t>(kCapacityBytes - impl_->used_bytes(port));
    return Result::Ok;
}

Result Store::num_files(int port, std::int32_t& max_files, std::int32_t& files_used) {
    std::lock_guard lock{impl_->mutex};
    if (!impl_->valid_port(port)) return Result::NoPack;
    const Result load_result = impl_->load(port);
    if (load_result != Result::Ok) return load_result;
    max_files = kDirectoryEntryCount;
    files_used = static_cast<std::int32_t>(std::count_if(
        impl_->paks[port].entries.begin(), impl_->paks[port].entries.end(),
        [](const Impl::Entry& entry) { return entry.occupied; }));
    return Result::Ok;
}

Result Store::file_state(int port, int file_number, FileState& state) {
    std::lock_guard lock{impl_->mutex};
    if (!impl_->valid_port(port)) return Result::NoPack;
    const Result load_result = impl_->load(port);
    if (load_result != Result::Ok) return load_result;
    if (file_number < 0 || file_number >= kDirectoryEntryCount) return Result::Invalid;
    const Impl::Entry& entry = impl_->paks[port].entries[file_number];
    if (!entry.occupied) return Result::Invalid;
    state.file_size = static_cast<std::uint32_t>(entry.data.size());
    state.key = entry.key;
    return Result::Ok;
}

Result Store::allocate_file(int port, const Key& key, std::uint32_t file_size,
                            int& file_number) {
    std::lock_guard lock{impl_->mutex};
    if (!impl_->valid_port(port)) return Result::NoPack;
    const Result load_result = impl_->load(port);
    if (load_result != Result::Ok) return load_result;
    if (file_size == 0 || allocated_size(file_size) > kCapacityBytes) return Result::Invalid;
    for (const Impl::Entry& entry : impl_->paks[port].entries) {
        if (entry.occupied && entry.key == key) return Result::Exists;
    }
    if (impl_->used_bytes(port) + allocated_size(file_size) > kCapacityBytes) {
        return Result::DataFull;
    }
    for (int i = 0; i < kDirectoryEntryCount; ++i) {
        if (!impl_->paks[port].entries[i].occupied) {
            Impl::Pak candidate = impl_->paks[port];
            Impl::Entry& entry = candidate.entries[i];
            entry.occupied = true;
            entry.key = key;
            entry.data.assign(file_size, 0);
            if (!impl_->save(port, candidate)) return Result::ControllerFailure;
            impl_->paks[port] = std::move(candidate);
            file_number = i;
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[controller-pak] port %d allocated file %d (%u bytes)\n",
                         port + 1, i, file_size));
            return Result::Ok;
        }
    }
    return Result::DirectoryFull;
}

Result Store::delete_file(int port, const Key& key) {
    std::lock_guard lock{impl_->mutex};
    if (!impl_->valid_port(port)) return Result::NoPack;
    const Result load_result = impl_->load(port);
    if (load_result != Result::Ok) return load_result;
    Impl::Pak candidate = impl_->paks[port];
    for (Impl::Entry& entry : candidate.entries) {
        if (entry.occupied && entry.key == key) {
            entry = {};
            if (!impl_->save(port, candidate)) return Result::ControllerFailure;
            impl_->paks[port] = std::move(candidate);
            return Result::Ok;
        }
    }
    return Result::Invalid;
}

Result Store::read_file(int port, int file_number, std::uint32_t offset,
                        std::span<std::uint8_t> output) {
    std::lock_guard lock{impl_->mutex};
    if (!impl_->valid_port(port)) return Result::NoPack;
    const Result load_result = impl_->load(port);
    if (load_result != Result::Ok) return load_result;
    if (file_number < 0 || file_number >= kDirectoryEntryCount) return Result::Invalid;
    const Impl::Entry& entry = impl_->paks[port].entries[file_number];
    if (!entry.occupied || offset > entry.data.size() || output.size() > entry.data.size() - offset) {
        return Result::Invalid;
    }
    std::copy_n(entry.data.begin() + offset, output.size(), output.begin());
    return Result::Ok;
}

Result Store::write_file(int port, int file_number, std::uint32_t offset,
                         std::span<const std::uint8_t> input) {
    std::lock_guard lock{impl_->mutex};
    if (!impl_->valid_port(port)) return Result::NoPack;
    const Result load_result = impl_->load(port);
    if (load_result != Result::Ok) return load_result;
    if (file_number < 0 || file_number >= kDirectoryEntryCount) return Result::Invalid;
    Impl::Pak candidate = impl_->paks[port];
    Impl::Entry& entry = candidate.entries[file_number];
    if (!entry.occupied || offset > entry.data.size() || input.size() > entry.data.size() - offset) {
        return Result::Invalid;
    }
    std::copy(input.begin(), input.end(), entry.data.begin() + offset);
    if (!impl_->save(port, candidate)) return Result::ControllerFailure;
    impl_->paks[port] = std::move(candidate);
    return Result::Ok;
}

} // namespace wr64::controller_pak
