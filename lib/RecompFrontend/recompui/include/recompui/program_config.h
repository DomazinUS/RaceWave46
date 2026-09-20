#pragma once

#include "recompui.h"
#include <string>

namespace recompui {
    namespace programconfig {
        void set_program_name(const std::string& name);
        void set_program_id(const std::u8string& id);
        const std::string &get_program_name();
        const std::u8string &get_program_id();
    }
}
