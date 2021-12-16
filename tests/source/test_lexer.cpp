#include <catch2/catch.hpp>

#include <css/lex.h>

namespace css::lexer::test {

namespace {
    auto xy = R"()";
}

TEST_CASE("consumes comment", "[lexer]")
{
    auto input = R"(/* * / ***** */)";
    std::vector<css::token> ts;
    REQUIRE_NOTHROW(ts = lex(input));
    REQUIRE(ts.empty());
}

/*TEST_CASE("lex random css2 does not throw", "[lexer]")
{
    std::vector<css::token> ts;
    REQUIRE_NOTHROW(ts = lex(css2));
}

TEST_CASE("lex random css1 generates expected tokens", "[lexer]")
{
    auto const ex = std::vector<token::type_t>{
    };
    std::vector<css::token> ts;
    REQUIRE_NOTHROW(ts = lex(css1));
    auto types = css::types(ts);
    REQUIRE(std::vector<token::type_t>(types.begin(), types.begin()+ex.size()) == ex);
}*/

}