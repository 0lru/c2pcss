#include "parser.h"

namespace css::parser {

void parser<rule_set>::parse(input& iterator, rule_set& rule_set)
{
    parser<selector_list>::parse(iterator, rule_set.selector_list);
}

}
