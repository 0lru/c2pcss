#include <catch2/catch.hpp>

#include <css/tokenize.h>

namespace css::test {

TEST_CASE("can parse decimal without dot", "[tokenize][detail]")
{
    auto input = std::string(R"(1234)");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::number(begin, end)==end);
}

TEST_CASE("can parse leading dot", "[tokenize][detail]")
{
    auto input = std::string(R"(.1234)");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::number(begin, end)==end);
}

TEST_CASE("number must contain decimal after dot", "[tokenize][detail]")
{
    auto input = std::string(R"(1.)");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::number(begin, end)==begin);
}

TEST_CASE("can use capital e", "[tokenize][detail]")
{
    auto input = std::string(R"(.0E5)");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::number(begin, end)==end);
}

}
