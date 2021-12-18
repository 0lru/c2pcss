#include "context.h"
#include "parser.h"

namespace css::parser {

bool parser<px>::parse(context& context, px& px)
{
    if (context.peek().string_view() != "px") {
        context.make_error("expected 'px', got '{}'", context.peek().string());
        return false;
    }
    context.consume(skip_trailing_whitespace);
    return true;
}

bool parser<em>::parse(context& context, em& px)
{
    if (context.peek().string_view() != "em") {
        context.make_error("expected 'em', got '{}'", context.peek().string());
        return false;
    }
    context.consume(skip_trailing_whitespace);
    return true;
}

bool parser<rem>::parse(context& context, rem& rem)
{
    if (context.peek().string_view() != "em") {
        context.make_error("expected 'em', got '{}'", context.peek().string());
        return false;
    }
    context.consume(skip_trailing_whitespace);
    return true;
}

bool parser<length>::parse(context& context, length& length)
{
    return false;
}

}
