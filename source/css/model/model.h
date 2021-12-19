#pragma once

#include "collection.h"
#include "style_typedef.h"
#include "style_types.h"

namespace css {

//
// the declaration block is a "sparse" enumeration collection
using declaration_block = collection<style_id, style_typedef>;

struct rule_set {
    selector_list selector_list;
    declaration_block declaration_block;
};

}
