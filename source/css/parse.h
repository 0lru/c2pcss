#include "tokenizer/tokenize.h"
#include "parser/context.h"
#include "model/model.h"

#include <iostream>

namespace css {

template <typename T>
bool parse(string const& input, T& value)
{
    auto stream = tokenize(input);
    parser::context context(stream);
    return parser::parser<T>::parse(context, value);
}

}