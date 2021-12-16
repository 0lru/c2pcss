#pragma once

#include <algorithm>
#include <charconv>
#include <cstdint>
#include <istream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace css {

using pos = char const*;

class lex_error : std::runtime_error {
public:
    lex_error(std::string const& what)
        : std::runtime_error(what)
    {
    }
};

enum class token_type {
    // 1:1 of https://drafts.csswg.org/css-syntax
    ident,
    function,
    at_keyword,
    hash,
    string,
    bad_string,
    url,
    bad_url,
    delim,
    number,
    percentage,
    dimension,
    whitespace,
    cdo,
    cdc,
    colon,
    semicolon,
    comma,
    minus,
    square_brackets_left,
    square_brackets_right,
    round_brackets_left,
    round_brackets_right,
    curly_brackets_left,
    curly_brackets_right
};

struct token {

    pos begin;
    pos end;
    token_type type;

    // number of points
    std ::size_t size() const { return end - begin; }

    // make string
    std::string string() const { return std::string(begin, end); }

    // make string view
    std::string_view string_view() const { return std::string_view(begin, end - begin); }

    // parse number
    template <typename T>
    void parse(T& value) { std::from_chars(begin, end, value); }

    // parse number
    template <typename T>
    void parse(T& value, int const base) { std::from_chars(begin, end, value, base); }

    // check if all points are of ..
    template <typename T>
    bool all_of(T&& t) { return std::all_of(begin, end, std::forward<T>(t)); }
};

using token_stream = std::vector<token>;
using token_iterator = token_stream::iterator;

token_stream lex(pos start, pos end);
token_stream lex(std::string const&);

std::vector<token_type> flatten(token_stream const&);

}
