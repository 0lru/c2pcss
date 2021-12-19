#pragma once

#include "color.h"
#include "enum_table.h"
#include "unit_based_value.h"

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

const char px_unit_name[3] = "px";
const char em_unit_name[3] = "em";
const char rem_unit_name[4] = "rem";
const char percentage_unit_name[2] = "%";

struct px : public unit_based_value<float, px_unit_name> {
};
struct em : public unit_based_value<float, em_unit_name> {
};
struct rem : public unit_based_value<float, rem_unit_name> {
};
struct percentage : public unit_based_value<float, percentage_unit_name> {
};

px operator"" _px(const char* value);
em operator"" _em(const char* value);
rem operator"" _rem(const char* value);
percentage operator"" _percent(const char* value);

using length = std::variant<px, em, rem>;
using length_percentage = std::variant<length, percentage>;
//using length_percentage = std::variant<px, em, rem, percentage>;

enum class combinator {
    plus, // '+'
    tilde, // '~'
    greater, // '>'
};

struct type_selector {
    std::string target;
};
struct hash_selector {
    std::string target;
};
struct class_selector {
    std::string target;
};
struct pseudo_selector {
    std::string target;
};

//
// this is/"includes" the <compound-selector> ..
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

enum class position {
    absolute,
    static_,
    // ...
};

}
