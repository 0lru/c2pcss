#pragma once
// #include "color.h"

#include <variant>
#include <vector>

namespace css {

enum class cascade {
    inherit,
    initial
};

template <typename T>
using cascadable = std::variant<cascade, T>;

struct px {
    float value;
};

struct em {
    float value;
};

struct rem {
    float value;
};

struct percentage {
    float value;
};

using length = std::variant<px, em, rem>;

using length_percentage = std::variant<length, percentage>;

enum class combinator {
    plus, // '+'
    tilde, // '~'
    greater, // '>'
};

struct type_selector {
    std::string value;
};
struct hash_selector {
    std::string value;
};
struct class_selector {
    std::string value;
};
struct pseudo_selector {
    std::string value;
};

struct selector_segment {
    // optional combinator
    std::optional<combinator> combinator;
    // this can also contain the universal selector '*'
    type_selector type_selector;
    // example: 'my-item' for '#my-item'
    std::vector<hash_selector> hash_selectors;
    // example: 'xyz' for '.xyz'
    std::vector<class_selector> class_selectors;
    // example: 'hover' for ':hover'
    std::vector<pseudo_selector> pseudo_selectors;
};

using selector = std::vector<selector_segment>;

}
