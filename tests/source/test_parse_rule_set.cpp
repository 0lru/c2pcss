#include <catch2/catch.hpp>
#include <css/parse.h>

namespace css::test {

TEST_CASE("can parse empty rule set", "[parser][selector]")
{
    rule_set rule_set;
    REQUIRE(parse("* {}", rule_set));
}

}