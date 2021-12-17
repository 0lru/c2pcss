#pragma once
#include "color.h"

#include <optional>
#include <variant>
#include <vector>

namespace css {

//
// simple typedef to make clear, that our intent is to parse utf8-aware
using utf8_t = char;
using pos = utf8_t const*;
using string = std::string; 
// using code_point = std::int16_t.. etc.

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
// <complex-selector> = <compound-selector> [ <combinator>? <compound-selector> ]*
//
using complex_selector = std::vector<compound_selector>;

//
// <selector-list> = <complex-selector-list> = <complex-selector>#
using selector_list = std::vector<complex_selector>;

}
