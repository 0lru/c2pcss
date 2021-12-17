#include "tokenizer/tokenize.h"
#include "parser/rule.h"
#include "model/model.h"

#include <iostream>

namespace css {

template <typename T>
void parse(string const& input, T& value)
{
    auto stream = tokenize(input);
    token_stream_reader reader(stream);
    rule<T, void>::apply_to(reader, value);
}

}