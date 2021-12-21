#pragma once

#include "error.h"
#include "parser.h"
#include "warning.h"

#include <css/tokenizer/token_stream.h>

#include <fmt/core.h>

namespace css::parser {

class context {
public:
    context(token_stream& stream)
        : _stream(stream)
        , _pos(stream.begin()) {};

    // look ahead..
    template <typename... Args>
    bool match(token_type token_type, Args&&... args) const
    {
        if (_pos == _stream.end())
            return false;
        return token_type == _pos->type || match(std::forward<Args>(args)...);
    }

    template <typename... Args>
    bool match(utf8_t delimiter, Args&&... args) const
    {
        if (_pos == _stream.end())
            return false;
        return delimiter == *_pos->begin || match(std::forward<Args>(args)...);
    }

    bool match(utf8_t delimiter) const
    {
        if (_pos == _stream.end())
            return false;
        return delimiter == *_pos->begin;
    }

    bool match(token_type token_type) const
    {
        if (_pos == _stream.end())
            return false;
        return token_type == _pos->type;
    }

    token const& peek() const { return *_pos; }

    //
    // per default, white space is skipped. a lexeme can be (only)
    // be parsed by setting this flag to false explicitely
    void consume(consumer::consumption_tactics consumption_tactic)
    {
        token const& token = *_pos;
        ++_pos;
        if (consumption_tactic == consumer::consumption_tactics::skip_trailing_whitespace)
            skip_whitespace();
    }

    template <typename... Args>
    void make_error(char const* what, Args&&... args)
    {
        _errors.push_back(error(*_pos, fmt::format(what, std::forward<Args>(args)...)));
    }

    //
    // demands that the current token is of type token_type. in case that
    // this is not true, an error generated at the current line and position.
    bool demand(token_type token_type)
    {
        if (_pos->type != token_type) {
            make_error("syntax error: expected identifier '{}', got '{}'",
                to_string(_pos->type), to_string(token_type));
            return false;
        }
        return true;
    }

    //
    // delimiter version
    bool demand(char delimiter)
    {
        if (_pos->type != token_type::delimiter) {
            make_error("syntax error: expected delimiter token, got '{}'",
                to_string(_pos->type));
            return false;
        }
        if (_pos->string_view()[0] != delimiter) {
            make_error("syntax error: expected '{}' token, got '{}'",
                delimiter, _pos->string_view());
            return false;
        }
        return true;
    }

    bool consume(char delimiter, consumer::consumption_tactics consumption_tactics)
    {
        auto success = demand(delimiter);
        consume(consumption_tactics);
        return success;
    }

    void skip_whitespace()
    {
        while (_pos != _stream.end() && _pos->type == token_type::whitespace)
            ++_pos;
    }

private:
    token_stream& _stream;
    token_stream::iterator _pos;
    std::vector<error> _errors;
};

}
