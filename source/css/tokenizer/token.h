#pragma once

#include "token_type.h"

#include <algorithm>
#include <charconv>
#include <cstdint>
#include <string_view>
#include <vector>

namespace css {

//
// simple typedef to make clear, that our intent is to parse utf8-aware
using utf8_t = char;
using pos = utf8_t const*;
using string = std::string;
// using code_point = std::int16_t.. etc.

struct token {
    token_type type;

    pos begin;
    pos end;

    std::size_t line;
    std::size_t column;

    token(token&&) = default;
    token(token const&) = default;
    token& operator=(token&&) = default;
    token& operator=(token const&) = default;

    // number of points
    std::size_t size() const { return end - begin; }

    // make string
    string string() const { return std::string(begin, end); }

    // make string view
    std::string_view string_view() const { return std::string_view(begin, end - begin); }

    // parse number
    template <typename T>
    void parse(T& value) const { std::from_chars(begin, end, value); }

    // convenience
    template <typename T>
    void cast() const { T value; std::from_chars(begin, end, value); return value; }

    // parse number
    template <typename T>
    void parse(T& value, int const base) const { std::from_chars(begin, end, value, base); }

    // check if all points are of ..
    template <typename T>
    bool all_of(T&& t) const { return std::all_of(begin, end, std::forward<T>(t)); }
};

}
