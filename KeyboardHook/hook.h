#ifndef HOOK_H
#define HOOK_H

#include "../Macros/macro.h"

#include <string>
#include <algorithm>

class hook {
    std::vector<macro> scans;

public:
    void add_scan(const macro& scan);
    bool remove_scan(const macro& scan);
};



#endif //HOOK_H
