#pragma once

#include <string>

namespace css {

enum class token_type : std::uint16_t {
    // 1:1 of https://drafts.csswg.org/css-syntax
    none,
    ident,
    function,
    at_keyword,
    hash, // something like #aaa
    quoted_string,
    bad_string, // ?
    url,
    bad_url,
    delimiter,
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

std::string const& to_string(token_type const);

}
