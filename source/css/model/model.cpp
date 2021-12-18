#include "model.h"

namespace css {

    std::string to_string_<px>::impl(px const& value) { return std::to_string(value.value) + "px"; }

}