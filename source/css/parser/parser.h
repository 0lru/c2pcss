#pragma once

#include <css/model/model.h>

namespace css::parser {

class context;

struct consumer {
    enum consumption_tactics {
        skip_trailing_whitespace,
        keep_trailing_whitespace
    };
};

//
// this is template for parsers. for each typ in "model.h" there should one.
// a parser may fail. instead of throwing an exception, the parser should report
// the error to the context and return false instead.
template <typename T, typename = void>
struct parser : public consumer {
    static bool parse(context&, T&);
};

}
