#include <catch2/catch.hpp>

#include <css/tokenize.h>

namespace css::test {

TEST_CASE("can parse empty comment", "[tokenize][detail]")
{
    auto input = std::string(R"(/**/)");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::comment(begin, end)==end);
}

TEST_CASE("can parse star and slash inside comment", "[tokenize][detail]")
{
    auto input = std::string(R"(/* * / **/)");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::comment(begin, end)==end);
}

TEST_CASE("can parse newline in comment", "[tokenize][detail]")
{
    auto input = std::string("/*\n*/");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::comment(begin, end)==end);
}

}
