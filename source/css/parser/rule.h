#include "token_stream_iterator.h"

#include <css/model/model.h>

namespace css {

//
// this is template. with this, one can apply the rule by model type (see parse.h)
template <typename T, typename = void>
struct rule {
    static void apply_to(token_stream_reader&, T&);
};

}
