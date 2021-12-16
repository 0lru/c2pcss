#pragma once

#include "token_type.h"

#include <algorithm>
#include <charconv>
#include <cstdint>
#include <istream>
#include <stdexcept>
#include <string_view>
#include <vector>

namespace css {

using pos = char const*;

class tokenize_error : std::runtime_error {
public:
    tokenize_error(std::string const& what)
        : std::runtime_error(what)
    {
    }
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

token_stream tokenize(pos start, pos end);
token_stream tokenize(std::string const&);

using token_type_stream = std::vector<token_type>;
using token_content_stream = std::vector<std::string>;

token_type_stream flatten_by_type(token_stream const&);
token_content_stream flatten_by_content(token_stream const&);
std::vector<std::string> to_string(token_type_stream const&);
void dump(std::ostream&, token_type_stream);

namespace detail {

    pos escape(pos const, pos const);
    pos escape_with_newline(pos const, pos const);
    pos ident(pos const, pos const);
    pos quoted_string(pos const, pos const);
    pos comment(pos const, pos const);
    pos number(pos const, pos const);
    pos url(pos const, pos const);

}

}
