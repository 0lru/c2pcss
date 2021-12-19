#include <catch2/catch.hpp>
#include <css/model/model.h>
#include <css/parse.h>

namespace css::test {

// ("[^_]*)_([^"]")
TEST_CASE("can parse display", "[parser][selector]")
{
    REQUIRE(parse<display>("none") == display::none);
    REQUIRE(parse<display>("inline") == display::inline_);
    REQUIRE(parse<display>("block") == display::block);
    REQUIRE(parse<display>("contents") == display::contents);
    REQUIRE(parse<display>("list-item") == display::list_item);
    REQUIRE(parse<display>("inline-block") == display::inline_block);
    REQUIRE(parse<display>("inline-table") == display::inline_table);
    REQUIRE(parse<display>("table") == display::table);
    REQUIRE(parse<display>("table-cell") == display::table_cell);
    REQUIRE(parse<display>("table-column") == display::table_column);
    REQUIRE(parse<display>("table-column-group") == display::table_column_group);
    REQUIRE(parse<display>("table-footer-group") == display::table_footer_group);
    REQUIRE(parse<display>("table-header-group") == display::table_header_group);
    REQUIRE(parse<display>("table-row") == display::table_row);
    REQUIRE(parse<display>("table-row-group") == display::table_row_group);
    REQUIRE(parse<display>("flex") == display::flex);
    REQUIRE(parse<display>("inline-flex") == display::inline_flex);
    REQUIRE(parse<display>("grid") == display::grid);
    REQUIRE(parse<display>("inline-grid") == display::inline_grid);
    REQUIRE(parse<display>("ruby") == display::ruby);
    REQUIRE(parse<display>("ruby-base") == display::ruby_base);
    REQUIRE(parse<display>("ruby-text") == display::ruby_text);
    REQUIRE(parse<display>("ruby-base-container") == display::ruby_base_container);
    REQUIRE(parse<display>("ruby-text-container") == display::ruby_text_container);
    REQUIRE(parse<display>("run-in") == display::run_in);
}

}
