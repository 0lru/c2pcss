#include "color.h"

namespace css {

    /*
            x = ((x & 0xf00) << 20)
                | ((x & 0xf00) << 16)
                | ((x & 0x0f0) << 16)
                | ((x & 0x0f0) << 12)
                | ((x & 0x00f) << 12)
                | ((x & 0x00f) << 8)
                | 0xff;
*/
}