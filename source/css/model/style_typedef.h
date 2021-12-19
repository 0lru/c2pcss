#pragma once

//
// this maps tyle identifiers, which are enumeration values to their types

#include "style_id.h"
#include "style_types.h"

namespace css {

template<style_id s>
class style_typedef;

/*template <style t>
class style_definition {
};*/

/*template <>
class style_definition<style::left> {
    using type_t = css::length_percentage;
};*/

/*
template <>
struct style_definition<style::display> {
    using type_t = css::display;
};*/
/*
    template<style t> struct style_definition{};
    template<> struct style_definition<style::display> { using type = css::display; };
    template<> struct style_definition<style::box_sizing> { using type = css::box_sizing; };
    template<> struct style_definition<style::position> { using type = css::position; };
    template<> struct style_definition<style::top> { using type = css::length_percentage; };
    template<> struct style_definition<style::right> { using type = css::length_percentage; };
    template<> struct style_definition<style::bottom> { using type = css::length_percentage; };
    template<> struct style_definition<style::width> { using type = css::length_percentage; };
    template<> struct style_definition<style::height> { using type = css::length_percentage; };
    template<> struct style_definition<style::border_left_width> { using type = css::length_percentage; };
    template<> struct style_definition<style::border_top_width> { using type = css::length_percentage; };
    template<> struct style_definition<style::border_right_width> { using type = css::length_percentage; };
    template<> struct style_definition<style::border_bottom_width> { using type = css::length_percentage; };
    template<> struct style_definition<style::margin_left> { using type = css::length_percentage; };
    template<> struct style_definition<style::margin_top> { using type = css::length_percentage; };
    template<> struct style_definition<style::margin_right> { using type = css::length_percentage; };
    template<> struct style_definition<style::margin_bottom> { using type = css::length_percentage; };
    template<> struct style_definition<style::padding_left> { using type = css::length_percentage; };
    template<> struct style_definition<style::padding_top> { using type = css::length_percentage; };
    template<> struct style_definition<style::padding_right> { using type = css::length_percentage; };
    template<> struct style_definition<style::padding_bottom> { using type = css::length_percentage; };
    template<> struct style_definition<style::font_size> { using type = css::font_size; };
    template<> struct style_definition<style::font_family> { using type = css::font_family; };
    template<> struct style_definition<style::font_style> { using type = css::font_style; };
    template<> struct style_definition<style::color> { using type = css::color; };
    template<> struct style_definition<style::background_color> { using type = css::optional_color; };
    template<> struct style_definition<style::flex_basis> { using type = css::flex_basis; };
    template<> struct style_definition<style::flex_grow> { using type = css::number; };
    template<> struct style_definition<style::flex_shrink> { using type = css::number; };
    template<> struct style_definition<style::flex_direction> { using type = css::flex_direction; };
    template<> struct style_definition<style::writing_mode> { using type = css::writing_mode; };
    template<> struct style_definition<style::direction> { using type = css::direction; };
    */

}
