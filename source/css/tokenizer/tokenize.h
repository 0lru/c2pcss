#pragma once

#include "tokenize_error.h"
#include "token_stream.h"

namespace css {

namespace detail {

    pos escape(pos const, pos const);
    pos escape_with_newline(pos const, pos const);
    pos ident(pos const, pos const);
    pos quoted_string(pos const, pos const);
    pos comment(pos const, pos const);
    pos number(pos const, pos const);
    pos url(pos const, pos const);

}

token_stream tokenize(pos start, pos end);
token_stream tokenize(std::string const&);

using token_type_stream = std::vector<token_type>;
using token_content_stream = std::vector<std::string>;

token_type_stream flatten_by_type(token_stream const&);
token_content_stream flatten_by_content(token_stream const&);
std::vector<std::string> to_string(token_type_stream const&);
void dump(std::ostream&, token_type_stream);
std::string recover_input(token_stream const&);

}
