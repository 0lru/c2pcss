#include <catch2/catch.hpp>

#include <css/tokenizer/tokenize.h>
#include <regex>

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
    auto input = std::string(R"(--_-aAzZ09)");
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

TEST_CASE("ident must not start with non ascii", "[tokenize][detail]")
{
    auto input = std::string(R"($variable)");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::ident(begin, end)==begin);
}

TEST_CASE("single character which is no ident is no ident", "[tokenize][detail]")
{
    auto input = std::string(R"($\nabc)");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::ident(begin, end)==begin);
}

TEST_CASE("test regex", "")
{
//    auto e = std::regex(R"(^(?:--|-?(?:[a-zA-Z]))(?:[0-9a-zA-Z_-])*)");
    auto e = std::regex(R"("^(?:--|-?(?:[a-zA-Z]|\\\\([0-9a-fA-F]{1,6}\\s?|[^\\n[0-9a-fA-F])|[^\\x00-\\x7F]))(?:[0-9a-zA-Z_-]|\\\\([0-9a-fA-F]{1,6}\\s?|[^\\n[0-9a-fA-F])|[^\\x00-\\x7F])*")");
    std::cmatch m;
    bool matched = std::regex_search("$\n abc", m, e);
    REQUIRE(matched == false);
   // (?:--|-?(=:[a-zA-Z]))
    matched = std::regex_search("$\n abc", m, e);
    REQUIRE(matched == false);
}


}
