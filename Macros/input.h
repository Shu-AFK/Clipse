#ifndef INPUT_H
#define INPUT_H

#include <windows.h>
#include <cstring>

inline bool operator==(const INPUT& lhs, const INPUT& rhs) {
    if (lhs.type != rhs.type)
        return false;

    // Compare based on input type
    switch (lhs.type) {
        case INPUT_KEYBOARD:
            return lhs.ki.wVk == rhs.ki.wVk &&
                   lhs.ki.wScan == rhs.ki.wScan &&
                   lhs.ki.dwFlags == rhs.ki.dwFlags &&
                   lhs.ki.time == rhs.ki.time &&
                   lhs.ki.dwExtraInfo == rhs.ki.dwExtraInfo;

        case INPUT_MOUSE:
            return lhs.mi.dx == rhs.mi.dx &&
                   lhs.mi.dy == rhs.mi.dy &&
                   lhs.mi.mouseData == rhs.mi.mouseData &&
                   lhs.mi.dwFlags == rhs.mi.dwFlags &&
                   lhs.mi.time == rhs.mi.time &&
                   lhs.mi.dwExtraInfo == rhs.mi.dwExtraInfo;

        case INPUT_HARDWARE:
            return lhs.hi.uMsg == rhs.hi.uMsg &&
                   lhs.hi.wParamL == rhs.hi.wParamL &&
                   lhs.hi.wParamH == rhs.hi.wParamH;

        default:
            return false;
    }
}

#endif //INPUT_H
