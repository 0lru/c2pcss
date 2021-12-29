#pragma once

#include "color.h"
#include "enum_table.h"
#include "unit_based_value.h"

#include <optional>
#include <variant>
#include <vector>

namespace css {

const char px_unit_name[3] = "px";
const char em_unit_name[3] = "em";
const char rem_unit_name[4] = "rem";
const char percentage_unit_name[2] = "%";

struct px : public unit_based_value<float, px_unit_name> {
    using unit_based_value::unit_based_value;
};
struct em : public unit_based_value<float, em_unit_name> {
    using unit_based_value::unit_based_value;
};
struct rem : public unit_based_value<float, rem_unit_name> {
    using unit_based_value::unit_based_value;
};
struct percentage : public unit_based_value<float, percentage_unit_name> {
    using unit_based_value::unit_based_value;
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

enum class cascade {
    inherit,
    initial,
    unset
};

enum class position : std::uint8_t {
    static_,
    relative,
    fixed,
    absolute,
    sticky
};

enum class display {
    none,
    inline_,
    block,
    contents,
    list_item,
    inline_block,
    inline_table,
    table,
    table_cell,
    table_column,
    table_column_group,
    table_footer_group,
    table_header_group,
    table_row,
    table_row_group,
    flex,
    inline_flex,
    grid,
    inline_grid,
    ruby,
    ruby_base,
    ruby_text,
    ruby_base_container,
    ruby_text_container,
    run_in,
};

enum class direction {
    ltr = 0,
    rtl = 1
};

enum class box_sizing {
    content_box = 0,
    border_box = 1
};

enum class align_items {
    start = 0,
    center = 1,
    end = 2,
    stretch = 3,
    baseline = 4
};

enum class justify_content {
    space_between = 0,
    space_around = 1,
    start = 2,
    center = 3,
    end = 4
};

enum class font_style {
    normal,
    italic,
    oblique
};

using border_style_t = std::uint8_t;
enum class border_style : border_style_t {
    dotted,
    dashed,
    solid,
    double_,
    groove,
    ridge,
    inset,
    outset,
    none,
    hidden
};

template <typename T>
using cascaded = std::variant<cascade, T>;

// inherited:
// color, cursor, font*, direction, text*

}
