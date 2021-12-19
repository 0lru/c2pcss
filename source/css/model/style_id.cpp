#include "style_id.h"
#include "enum_table.h"

namespace css {

template <>
auto enum_table<style_id> = enum_meta<style_id>({

    { style_id::display, "display" },
    { style_id::box_sizing, "box-sizing" },
    { style_id::position, "position" },

    { style_id::left, "left" },
    { style_id::top, "top" },
    { style_id::right, "right" },
    { style_id::bottom, "bottom" },

    { style_id::width, "width" },
    { style_id::height, "height" },

    { style_id::border_left_width, "border-left-width" },
    { style_id::border_top_width, "border-top-width" },
    { style_id::border_right_width, "border-right-width" },
    { style_id::border_bottom_width, "border-bottom-width" },

    { style_id::margin_left, "margin-left" },
    { style_id::margin_top, "margin-top" },
    { style_id::margin_right, "margin-right" },
    { style_id::margin_bottom, "margin-bottom" },

    { style_id::padding_left, "padding-left" },
    { style_id::padding_top, "padding-top" },
    { style_id::padding_right, "padding-right" },
    { style_id::padding_bottom, "padding-bottom" },

    { style_id::font_size, "font-size" },
    { style_id::font_family, "font-family" },
    { style_id::font_style, "font-style" },

    { style_id::color, "color" },
    { style_id::background_color, "background-color" },

    { style_id::flex_grow, "flex-grow" },
    { style_id::flex_basis, "flex-basis" },
    { style_id::flex_shrink, "flex-shrink" },
    { style_id::flex_direction, "flex-direction" },

    { style_id::writing_mode, "writing-mode" },
    { style_id::direction, "direction" }

});

}