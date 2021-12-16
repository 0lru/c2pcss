#include <catch2/catch.hpp>

#include <css/tokenize.h>

namespace css::test {

TEST_CASE("can tokenize double quoted string", "[tokenize]")
{
    auto input = std::string(R"("")");
    auto token_stream = tokenize(input);
    auto token_types = flatten_by_type(token_stream);
    REQUIRE(token_types == std::vector<token_type> { token_type::quoted_string });
}

TEST_CASE("can tokenize color hash color", "[tokenize]")
{
    auto input = std::string(R"(#112233)");
    decltype(tokenize(input)) token_stream;
    REQUIRE_NOTHROW(token_stream = tokenize(input));
    auto token_types = flatten_by_type(token_stream);
    REQUIRE(token_types == std::vector<token_type> { token_type::hash });
}

TEST_CASE("can tokenize hash with escape", "[tokenize]")
{
    auto input = std::string(R"(#11\22 33)");
    decltype(tokenize(input)) token_stream;
    REQUIRE_NOTHROW(token_stream = tokenize(input));
    auto token_types = flatten_by_type(token_stream);
    REQUIRE(token_types == std::vector<token_type> { token_type::hash });
}

TEST_CASE("can parse all kind of deli tokens", "[tokenize]")
{
    auto input = std::string(R"((){}[],:)");
    decltype(tokenize(input)) token_stream;
    REQUIRE_NOTHROW(token_stream = tokenize(input));
    auto token_types = flatten_by_type(token_stream);
    REQUIRE(token_types == std::vector<token_type> {
                token_type::round_brackets_left,
                token_type::round_brackets_right,
                token_type::curly_brackets_left,
                token_type::curly_brackets_right,
                token_type::square_brackets_left,
                token_type::square_brackets_right,
                token_type::comma,
                token_type::colon,
            });
}

TEST_CASE("can tokenize numbers with leading digit", "[tokenize]")
{
    auto input = std::string(R"(0 1 2 3 4 5 6 7 8 9)");
    std::vector<token_type> expectation;
    decltype(tokenize(input)) token_stream;
    REQUIRE_NOTHROW(token_stream = tokenize(input));
    auto token_types = flatten_by_type(token_stream);
    for (auto c : input)
        expectation.push_back(std::isdigit(c) ? token_type::number : token_type::whitespace);
    REQUIRE(token_types == expectation);
}

TEST_CASE("can tokenize plus deli and number starting with plus", "[tokenize]")
{
    auto input = std::string(R"(+ +123)");
    std::vector<token_type> expectation;
    decltype(tokenize(input)) token_stream;
    REQUIRE_NOTHROW(token_stream = tokenize(input));
    auto token_types = flatten_by_type(token_stream);
    REQUIRE(token_types == token_type_stream { token_type::delimiter, token_type::whitespace, token_type::number });
}

TEST_CASE("can differentiate number with minus, cdc and minus delimiter", "[tokenize]")
{
    auto input = std::string(R"(- -123 -->)");
    auto token_stream = tokenize(input);
    REQUIRE_NOTHROW(token_stream = tokenize(input));
    auto token_types = flatten_by_type(token_stream);
    REQUIRE(token_types == token_type_stream { 
        token_type::delimiter,
        token_type::whitespace, 
        token_type::number,
        token_type::whitespace, 
        token_type::cdc
        });
}

TEST_CASE("can differentiate number with full stop and full stop delimiter", "[tokenize]")
{
    auto input = std::string(R"(.123e3 .)");
    auto token_stream = tokenize(input);
    REQUIRE_NOTHROW(token_stream = tokenize(input));
    auto token_types = flatten_by_type(token_stream);
    REQUIRE(token_types == token_type_stream { 
        token_type::number,
        token_type::whitespace, 
        token_type::delimiter
        });
}

TEST_CASE("can differentiate less than sign and cdo", "[tokenize]")
{
    auto input = std::string(R"(< <!--)");
    auto token_stream = tokenize(input);
    REQUIRE_NOTHROW(token_stream = tokenize(input));
    auto token_types = flatten_by_type(token_stream);
    REQUIRE(token_types == token_type_stream { 
        token_type::delimiter,
        token_type::whitespace, 
        token_type::cdo
        });
}

TEST_CASE("can parse at keyword", "[tokenize]")
{
    auto input = std::string(R"(@ @--qweasd)");
    auto token_stream = tokenize(input);
    REQUIRE_NOTHROW(token_stream = tokenize(input));
    auto token_types = flatten_by_type(token_stream);
    REQUIRE(token_types == token_type_stream { 
        token_type::delimiter,
        token_type::whitespace, 
        token_type::at_keyword
        });
}

TEST_CASE("can parse idents inbetween", "[tokenize]")
{
    auto input = std::string(R"(@ --qweasd <)");
    auto token_stream = tokenize(input);
    REQUIRE_NOTHROW(token_stream = tokenize(input));
    auto token_types = flatten_by_type(token_stream);
    REQUIRE(token_types == token_type_stream { 
        token_type::delimiter,
        token_type::whitespace, 
        token_type::ident,
        token_type::whitespace, 
        token_type::delimiter 
        });
}

}
