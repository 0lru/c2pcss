#include "tokenize.h"
#include <regex>
#include <sstream>
#include <unordered_map>
namespace css {

using tokenizer = void (*)(token_stream&, pos, pos);

/*auto parsing_strategies = std::unordered_map<char, tokenizer> {
    { '{', token::brace_left }
};

namespace {

    auto lut = []() {
        auto lut = std::vector<token::type_t>(256, token::type_t::none);
        for (auto& [c, type] : lut_definition)
            lut[c] = type;
        return lut;
    }();

}
*/

namespace detail {

    auto escape_char = '\\';

    //
    // we assume that \r\n is replaced by \n. furthermode this uses regex and is not
    // optimized. as an layer of abstraction, the tokenizer does not use them directly
    // and one may can exchange these regex with handcraftet, more performant algorithms
    namespace expression {

        auto const non_ascii = std::string(R"([^\x00-\x7F])");
        auto const escape = std::string(R"((\\[[:xdigit:]]{1,6}\s?|\\[^\n[:xdigit:]]))");
        auto const escape_with_newline = std::string(R"((\\[[:xdigit:]]{1,6}\s?|\\[^[:xdigit:]]))");
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
        return std::regex_match(it, m, e) ? it + m[0].length() : it;
    }

    pos escape_with_newline(pos const it, pos const end)
    {
        static auto const e = std::regex(std::string("^") + expression::escape_with_newline);
        std::cmatch m;
        return std::regex_match(it, m, e) ? it + m[0].length() : it;
    }

    pos ident(pos const it, pos const end)
    {
        static auto const e = std::regex(std::string("^") + expression::ident);
        std::cmatch m;
        return std::regex_match(it, m, e) ? it + m[0].length() : it;
    }

    pos quoted_string(pos const it, pos const end)
    {
        static auto const e = std::regex("^" + expression::quoted_string);
        std::cmatch m;
        return std::regex_match(it, m, e) ? it + m[0].length() : it;
    }

    pos comment(pos const it, pos const end)
    {
        static auto const e = std::regex("^" + expression::comment);
        std::cmatch m;
        return std::regex_match(it, m, e) ? it + m[0].length() : it;
    }

    pos number(pos const it, pos const end)
    {
        static auto const e = std::regex("^" + expression::number);
        std::cmatch m;
        return std::regex_match(it, m, e) ? it + m[0].length() : it;
    }

    pos url(pos const it, pos const end)
    {
        static auto const e = std::regex("^" + expression::url);
        std::cmatch m;
        return std::regex_match(it, m, e) ? it + m[0].length() : it;
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

token_stream tokenize(pos it, pos end)
{
    token_stream tokens;
    tokens.reserve(4096);
    while (it != end) {
        //
        // '/' consume comment, do not emit token
        if (auto temp = detail::comment(it, end); temp != it) {
            it = temp;
            continue;
        }
        throw tokenize_error("unknown symbol, rest ..." + std::string(it, it + 1) + "...");
    }
    return tokens;
}

std::vector<token> tokenize(std::string const& s)
{
    return tokenize(s.data(), &s[s.size()]);
}

std::vector<token_type> flatten(token_stream const& stream)
{
    auto transformed = std::vector<token_type>(stream.size());
    std::transform(stream.begin(), stream.end(), transformed.begin(),
        [](auto const& token) { return token.type; });
    return transformed;
}

}
