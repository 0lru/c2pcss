#include <catch2/catch.hpp>

#include <css/tokenize.h>

namespace css::test {

TEST_CASE("can math double minus", "[tokenize][detail]")
{
    auto input = std::string(R"(--)");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::ident(begin, end)==end);
}

TEST_CASE("single minus must be followed by ident char", "[tokenize][detail]")
{
    auto input = std::string(R"(-0)");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::ident(begin, end)==begin);
}

TEST_CASE("tail can contain lower, minus and word characters", "[tokenize][detail]")
{
    auto input = std::string(R"(--_-aA0)");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::ident(begin, end)==end);
}

TEST_CASE("prefix can contain escape characters", "[tokenize][detail]")
{
    auto input = std::string(R"(-\aa)");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::ident(begin, end)==end);
}

TEST_CASE("suffix can contain escape characters", "[tokenize][detail]")
{
    auto input = std::string(R"(--\bb asd)");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::ident(begin, end)==end);
}

TEST_CASE("test simple ident", "[tokenize][detail]")
{
    auto input = std::string(R"(example {)");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::ident(begin, end)==begin + std::string("example").size());
}

}
