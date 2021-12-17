#include "tokenizer/tokenize.h"
#include "parser/parser.h"
#include "model/model.h"

#include <iostream>

namespace css {

template <typename T>
void parse(string const& input, T& value)
{
    auto stream = tokenize(input);
    parser::input iterator(stream);
    parser::parser<T>::parse(iterator, value);
}

}