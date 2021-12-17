#pragma once

#include "token.h"

namespace css {

struct token_stream {
public:
    using iterator = std::vector<token>::iterator;
    using const_iterator = std::vector<token>::const_iterator;

    token_stream();
    token_stream(token_stream&&) = default;
    token_stream(token_stream const&) = delete;
    token_stream& operator=(token_stream&&) = default;
    token_stream& operator=(token_stream const&) = delete;

    iterator begin() { return _tokens.begin(); }
    iterator end() { return _tokens.end(); }

    const_iterator begin() const { return _tokens.begin(); }
    const_iterator end() const { return _tokens.end(); }

    std::size_t size() const { return _tokens.size(); }
    std::size_t code_point_count() const { return _code_point_count; }

    void push(token_type type, pos begin, pos end);

    std::size_t line() const { return _line; }
    std::size_t column() const { return _column; }

private:
    std::size_t _line;
    std::size_t _column;
    std::size_t _code_point_count = 0;
    std::vector<token> _tokens;
};

}
