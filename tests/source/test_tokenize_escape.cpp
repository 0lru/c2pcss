#include <catch2/catch.hpp>

#include <css/tokenize.h>

namespace css::test {

TEST_CASE("can parse escape character with 6 hex digits", "[detail][escape]")
{
    auto input = std::string(R"(\abcdef)");
    REQUIRE_NOTHROW(detail::escape(input.data(), input.data()+input.size()));
    REQUIRE(detail::escape(input.data(), input.data()+input.size()) == input.data()+input.size());
}

TEST_CASE("can parse escape character with 4 hex digits", "[detail][escape]")
{
    auto input = std::string(R"(\0abc)");
    REQUIRE_NOTHROW(detail::escape(input.data(), input.data()+input.size()));
    REQUIRE(detail::escape(input.data(), input.data()+input.size()) == input.data()+input.size());
}

TEST_CASE("escaping newline is not allowed in plain escape", "[detail][escape]")
{
    auto input = std::string("\"\\\n\"");
    REQUIRE(detail::escape(input.data(), input.data()+input.size()) == input.data());
}

TEST_CASE("escaping newline allowed", "[detail][escape_with_newline]")
{
    auto input = std::string("\"\\\n\"");
    REQUIRE(detail::escape_with_newline(input.data(), input.data()+input.size()) == input.data());
}

}
