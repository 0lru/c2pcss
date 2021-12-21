#pragma once

#include "context.h"

#include <css/model/model.h>

namespace css::parser {

class context;


//
// we define typed parsers. one for each type
template <typename T, typename = void>
struct parser : public consumer {
    static bool parse(context&, T&);
    static bool has_matching_precondition(context&) { }
};

template <typename T>
struct parser<T, typename std::enable_if<std::is_enum<T>::value>::type> : public consumer {
    static bool has_matching_precondition(context& context) 
    {
        if (context.peek().type != token_type::ident)
            return false;
        return enum_table<T>.contains(context.peek().string());
    }

    static bool parse(context& context, T& enum_value)
    {
        context.demand(token_type::ident);
        auto const content = context.peek().string();
        if (!enum_table<T>.contains(content)) {
            context.make_error("unexpected token content: '{}'", content);
            return false;
        }
        enum_value = enum_table<T>[content];
        context.consume(skip_trailing_whitespace);
        return true;
    }
};

template <typename T>
struct parser<cascaded<T>, void> : public consumer {
    static bool has_matching_precondition(context& context) 
    {
        if (context.peek().type != token_type::ident)
            return false;
        auto name = context.peek().string();
        if (enum_table<T>.contains(name))
            return true;
        else if (enum_table<cascade>.contains(name))
            return true;
        return false;
    }

    static bool parse(context& context, cascaded<T>& cascaded)
    {
        context.demand(token_type::ident);

        auto const name = context.peek().string();
        if (enum_table<cascade>.contains(name))
        {
            cascade value;
            if (!parser<cascade>::parse(context, value))
                return false;
            cascaded = value;
            return true;
        }

        T value;
        if(!parser<T>::parse(context, value))
            return false;
        cascaded = value;
        return true;
    }
};

}