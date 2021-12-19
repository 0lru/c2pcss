#include <catch2/catch.hpp>
#include <css/model/model.h>
#include <css/parse.h>

namespace css::test {

//
// don't make to_string test, since a test of enum_meta-class is sufficient
TEST_CASE("can parse cascaded value", "[parser][style]")
{
    {
        cascaded<position> cascaded_position;
        parse("initial", cascaded_position);
        REQUIRE(std::holds_alternative<cascade>(cascaded_position));
        REQUIRE(std::get<cascade>(cascaded_position) == cascade::initial);
    }
    {
        cascaded<position> cascaded_position;
        parse("inherit", cascaded_position);
        REQUIRE(std::holds_alternative<cascade>(cascaded_position));
        REQUIRE(std::get<cascade>(cascaded_position) == cascade::inherit);
    }
    {
        cascaded<position> cascaded_position;
        parse("unset", cascaded_position);
        REQUIRE(std::holds_alternative<cascade>(cascaded_position));
        REQUIRE(std::get<cascade>(cascaded_position) == cascade::unset);
    }
}

TEST_CASE("can parse cascaded inside declaration block", "[parser][style]")
{
    {
        declaration_block block;
        REQUIRE_NOTHROW(parse(R"({ position: unset })", block));
        REQUIRE(block.size() == 1);
        auto cascaded_position = block.get<style_id::position>();
        REQUIRE(std::holds_alternative<cascade>(cascaded_position));
        REQUIRE(std::get<cascade>(cascaded_position) == cascade::unset);
    }
    {
        declaration_block block;
        REQUIRE_NOTHROW(parse(R"({ position: inherit })", block));
        REQUIRE(block.size() == 1);
        auto cascaded_position = block.get<style_id::position>();
        REQUIRE(std::holds_alternative<cascade>(cascaded_position));
        REQUIRE(std::get<cascade>(cascaded_position) == cascade::inherit);
    }
}

}
