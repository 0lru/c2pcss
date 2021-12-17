#pragma once
#include "color.h"

#include <optional>
#include <variant>
#include <vector>

namespace css {

//
// we assume fixed width (1,2,3,4 ... bytes) code points. revise: can we migrate to icu..?
using code_point = char;
using pos = code_point const*;
using string = std::string;

enum class cascade {
    inherit,
    initial
};

template <typename T>
using cascadable = std::variant<cascade, T>;

struct px {
    float value;
};

struct em {
    float value;
};

struct rem {
    float value;
};

struct percentage {
    float value;
};

using length = std::variant<px, em, rem>;

using length_percentage = std::variant<length, percentage>;

enum class combinator {
    plus, // '+'
    tilde, // '~'
    greater, // '>'
};

struct type_selector {
    string value;
};
struct hash_selector {
    string value;
};
struct class_selector {
    string value;
};
struct pseudo_selector {
    string value;
};

//
// this "includes" the <compound-selector> ..
struct compound_selector {
    // optional combinator
    std::optional<combinator> combinator;

    // this can also contain the universal selector '*'
    type_selector type_selector = css::type_selector { "*" };

    // example: 'my-item' for '#my-item'
    std::vector<hash_selector> hash_selectors;
    // example: 'xyz' for '.xyz'
    std::vector<class_selector> class_selectors;
    // example: 'hover' for ':hover'
    std::vector<pseudo_selector> pseudo_selectors;
    //
    // TODO: functional sel.
};

//
// <compound-selector> [ <combinator>? <compound-selector> ]*
//
using complex_selector = std::vector<compound_selector>;

//
// separated by comma:
// <selector-list> = <complex-selector-list> = <complex-selector>#
using selector_list = std::vector<complex_selector>;

}
