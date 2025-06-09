#include "hook.h"

void hook::add_scan(const macro& scan) {
    scans.push_back(scan);
}

bool hook::remove_scan(const macro& scan) {
    if (const auto it = std::find(scans.begin(), scans.end(), scan); it != scans.end()) {
        scans.erase(it);
        return true;
    }

    return false;
}