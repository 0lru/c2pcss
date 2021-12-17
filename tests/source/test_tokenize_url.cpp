#include <catch2/catch.hpp>
#include <css/tokenizer/tokenize.h>

namespace css::test {

TEST_CASE("can parse url", "[tokenize][detail]")
{
    auto input = std::string(R"(http://mysite.example.com/mycursor.png)");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::url(begin, end) == end);
}

// 
// https://drafts.csswg.org/css-syntax/#typedef-url-token: states that it isn't allowed
// https://developer.mozilla.org/de/docs/Web/CSS/url(): states that it is allowed..
TEST_CASE("can use single quotation around url", "[tokenize][detail]")
{
    auto input = std::string(R"('http://mysite.example.com/mycursor.png')");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::url(begin, end) == end);
}

TEST_CASE("can use double quotation around url", "[tokenize][detail]")
{
    auto input = std::string(R"("http://mysite.example.com/mycursor.png")");
    auto begin = input.data();
    auto end = input.data() + input.size();
    REQUIRE(detail::url(begin, end) == end);
}

}