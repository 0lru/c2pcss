#include <catch2/catch.hpp>

#include <css/tokenize.h>
#include <iostream>

namespace {

auto const radom_css_1 = R"(

@keyframes example {
    from {background-color: red;}
    to {background-color: yellow;}
}

div {
    width: 100px;
    height: 100px;
    background-color: red;
    animation-name: example;
    animation-duration: 4s;
})";

}

namespace css::test {

TEST_CASE("tokenize random css 1", "[tokenize][random]")
{
    token_stream token_stream;
    REQUIRE_NOTHROW(token_stream = tokenize(radom_css_1));
    auto token_types = flatten_by_type(token_stream);
    //
    // the list was generated with "dump":
    // dump(std::cout, token_types);
    REQUIRE(token_types == token_type_stream {  
        token_type::whitespace,
        token_type::at_keyword,
        token_type::whitespace,
        token_type::ident,
        token_type::whitespace,
        token_type::curly_brackets_left,
        token_type::whitespace,
        token_type::ident,
        token_type::whitespace,
        token_type::curly_brackets_left,
        token_type::ident,
        token_type::colon,
        token_type::whitespace,
        token_type::ident,
        token_type::semicolon,
        token_type::curly_brackets_right,
        token_type::whitespace,
        token_type::ident,
        token_type::whitespace,
        token_type::curly_brackets_left,
        token_type::ident,
        token_type::colon,
        token_type::whitespace,
        token_type::ident,
        token_type::semicolon,
        token_type::curly_brackets_right,
        token_type::whitespace,
        token_type::curly_brackets_right,
        token_type::whitespace,
        token_type::ident,
        token_type::whitespace,
        token_type::curly_brackets_left,
        token_type::whitespace,
        token_type::ident,
        token_type::colon,
        token_type::whitespace,
        token_type::number,
        token_type::ident,
        token_type::semicolon,
        token_type::whitespace,
        token_type::ident,
        token_type::colon,
        token_type::whitespace,
        token_type::number,
        token_type::ident,
        token_type::semicolon,
        token_type::whitespace,
        token_type::ident,
        token_type::colon,
        token_type::whitespace,
        token_type::ident,
        token_type::semicolon,
        token_type::whitespace,
        token_type::ident,
        token_type::colon,
        token_type::whitespace,
        token_type::ident,
        token_type::semicolon,
        token_type::whitespace,
        token_type::ident,
        token_type::colon,
        token_type::whitespace,
        token_type::number,
        token_type::ident,
        token_type::semicolon,
        token_type::whitespace,
        token_type::curly_brackets_right
    });
}

}
