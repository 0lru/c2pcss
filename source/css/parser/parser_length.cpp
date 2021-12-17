#include "context.h"
#include "parser.h"

namespace css::parser {

void parser<px>::parse(context& context, px& px)
{
    if (context.peek().string_view() != "px")
        context.make_error("expected 'px', got '{}'", context.peek().string());
    else
        context.consume(skip_whitespace);
}

void parser<em>::parse(context& context, em& px)
{
    if (context.peek().string_view() != "em")
        context.make_error("expected 'em', got '{}'", context.peek().string());
    else
        context.consume(skip_whitespace);
}

void parser<rem>::parse(context& context, rem& rem)
{
    if (context.peek().string_view() != "em")
        context.make_error("expected 'em', got '{}'", context.peek().string());
    else
        context.consume(skip_whitespace);
}

void parser<length>::parse(context& context, length& length)
{
}

}
