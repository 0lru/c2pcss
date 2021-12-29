#include <catch2/catch.hpp>
#include <css/model/color.h>
#include <iostream>

namespace css::test {

TEST_CASE("test color component getters", "[color]")
{
    {
        auto red = color("khaki");
        REQUIRE(red.red() == 0xf0);
        REQUIRE(red.green() == 0xe6);
        REQUIRE(red.blue() == 0x8c);
        REQUIRE(red.alpha() == 255);
    }
}

TEST_CASE("can create color from hex", "[color]")
{
    REQUIRE(color(0xf0e68cff) == color("khaki"));
}

TEST_CASE("can create color from hex string", "[color]")
{
    REQUIRE(color("#f0e68cff") == color("khaki"));
}

TEST_CASE("can create color from color components", "[color]")
{
    REQUIRE(color(0xf0, 0xe6, 0x8c, 0xff) == color("khaki"));
}

TEST_CASE("can create from hash, 3 digits", "[color]")
{
    REQUIRE(color(0x11, 0x22, 0x33, 0xff) == color("#123"));
}

TEST_CASE("can create from hash, 6 digits", "[color]")
{
    REQUIRE(color(0x11, 0x22, 0x33, 0xff) == color("#112233"));
}

TEST_CASE("can create from hash, 8 digits", "[color]")
{
    REQUIRE(color(0x33, 0x22, 0x11, 0xab) == color("#332211ab"));
}

}
