#include "model.h"

namespace css {

px operator"" _px(const char* value) { return px { value }; }
em operator"" _em(const char* value) { return em { value }; }
rem operator"" _rem(const char* value) { return rem { value }; }
percentage operator"" _percent(const char* value) { return percentage { value }; }

}