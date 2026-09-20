#include "program_config.h"

static std::string program_name = "";
static std::u8string program_id = u8"";

namespace recompui {
    namespace programconfig {
        void set_program_name(const std::string& name) {
            program_name = name;
        }

        void set_program_id(const std::u8string& id) {
            program_id = id;
        }

        const std::string &get_program_name() {
            if (program_name.empty()) {
                throw std::runtime_error("Program name has not been set. Run recompui::programconfig::set_program_name(...) first.");
            }
            return program_name;
        }

        const std::u8string &get_program_id() {
            if (program_id.empty()) {
                throw std::runtime_error("Program ID has not been set. Run recompui::programconfig::set_program_id(...) first.");
            }
            return program_id;
        }
    }
}
