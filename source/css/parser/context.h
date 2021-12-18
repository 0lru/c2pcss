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

    template <typename... Args>
    bool match(token_type token_type, Args&&... args)
    {
        if (_pos == _stream.end())
            return false;
        return token_type == _pos->type || match(std::forward<Args>(args)...);
    }

    template <typename... Args>
    bool match(utf8_t delimiter, Args&&... args)
    {
        if (_pos == _stream.end())
            return false;
        return delimiter == *_pos->begin || match(std::forward<Args>(args)...);
    }

    bool match(utf8_t delimiter)
    {
        if (_pos == _stream.end())
            return false;
        return delimiter == *_pos->begin;
    }

    bool match(token_type token_type)
    {
        if (_pos == _stream.end())
            return false;
        return token_type == _pos->type;
    }

    // token& peek() { return *_pos; }
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
