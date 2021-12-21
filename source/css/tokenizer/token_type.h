#pragma once

#include <css/model/model.h>
#include <string>

namespace css {

enum token_type : std::uint16_t {
    // 1:1 of https://drafts.csswg.org/css-syntax
    none,
    ident,
    function,
    at_keyword,
    hash, // #ff, #zabc, #ffffffff ...
    delimiter,
    quoted_string,
    bad_string, // ?
    url,
    bad_url,
    number,
    percentage,
    dimension,
    whitespace,
    cdo,
    cdc,
    eof // added
};

std::string const& to_string(token_type const);

}
