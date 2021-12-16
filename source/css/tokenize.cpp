#include "tokenize.h"
#include <iostream>
#include <regex>
#include <sstream>
#include <unordered_map>

namespace css {

namespace detail {

    auto escape_char = '\\';

    //
    // we assume that \r\n is replaced by \n. furthermode this uses regex and is not
    // optimized. as an layer of abstraction, the tokenizer does not use them directly
    // and one may can exchange these regex with handcraftet, more performant algorithms
    namespace expression {

        auto const non_ascii = std::string(R"([^\x00-\x7F])");
        auto const escape = std::string(R"(\\([0-9a-fA-F]{1,6}\s?|[^\n[0-9a-fA-F]))");
        auto const escape_with_newline = std::string(R"(\\([0-9a-fA-F]{1,6}\s?|[^[0-9a-fA-F]))");
        auto const ident = std::string()
            + R"((?:--|-?(?:[a-zA-Z])"
            + "|" + escape + "|"
            + non_ascii + R"())(?:[\w_-])"
            + "|" + escape
            + "|" + non_ascii + R"()*)";
        auto const quoted_string = std::string(R"("(?:[^"\n\\]|)" + escape_with_newline + R"()*")");
        auto const comment = std::string(R"(\/\*([^*]|[\r\n]|(\*+([^*\/]|[\r\n])))*\*+\/)");
        auto const number = std::string(R"([-+]?([0-9]+(\.[0-9]+)?|\.[0-9]+)([eE][-+]?[0-9]+)?)");
        auto const url = std::string(R"(['"]?[^\\\s"'\)\(]*["']?)");
    }

    pos escape(pos const it, pos const end)
    {
        static auto const e = std::regex(std::string("^") + expression::escape);
        std::cmatch m;
        return std::regex_search(it, m, e) ? it + m[0].length() : it;
    }

    pos escape_with_newline(pos const it, pos const end)
    {
        static auto const e = std::regex(std::string("^") + expression::escape_with_newline);
        std::cmatch m;
        return std::regex_search(it, m, e) ? it + m[0].length() : it;
    }

    pos ident(pos const it, pos const end)
    {
        static auto const e = std::regex(std::string("^") + expression::ident);
        std::cmatch m;
        return std::regex_search(it, m, e) ? it + m[0].length() : it;
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

    int look_ahead_and_compare(char const* const points, int size, pos const begin, pos const end)
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
        stream.push_back({ begin, temp, token_type::quoted_string });
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
        stream.push_back({ begin, it, token_type::hash });
    } else {
        stream.push_back({ begin, it, token_type::delimiter });
    }
    return it;
}

template <token_type t>
pos tokenize_delimiter(token_stream& stream, pos const begin, pos const)
{
    stream.push_back({ begin, begin + 1, t });
    return begin + 1;
}

pos tokenize_number(token_stream& stream, pos const begin, pos const end)
{
    if (auto temp = detail::number(begin, end); temp != begin) {
        stream.push_back({ begin, temp, token_type::number });
        return temp;
    }
    return begin;
}

pos tokenize_whitespace(token_stream& stream, pos const begin, pos const end)
{
    auto it = begin + 1;
    while (it != end && std::isspace(*it))
        ++it;
    stream.push_back({ begin, it, token_type::whitespace });
    return it;
}

pos tokenize_plus_sign(token_stream& stream, pos const begin, pos const end)
{
    auto it = begin + 1;
    if (std::isdigit(*it)) {
        if (auto temp = detail::number(begin, end); temp != begin) {
            stream.push_back({ begin, temp, token_type::number });
            return temp;
        }
    }
    stream.push_back({ begin, it, token_type::delimiter });
    return it;
}

pos tokenize_minus_sign(token_stream& stream, pos const begin, pos const end)
{
    auto it = begin + 1;
    //
    // first '-' already parsed..
    if (detail::look_ahead_and_compare("->", 2, it, end) == 0) {
        stream.push_back({ begin, begin + 3, token_type::cdc });
        return begin + 3;
    }
    //
    // number.. parse from begin
    else if (std::isdigit(*it)) {
        if (auto temp = detail::number(begin, end); temp != begin) {
            stream.push_back({ begin, temp, token_type::number });
            return temp;
        }
    } else if (auto temp = detail::ident(begin, end); temp != begin) {
        stream.push_back({ begin, temp, token_type::ident });
        return temp;
    }
    //
    // assume it = begin + 1
    stream.push_back({ begin, it, token_type::delimiter });
    return it;
}

pos tokenize_full_stop(token_stream& stream, pos const begin, pos const end)
{
    auto it = begin + 1;
    if (std::isdigit(*it)) {
        if (auto temp = detail::number(begin, end); temp != begin) {
            stream.push_back({ begin, temp, token_type::number });
            return temp;
        }
    }
    stream.push_back({ begin, it, token_type::delimiter });
    return it;
}

pos tokenize_less_than_sign(token_stream& stream, pos const begin, pos const end)
{
    auto it = begin + 1;
    //
    // '<' already parsed..
    if (detail::look_ahead_and_compare("!--", 3, it, end) == 0) {
        stream.push_back({ begin, it, token_type::cdo });
        return begin + 4;
    } else {
        stream.push_back({ begin, it, token_type::delimiter });
        return it;
    }
}

pos tokenize_commercial_at(token_stream& stream, pos const begin, pos const end)
{
    auto it = begin + 1;
    if (auto temp = detail::ident(it, end); temp != it) {
        stream.push_back({ begin, temp, token_type::at_keyword });
        return temp;
    }
    stream.push_back({ begin, it, token_type::delimiter });
    return it;
}

auto parsing_strategies = std::unordered_map<char, tokenizer> {
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
    { '(', tokenize_delimiter<token_type::round_brackets_left> },
    { ')', tokenize_delimiter<token_type::round_brackets_right> },
    { '{', tokenize_delimiter<token_type::curly_brackets_left> },
    { '}', tokenize_delimiter<token_type::curly_brackets_right> },
    { '[', tokenize_delimiter<token_type::square_brackets_left> },
    { ']', tokenize_delimiter<token_type::square_brackets_right> },
    { ',', tokenize_delimiter<token_type::comma> },
    { ':', tokenize_delimiter<token_type::colon> },
    { ';', tokenize_delimiter<token_type::semicolon> },
};

namespace {

    auto strategy_lut = []() {
        auto lut = std::vector<tokenizer>(256, nullptr);
        for (auto& [c, s] : parsing_strategies)
            lut[c] = s;
        return lut;
    }();

}

token_stream tokenize(pos it, pos end)
{
    token_stream token_stream;
    token_stream.reserve(4096);
    while (it != end) {
        if (*it < 256 && *it >= 0) {
            if (auto strategy = strategy_lut[*it]; strategy != nullptr) {
                if (auto temp = strategy(token_stream, it, end); temp != it) {
                    it = temp;
                    continue;
                }
            }
        }
        if (auto temp = detail::ident(it, end); temp != it) {
            token_stream.push_back({ it, temp, token_type::ident });
            it = temp;
            continue;
        }
        throw tokenize_error("unknown symbol, rest ..." + std::string(it, it + 1) + "...");
    }
    return token_stream;
}

std::vector<token> tokenize(std::string const& s)
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

std::vector<std::string> to_string(token_type_stream const& type_stream)
{
    auto string_stream = std::vector<std::string>(type_stream.size());
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

}
