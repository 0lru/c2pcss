#include "style.h"
#include "enum_table.h"

namespace css {

template <>
auto enum_table<style> = enum_meta<style>({

    { style::display, "display" },
    { style::box_sizing, "box-sizing" },
    { style::position, "position" },

    { style::left, "left" },
    { style::top, "top" },
    { style::right, "right" },
    { style::bottom, "bottom" },

    { style::width, "width" },
    { style::height, "height" },

    { style::border_left_width, "border-left-width" },
    { style::border_top_width, "border-top-width" },
    { style::border_right_width, "border-right-width" },
    { style::border_bottom_width, "border-bottom-width" },

    { style::margin_left, "margin-left" },
    { style::margin_top, "margin-top" },
    { style::margin_right, "margin-right" },
    { style::margin_bottom, "margin-bottom" },

    { style::padding_left, "padding-left" },
    { style::padding_top, "padding-top" },
    { style::padding_right, "padding-right" },
    { style::padding_bottom, "padding-bottom" },

    { style::font_size, "font-size" },
    { style::font_family, "font-family" },
    { style::font_style, "font-style" },

    { style::color, "color" },
    { style::background_color, "background-color" },

    { style::flex_grow, "flex-grow" },
    { style::flex_basis, "flex-basis" },
    { style::flex_shrink, "flex-shrink" },
    { style::flex_direction, "flex-direction" },

    { style::writing_mode, "writing-mode" },
    { style::direction, "direction" }

});

}