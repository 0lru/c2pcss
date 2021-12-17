#include "tokenizer/tokenize.h"
#include "parser/context.h"
#include "model/model.h"

#include <iostream>

namespace css {

template <typename T>
void parse(string const& input, T& value)
{
    auto stream = tokenize(input);
    parser::context context(stream);
    parser::parser<T>::parse(context, value);
}

}