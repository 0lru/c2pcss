#include "token_type.h"

#include <unordered_map>
#include <stdexcept>

namespace css {

namespace {

    auto const _string_map_ = std::unordered_map<token_type, std::string> {
        { token_type::none, "none" },
        { token_type::ident, "ident" },
        { token_type::function, "function" },
        { token_type::at_keyword, "at_keyword" },
        { token_type::hash, "hash" },
        { token_type::quoted_string, "quoted_string" },
        { token_type::bad_string, "bad_string" },
        { token_type::url, "url" },
        { token_type::bad_url, "bad_url" },
        { token_type::delimiter, "delimiter" },
        { token_type::number, "number" },
        { token_type::percentage, "percentage" },
        { token_type::dimension, "dimension" },
        { token_type::whitespace, "whitespace" },
        { token_type::cdo, "cdo" },
        { token_type::cdc, "cdc" },
        { token_type::colon, "colon" },
        { token_type::semicolon, "semicolon" },
        { token_type::comma, "comma" },
        { token_type::minus, "minus" },
        { token_type::square_brackets_left, "square_brackets_left" },
        { token_type::square_brackets_right, "square_brackets_right" },
        { token_type::round_brackets_left, "round_brackets_left" },
        { token_type::round_brackets_right, "round_brackets_right" },
        { token_type::curly_brackets_left, "curly_brackets_left" },
        { token_type::curly_brackets_right, "curly_brackets_right" }
    };
}

std::string const& to_string(token_type const token_type)
{
    auto it = _string_map_.find(token_type);
    if (it == _string_map_.end())
        throw std::invalid_argument("unknown token tyoe");
    return it->second;
}

}
