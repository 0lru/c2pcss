#include "parser.h"

namespace css {

token_iterator rule<color, void>::parse(token_iterator begin, token_iterator end, color& out)
{
    if (begin->type == token::hash) {
        auto it = begin + 1;
        if (it == end)
            return begin;
        if (it->type != token::sequence && it->type != token::numeric)
            return begin;
        if (!it->all_of(isxdigit))
            return begin;
        out = color();
        std::uint32_t x;
        it->parse_integer(x, 16);
        switch (it->size())
        {
        case 6:
            x = (x << 8) | 0xff;
            break;
        case 8:
            break;
        case 3:
            x =   ((x & 0xf00) << 20) 
                | ((x & 0xf00) << 16) 
                | ((x & 0x0f0) << 16)
                | ((x & 0x0f0) << 12)
                | ((x & 0x00f) << 12)
                | ((x & 0x00f) << 8 )  
                | 0xff;
            break;
        default:
            return begin;
        };
        out = x;
        return it + 1;
    }
    return begin;
}

}