#pragma once

#include "error.h"
#include <css/tokenizer/token_stream.h>

namespace css::parser {

class input {
public:
    input(token_stream& stream)
        : _stream(stream)
        , _pos(stream.begin()) {};

    template <typename... Args>
    bool match_any_of(token_type token_type, Args&&... args)
    {
        if (_pos == _stream.end())
            return false;
        return token_type == _pos->type || match_any_of(std::forward<Args>(args)...);
    }

    template <typename... Args>
    bool match_any_of(utf8_t delimiter, Args&&... args)
    {
        if (_pos == _stream.end())
            return false;
        return delimiter == *_pos->begin || match_any_of(std::forward<Args>(args)...);
    }

    bool match_any_of(utf8_t delimiter)
    {
        if (_pos == _stream.end())
            return false;
        return delimiter == *_pos->begin;
    }

    bool match_any_of(token_type token_type)
    {
        if (_pos == _stream.end())
            return false;
        return token_type == _pos->type;
    }

    void expect(token_type token_type)
    {
        if (_pos == _stream.end() && token_type != token_type::eof)
            throw error(_stream.line(), _stream.column(), "expected: " + to_string(token_type) + " got: eof");
        if (_pos->type != token_type)
            throw error(_pos->line, _pos->column, "expected: " + to_string(token_type) + " got: " + to_string(_pos->type));
    }

    //
    // per default, white space is skipped. a lexeme can be (only)
    // be parsed by setting this flag to false explicitely
    token const& consume(token_type token_type, bool skip_trailing_whitespace = true)
    {
        if (_pos->type != token_type)
            throw error(_pos->line, _pos->column, "expected: " + to_string(token_type) + " got: " + to_string(_pos->type));
        token const& token = *_pos;
        ++_pos;
        if (skip_trailing_whitespace)
            skip_whitespace();
        return token;
    }

    void skip_whitespace()
    {
        while (_pos != _stream.end() && _pos->type == token_type::whitespace)
            ++_pos;
    }

private:
    token_stream& _stream;
    token_stream::iterator _pos;
};

}
