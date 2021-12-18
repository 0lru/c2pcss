#include "parser.h"
#include "context.h"

#include <iostream>

namespace css::parser {

bool parser<rule_set>::parse(context& context, rule_set& rule_set)
{
    if (!parser<selector_list>::parse(context, rule_set.selector_list))
        return false;
    if (!context.consume('{', skip_trailing_whitespace))
        return false;
    if (!context.consume('}', skip_trailing_whitespace))
        return false;
    return true;
}

}
