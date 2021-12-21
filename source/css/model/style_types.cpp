#include "model.h"

namespace css {

px operator"" _px(const char* value) { return px(value); }
em operator"" _em(const char* value) { return em { value }; }
rem operator"" _rem(const char* value) { return rem { value }; }
percentage operator"" _percent(const char* value) { return percentage { value }; }

template <>
auto enum_table<cascade> = enum_meta<cascade>({

    { cascade::initial, "initial" },
    { cascade::inherit, "inherit" },
    { cascade::unset, "unset" }

});

template <>
auto enum_table<position> = enum_meta<position>({

    { position::static_, "static" },
    { position::relative, "relative" },
    { position::fixed, "fixed" },
    { position::absolute, "absolute" },
    { position::sticky, "sticky" }

});

// "("[^_]*)(_) -> $1-
template <>
auto enum_table<display> = enum_meta<display>({
    { display::none, "none" },
    { display::inline_, "inline" },
    { display::block, "block" },
    { display::contents, "contents" },
    { display::list_item, "list-item" },
    { display::inline_block, "inline-block" },
    { display::inline_table, "inline-table" },
    { display::table, "table" },
    { display::table_cell, "table-cell" },
    { display::table_column, "table-column" },
    { display::table_column_group, "table-column-group" },
    { display::table_footer_group, "table-footer-group" },
    { display::table_header_group, "table-header-group" },
    { display::table_row, "table-row" },
    { display::table_row_group, "table-row-group" },
    { display::flex, "flex" },
    { display::inline_flex, "inline-flex" },
    { display::grid, "grid" },
    { display::inline_grid, "inline-grid" },
    { display::ruby, "ruby" },
    { display::ruby_base, "ruby-base" },
    { display::ruby_text, "ruby-text" },
    { display::ruby_base_container, "ruby-base-container" },
    { display::ruby_text_container, "ruby-text-container" },
    { display::run_in, "run-in" },
});

template <>
auto enum_table<direction> = enum_meta<direction>({ { direction::ltr, "ltr" },
    { direction::rtl, "rtl" } });

template <>
auto enum_table<box_sizing> = enum_meta<box_sizing>({ { box_sizing::content_box, "content-box" },
    { box_sizing::border_box, "border-box" } });

}
