#include <catch2/catch.hpp>

#include <css/tokenizer/tokenize.h>

namespace css::test {

TEST_CASE("can parse escape character with 6 hex digits", "[tokenize][detail]")
{
    auto input = std::string(R"(\abcdef)");
    REQUIRE_NOTHROW(detail::escape(input.data(), input.data()+input.size()));
    REQUIRE(detail::escape(input.data(), input.data()+input.size()) == input.data()+input.size());
}

TEST_CASE("can parse escape character with 4 hex digits", "[tokenize][detail]")
{
    auto input = std::string(R"(\0abc)");
    REQUIRE_NOTHROW(detail::escape(input.data(), input.data()+input.size()));
    REQUIRE(detail::escape(input.data(), input.data()+input.size()) == input.data()+input.size());
}

TEST_CASE("escaping newline is not allowed in plain escape", "[tokenize][detail]")
{
    auto input = std::string("\"\\\n\"");
    REQUIRE(detail::escape(input.data(), input.data()+input.size()) == input.data());
}

TEST_CASE("escaping newline allowed", "[detail][detail]")
{
    auto input = std::string("\"\\\n\"");
    REQUIRE(detail::escape_with_newline(input.data(), input.data()+input.size()) == input.data());
}

TEST_CASE("escaping with space", "")
{
    auto input = std::string("\\22 33");
    // +4, because space after 22 will be consumed
    REQUIRE(detail::escape(input.data(), input.data()+input.size()) == input.data()+4);
}

}
