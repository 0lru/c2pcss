#include <catch2/catch.hpp>
#include <css/model/model.h>
#include <css/parse.h>

namespace css::test {

//
// don't make to_string test, since a test of enum_meta-class is sufficient
TEST_CASE("can parse position", "[parser][selector]")
{
    REQUIRE(parse<position>("absolute") == position::absolute);
    REQUIRE(parse<position>("static") == position::static_);
}

TEST_CASE("can parse position inside declaration block", "[parser][selector]")
{
}


TEST_CASE("test enum table works in both directions", "")
{
    REQUIRE(enum_table<position>.contains("absolute"));
    REQUIRE(enum_table<position>.contains(position::absolute));
    REQUIRE(enum_table<position>["absolute"] == position::absolute);
    REQUIRE(enum_table<position>[position::absolute] == "absolute");
}

}
