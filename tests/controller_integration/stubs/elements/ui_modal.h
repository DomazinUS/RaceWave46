#pragma once
#include <functional>
#include "recompinput/recompinput.h"
namespace recompui {
struct ContextId;
class TabbedModal;
namespace tab_callbacks {
using create_contents_t = std::function<void()>;
using can_close_t = std::function<bool()>;
using on_close_t = std::function<void()>;
}
}
