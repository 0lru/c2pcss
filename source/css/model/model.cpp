#include "model.h"

namespace css {

std::string to_string_<px>::impl(px const& value) { return std::to_string(value.value) + "px"; }
px operator"" _px(const char* value) { return px { std::stof(value) }; }
em operator"" _em(const char* value) { return em { std::stof(value) }; }
rem operator"" _rem(const char* value) { return rem { std::stof(value) }; }
percentage operator"" _percent(const char* value) { return percentage { std::stof(value) }; }

}