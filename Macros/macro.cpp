#include "macro.h"

bool macro::operator==(const macro& m) const {
    return (name == m.name) && (trigger == m.trigger) && (action == m.action);
}

bool macro::operator!=(const macro& m) const {
    return !(*this == m);
}