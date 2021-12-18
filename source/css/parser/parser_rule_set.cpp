#include "parser.h"

namespace css::parser {

bool parser<rule_set>::parse(context& iterator, rule_set& rule_set)
{
    return parser<selector_list>::parse(iterator, rule_set.selector_list);
}

}
