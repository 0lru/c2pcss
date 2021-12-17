#include <catch2/catch.hpp>

#include <css/tokenizer/tokenize.h>

namespace css::test {

namespace {
    auto xy = R"()";
}

TEST_CASE("can parse empty double quoted string", "[tokenize][detail]")
{
    auto input = std::string(R"("")");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::quoted_string(begin, end) == end);
}

TEST_CASE("can parse double quoted string with escaped quotes", "[tokenize][detail]")
{
    auto input = std::string(R"("\"")");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::quoted_string(begin, end) == end);
}

TEST_CASE("can escape newline in double quoted string", "[tokenize][detail]")
{
    auto input = std::string("\"\\\n\"");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::quoted_string(begin, end) == end);
}

}