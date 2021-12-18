#pragma once

#include "color.h"
#include "typed.h"

#include <optional>
#include <variant>
#include <vector>

namespace css {

enum class cascade {
    inherit,
    initial
};

template <typename T>
using cascadable = std::variant<cascade, T>;

struct px : public typed<float> {
};

struct em : public typed<float> {
};
struct rem : public typed<float> {
};
struct percentage : public typed<float> {
};

using length = std::variant<px, em, rem>;

using length_percentage = std::variant<length, percentage>;

enum class combinator {
    plus, // '+'
    tilde, // '~'
    greater, // '>'
};

struct type_selector : public typed<std::string> {
};
struct hash_selector : public typed<std::string> {
};
struct class_selector : public typed<std::string> {
};
struct pseudo_selector : public typed<std::string> {
};

//
// this "includes" the <compound-selector> ..
struct compound_selector {
    // optional combinator
    std::optional<combinator> combinator;

    // universal selector '*' is represented as std::nullopt
    std::optional<type_selector> type_selector;

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

// ?
struct rule_set {
    selector_list selector_list;
    /*declaration block*/
};

}
