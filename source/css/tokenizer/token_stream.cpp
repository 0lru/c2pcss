#include "token_stream.h"

namespace css {

token_stream::token_stream()
{
    _tokens.reserve(4096);
}

void token_stream::push(token_type type, pos begin, pos end)
{
    _tokens.push_back({ type, begin, end, _line, _column });
    _line += std::count_if(begin, end, [](auto c) { return c == '\n'; }) + 1;
    auto line_start = std::string_view(_tokens.begin()->begin, end - _tokens.begin()->begin).rfind('\n');
    auto column = line_start == string::npos ? end - begin : (end - begin) - line_start;
}

}
