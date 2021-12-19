#include <catch2/catch.hpp>
#include <css/model/model.h>
#include <css/parse.h>

namespace css::test {

TEST_CASE("can parse direction", "[parser][style]")
{
    REQUIRE(parse<direction>("ltr") == direction::ltr);
    REQUIRE(parse<direction>("rtl") == direction::rtl);
}

TEST_CASE("can parse direction inside declaration block", "[parser][style]")
{
    declaration_block block;
    REQUIRE_NOTHROW(parse(R"({ direction: ltr })", block));
    REQUIRE(block.size() == 1);
    auto cascaded = block.get<style_id::direction>();
    REQUIRE(std::holds_alternative<direction>(cascaded));
    REQUIRE(std::get<direction>(cascaded) == direction::ltr);
}

}