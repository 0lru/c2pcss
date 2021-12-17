#include <catch2/catch.hpp>

#include <css/tokenizer/tokenize.h>
#include <iostream>


auto const some_css_1 = std::string(R"(

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
})");

namespace css::test {

TEST_CASE("tokenize random css 1", "[tokenize][random]")
{
    token_stream token_stream;
    REQUIRE_NOTHROW(token_stream = tokenize(some_css_1));
    auto token_types = flatten_by_type(token_stream);
    //
    // the list was generated with "dump":
    // dump(std::cout, token_types);
    auto expectation = token_type_stream {
        token_type::whitespace,
        token_type::at_keyword,
        token_type::whitespace,
        token_type::ident,
        token_type::whitespace,
        token_type::delimiter,
        token_type::whitespace,
        token_type::ident,
        token_type::whitespace,
        token_type::delimiter,
        token_type::ident,
        token_type::delimiter,
        token_type::whitespace,
        token_type::ident,
        token_type::delimiter,
        token_type::delimiter,
        token_type::whitespace,
        token_type::ident,
        token_type::whitespace,
        token_type::delimiter,
        token_type::ident,
        token_type::delimiter,
        token_type::whitespace,
        token_type::ident,
        token_type::delimiter,
        token_type::delimiter,
        token_type::whitespace,
        token_type::delimiter,
        token_type::whitespace,
        token_type::ident,
        token_type::whitespace,
        token_type::delimiter,
        token_type::whitespace,
        token_type::ident,
        token_type::delimiter,
        token_type::whitespace,
        token_type::number,
        token_type::ident,
        token_type::delimiter,
        token_type::whitespace,
        token_type::ident,
        token_type::delimiter,
        token_type::whitespace,
        token_type::number,
        token_type::ident,
        token_type::delimiter,
        token_type::whitespace,
        token_type::ident,
        token_type::delimiter,
        token_type::whitespace,
        token_type::ident,
        token_type::delimiter,
        token_type::whitespace,
        token_type::ident,
        token_type::delimiter,
        token_type::whitespace,
        token_type::ident,
        token_type::delimiter,
        token_type::whitespace,
        token_type::ident,
        token_type::delimiter,
        token_type::whitespace,
        token_type::number,
        token_type::ident,
        token_type::delimiter,
        token_type::whitespace,
        token_type::delimiter
    };
    REQUIRE(token_types == expectation);
}

TEST_CASE("check data integrity of css 1", "[tokenize][random]")
{
    token_stream token_stream;
    REQUIRE_NOTHROW(token_stream = tokenize(some_css_1));
    std::string recovered = recover_input(token_stream);
    REQUIRE(recovered.size() == some_css_1.size());
    REQUIRE(recovered == some_css_1);
}

}
