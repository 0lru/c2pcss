#include <catch2/catch.hpp>
#include <css/model/model.h>
#include <css/parse.h>

namespace css::test {

TEST_CASE("can parse box-sizing", "[parser][style]")
{
    REQUIRE(parse<box_sizing>("content-box") == box_sizing::content_box);
    REQUIRE(parse<box_sizing>("border-box") == box_sizing::border_box);
}

TEST_CASE("can parse box-sizing inside declaration block", "[parser][style]")
{
    declaration_block block;
    REQUIRE_NOTHROW(parse(R"({ box-sizing: content-box })", block));
    REQUIRE(block.size() == 1);
    auto cascaded = block.get<style_id::box_sizing>();
    REQUIRE(std::holds_alternative<box_sizing>(cascaded));
    REQUIRE(std::get<box_sizing>(cascaded) == box_sizing::content_box);
}

}