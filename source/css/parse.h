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

template<typename T>
T parse(std::string const& input)
{
    T value;
    auto stream = tokenize(input);
    parser::context context(stream);
    if (!parser::parser<T>::parse(context, value))
        // TODO: custom exception with context included..
        std::runtime_error("failed to parse value");
    return value;
}

}