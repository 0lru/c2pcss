#include "lex.h"
#include <regex>
#include <unordered_map>

namespace css {

namespace detail {

    pos comment(pos input)
    {
        static auto const e = std::regex(R"(\/\*([^*]|[\r\n]|(\*+([^*\/]|[\r\n])))*\*+\/)");
        std::cmatch match;
        if (std::regex_search(input, match, e))
            return match[0].second;
        return input;
    }

}

/*
namespace {

    auto lut_definition = std::unordered_map<char, token::type_t> {
        { '{', token::brace_left },
        { '}', token::brace_right },
        { '(', token::round_bracket_left },
        { ')', token::round_bracket_right },
        { ':', token::colon },
        { ';', token::semicolon },
        { '.', token::point },
        { '#', token::hash },
        { ',', token::comma },
        { '>', token::greater },
        { '<', token::smaller },
        { '+', token::plus },
        { '~', token::tilde },
        { '@', token::alias },
        { '%', token::percentage },
        { '$', token::dollar }, // sass..
        // whitespace
        { ' ', token::whitespace },
        { '\f', token::whitespace },
        { '\n', token::whitespace },
        { '\r', token::whitespace },
        { '\t', token::whitespace },
        { '\v', token::whitespace }
    };

    auto lut = []() {
        auto lut = std::vector<token::type_t>(256, token::type_t::none);
        for (auto& [c, type] : lut_definition)
            lut[c] = type;
        return lut;
    }();

    pos comment(pos input)
    {
        static auto const e = std::regex(R"(\/\*([^*]|[\r\n]|(\*+([^*\/]|[\r\n])))*\*+\/)");
        std::cmatch match;
        if (std::regex_search(input, match, e))
            return match[0].second;
        return input;
    }

    pos sequence(pos input)
    {
        const char* ptr = input;
        while (std::isalpha(static_cast<unsigned char>(*ptr)))
            ++ptr;
        if (ptr == input)
            return input;
        while (*ptr == '_' 
            || *ptr == '-' 
            || std::isalnum(static_cast<unsigned char>(*ptr)))
            ++ptr;
        return ptr;
    }

    pos floating_point(pos input)
    {
        static auto const e = std::regex(R"(^[-+]?([0-9]+(\.[0-9]*)?|\.[0-9]+)([eE][-+]?[0-9]+)?)");
        std::cmatch match;
        if (std::regex_search(input, match, e))
            return match[0].second;
        return input;
    }

}
*/

std::vector<token> css::lex(pos it, pos end)
{
    std::vector<token> tokens;
    tokens.reserve(4096);
    while (it != end) {
        //
        // '/' consume comment, do not emit token
        if (auto temp = detail::comment(it); temp != it) {
            it = temp;
            continue;
        }
        throw lex_error("unknown symbol, rest ..." + std::string(it, it + 1) + "...");
    }
    return tokens;
}

std::vector<token> lex(std::string const& s)
{
    return lex(s.data(), &s[s.size()]);
}

std::vector<token_type> types(token_stream const& stream)
{
    auto transformed = std::vector<token_type>(stream.size());
    std::transform(stream.begin(), stream.end(), transformed.begin(),
        [](auto const& token) { return token.type; });
    return transformed;
}

}
