#include "context.h"
#include "parser.h"

namespace css::parser {

/*    bool parser<declaration_block>::parse(context& context, declartion_block& block)
    {
        context.demand('{');

        if (context.peek().string_view() != "px") {
            context.make_error("expected 'px', got '{}'", context.peek().string());
            return false;
        }
        context.consume(skip_trailing_whitespace);
        return true;
    } */

}