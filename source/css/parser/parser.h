#include "input.h"

#include <css/model/model.h>

namespace css::parser {

//
// this is template for "mini parsers". e.g. for each typ in "model.h",
// there exists one parser. with this any type can be constructed from string.
template <typename T, typename = void>
struct parser {
    static void parse(input&, T&);
};

}
