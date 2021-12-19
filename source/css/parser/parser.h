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
    bool check_precondition(context&) const { }
};

template <typename T>
struct parser<T, typename std::enable_if<std::is_enum<T>::value>::type> {
    bool check_precondition(context& context) const
    {
        return context.peek().type == token_type::ident;
    }

    static bool parse(context& context, T& enum_value)
    {
        context.demand(token_type::ident);
        auto const content = context.peek().string();
        if (!enum_table<T>.contains(content))
        {
            context.make_error("unexpected token content: '{}'", content);
            return false;
        }
        enum_value = enum_table<T>[content];
        return true;
    }
};

}