#include <catch2/catch.hpp>

#include <css/tokenizer/tokenize.h>

auto flawed = std::string("\n\n         \\\n");

namespace css::test {

TEST_CASE("unknown symbol error reports correct line and column", "[tokenize][error]")
{
    auto begin = flawed.data();
    auto end = flawed.data() + flawed.size();
    token_stream token_stream;
    try
    {
        token_stream = tokenize(flawed);
    }
    catch (css::tokenize_error& e)
    {
        REQUIRE(e.line() == 3);
        REQUIRE(e.column() == 10);
    }
}

}
