#include "tokenize.h"
#include <iostream>
#include <numeric>
#include <regex>
#include <sstream>
#include <unordered_map>

namespace css {

namespace detail {

    auto escape_char = '\\';

    //
    // we assume that \r\n is replaced by \n
    namespace expression {

        //
        // we assume ascii in non quoted areas
        auto const non_ascii = string(R"([^\x00-\x7F])");
        //
        // should work with utf8?
        auto const escape = string(R"(\\([0-9a-zA-Z]{1,6}\s?|[^\n[0-9a-zA-Z]))");
        auto const escape_with_newline = string(R"(\\([0-9a-zA-Z]{1,6}\s?|[^[0-9a-zA-Z]))");
        auto const quoted_string = string(R"("(?:[^"\n\\]|)" + escape_with_newline + R"()*")");
        auto const comment = string(R"(\/\*([^*]|[\r\n]|(\*+([^*\/]|[\r\n])))*\*+\/)");
        auto const number = string(R"([-+]?([0-9]+(\.[0-9]+)?|\.[0-9]+)([eE][-+]?[0-9]+)?)");
        auto const url = string(R"(['"]?[^\\\s"'\)\(]*["']?)");

    }

    pos escape(pos const it, pos const end)
    {
        static auto const e = std::regex(string("^") + expression::escape);
        std::cmatch m;
        return std::regex_search(it, m, e) ? it + m[0].length() : it;
    }

    pos escape_with_newline(pos const it, pos const end)
    {
        static auto const e = std::regex(string("^") + expression::escape_with_newline);
        std::cmatch m;
        return std::regex_search(it, m, e) ? it + m[0].length() : it;
    }

    namespace {

        bool is_non_ascii(code_point c) { return c >= 0x7F; }

        pos ident_code_point(pos begin, pos end)
        {
            if (begin == end)
                return begin;
            if (is_non_ascii(*begin) || *begin == '_' || *begin == '-' || std::isalnum(*begin))
                return begin + 1;
            if (auto temp = detail::escape(begin, end); temp != begin)
                return temp;
            return begin;
        }

    }
    pos ident(pos const begin, pos const end)
    {
        //
        // cp1: optional '-'
        auto it = begin;
        if (*it == '-') {
            ++it;
            if (it == end)
                return begin;
        }
        //
        // cp2: digit is not allowed
        if (std::isdigit(*it))
            return begin;
        if (auto temp = ident_code_point(it, end); temp != it) {
            it = temp;
        } else {
            return begin;
        }
        //
        // tail: is optional
        auto temp = ident_code_point(it, end);
        while (temp != it) {
            it = temp;
            temp = ident_code_point(it, end);
        }
        return it;
    }

    pos quoted_string(pos const it, pos const end)
    {
        static auto const e = std::regex("^" + expression::quoted_string);
        std::cmatch m;
        return std::regex_search(it, m, e) ? it + m[0].length() : it;
    }

    pos comment(pos const it, pos const end)
    {
        static auto const e = std::regex("^" + expression::comment);
        std::cmatch m;
        return std::regex_search(it, m, e) ? it + m[0].length() : it;
    }

    pos number(pos const it, pos const end)
    {
        static auto const e = std::regex("^" + expression::number);
        std::cmatch m;
        return std::regex_search(it, m, e) ? it + m[0].length() : it;
    }

    pos url(pos const it, pos const end)
    {
        static auto const e = std::regex("^" + expression::url);
        std::cmatch m;
        return std::regex_search(it, m, e) ? it + m[0].length() : it;
    }

    int look_ahead_and_compare(code_point const* const points, int size, pos const begin, pos const end)
    {
        auto remaining = static_cast<int>(end - begin);
        if (remaining < size)
            return remaining - size;
        return std::strncmp(points, begin, size);
    }

}

using tokenizer = pos (*)(token_stream&, pos const, pos const);

pos tokenize_string(token_stream& stream, pos const begin, pos const end)
{
    if (auto temp = detail::quoted_string(begin, end); temp != begin) {
        stream.push(token_type::quoted_string, begin, temp);
        return temp;
    }
    return begin;
}

pos tokenize_number_sign(token_stream& stream, pos const begin, pos const end)
{
    auto it = begin + 1;
    if (auto temp = detail::escape(it, end); it != end && (temp != it || std::isalnum(*it) || *it == '_' || *it == '-')) {
        if (temp != it)
            it = temp;
        else
            ++it;
        while (it != end) {
            if (auto temp = detail::escape(it, end); temp != it)
                it = temp;
            else if (std::isalnum(*it) || *it == '_' || *it == '-')
                ++it;
            else
                break;
        }
        stream.push(token_type::hash, begin, it);
    } else {
        stream.push(token_type::delimiter, begin, it);
    }
    return it;
}

template <token_type t>
pos tokenize_delimiter(token_stream& stream, pos const begin, pos const)
{
    stream.push(t, begin, begin + 1);
    return begin + 1;
}

pos tokenize_number(token_stream& stream, pos const begin, pos const end)
{
    if (auto temp = detail::number(begin, end); temp != begin) {
        stream.push(token_type::number, begin, temp);
        return temp;
    }
    return begin;
}

pos tokenize_whitespace(token_stream& stream, pos const begin, pos const end)
{
    auto it = begin + 1;
    while (it != end && std::isspace(*it))
        ++it;
    stream.push(token_type::whitespace, begin, it);
    return it;
}

pos tokenize_plus_sign(token_stream& stream, pos const begin, pos const end)
{
    auto it = begin + 1;
    if (std::isdigit(*it)) {
        if (auto temp = detail::number(begin, end); temp != begin) {
            stream.push(token_type::number, begin, temp);
            return temp;
        }
    }
    stream.push(token_type::delimiter, begin, it);
    return it;
}

pos tokenize_minus_sign(token_stream& stream, pos const begin, pos const end)
{
    auto it = begin + 1;
    //
    // first '-' already parsed..
    if (detail::look_ahead_and_compare("->", 2, it, end) == 0) {
        stream.push(token_type::cdc, begin, begin + 3);
        return begin + 3;
    }
    //
    // number.. parse from begin
    else if (std::isdigit(*it)) {
        if (auto temp = detail::number(begin, end); temp != begin) {
            stream.push(token_type::number, begin, temp);
            return temp;
        }
    } else if (auto temp = detail::ident(begin, end); temp != begin) {
        stream.push(token_type::ident, begin, temp);
        return temp;
    }
    //
    // assume it = begin + 1
    stream.push(token_type::delimiter, begin, it);
    return it;
}

pos tokenize_full_stop(token_stream& stream, pos const begin, pos const end)
{
    auto it = begin + 1;
    if (std::isdigit(*it)) {
        if (auto temp = detail::number(begin, end); temp != begin) {
            stream.push(token_type::number, begin, temp);
            return temp;
        }
    }
    stream.push(token_type::delimiter, begin, it);
    return it;
}

pos tokenize_less_than_sign(token_stream& stream, pos const begin, pos const end)
{
    auto it = begin + 1;
    //
    // '<' already parsed..
    if (detail::look_ahead_and_compare("!--", 3, it, end) == 0) {
        stream.push(token_type::cdo, begin, it);
        return begin + 4;
    } else {
        stream.push(token_type::delimiter, begin, it);
        return it;
    }
}

pos tokenize_commercial_at(token_stream& stream, pos const begin, pos const end)
{
    auto it = begin + 1;
    if (auto temp = detail::ident(it, end); temp != it) {
        stream.push(token_type::at_keyword, begin, temp);
        return temp;
    }
    stream.push(token_type::delimiter, begin, it);
    return it;
}

auto parsing_strategies = std::unordered_map<code_point, tokenizer> {
    { '\'', tokenize_string },
    { '"', tokenize_string },
    { '#', tokenize_number_sign },
    { '0', tokenize_number },
    { '1', tokenize_number },
    { '2', tokenize_number },
    { '3', tokenize_number },
    { '4', tokenize_number },
    { '5', tokenize_number },
    { '6', tokenize_number },
    { '7', tokenize_number },
    { '8', tokenize_number },
    { '9', tokenize_number },
    { '+', tokenize_plus_sign },
    { '-', tokenize_minus_sign },
    { '.', tokenize_full_stop },
    { '<', tokenize_less_than_sign },
    { '>', tokenize_delimiter<token_type::delimiter> },
    { '@', tokenize_commercial_at },
    { ' ', tokenize_whitespace },
    { '\f', tokenize_whitespace },
    { '\r', tokenize_whitespace },
    { '\n', tokenize_whitespace },
    { '\v', tokenize_whitespace }, // not listed, but added..
    { '(', tokenize_delimiter<token_type::delimiter> },
    { ')', tokenize_delimiter<token_type::delimiter> },
    { '{', tokenize_delimiter<token_type::delimiter> },
    { '}', tokenize_delimiter<token_type::delimiter> },
    { '[', tokenize_delimiter<token_type::delimiter> },
    { ']', tokenize_delimiter<token_type::delimiter> },
    { ',', tokenize_delimiter<token_type::delimiter> },
    { ':', tokenize_delimiter<token_type::delimiter> },
    { ';', tokenize_delimiter<token_type::delimiter> },
};

namespace {

    auto tokenizer_lookup_table = []() {
        auto lut = std::vector<tokenizer>(256, nullptr);
        for (auto& [c, s] : parsing_strategies)
            lut[c] = s;
        return lut;
    }();

}

token_stream tokenize(pos begin, pos end)
{
    token_stream stream;
    auto it = begin;
    while (it != end) {
        if (*it < 256 && *it >= 0) {
            if (auto strategy = tokenizer_lookup_table[*it]; strategy != nullptr) {
                if (auto temp = strategy(stream, it, end); temp != it) {
                    it = temp;
                    continue;
                }
            }
        }
        if (auto temp = detail::ident(it, end); temp != it) {
            stream.push(token_type::ident, it, temp);
            it = temp;
            continue;
        }
        auto line = std::count_if(begin, it, [](auto c) { return c == '\n'; }) + 1;
        auto line_start = string(begin, it - begin - 1).rfind('\n');
        auto column = line_start == string::npos ? it - begin : (it - begin) - line_start;
        throw tokenize_error(line, column,
            "line " + std::to_string(line) + ", col " + std::to_string(column) + ": failed to parse symbol:" + string(it, it + 1));
    }
    return stream;
}

token_stream tokenize(string const& s)
{
    return tokenize(s.data(), &s[s.size()]);
}

token_type_stream flatten_by_type(token_stream const& stream)
{
    auto transformed = token_type_stream(stream.size());
    std::transform(stream.begin(), stream.end(), transformed.begin(),
        [](auto const& token) { return token.type; });
    return transformed;
}

token_content_stream flatten_by_content(token_stream const& stream)
{
    auto transformed = token_content_stream(stream.size());
    std::transform(stream.begin(), stream.end(), transformed.begin(),
        [](auto const& token) { return token.string(); });
    return transformed;
}

std::vector<string> to_string(token_type_stream const& type_stream)
{
    auto string_stream = std::vector<string>(type_stream.size());
    std::transform(type_stream.begin(), type_stream.end(), string_stream.begin(),
        [](auto const token_type) { return to_string(token_type); });
    return string_stream;
}

void dump(std::ostream& stream, token_type_stream type_stream)
{
    stream << std::endl;
    for (auto& s : to_string(type_stream))
        stream << s << std::endl;
    stream << std::endl;
}

string recover_input(token_stream const& stream)
{
    auto size = std::accumulate(stream.begin(), stream.end(), std::size_t(0), [](auto value, auto& token) {
        return value + token.size();
    });
    string target;
    target.resize(size);
    std::size_t offset = 0;
    auto dst = target.begin();
    for (auto& token : stream) {
        offset += token.size();
        std::copy(token.begin, token.end, dst);
        std::advance(dst, token.size());
        //
        // writes '\0' at the end !?..
        // target.replace(offset, token.size(), token.begin, token.size());
    }
    return target;
}

}
