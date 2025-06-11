#ifndef HOOK_H
#define HOOK_H

#include "../Macros/macro.h"
#include "../defines.h"

#include <string>
#include <algorithm>
#include <stdexcept>
#include <thread>
#include <atomic>

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
inline HHOOK hKeyboardHook;
inline std::vector<macro> scans;

class hook {
    std::thread messageThread;
    std::atomic<bool> running{false};

    void messageLoop();

public:
    explicit hook(const std::vector<macro> &macros);
    ~hook();

    static void add_scan(const macro& scan);
    static bool remove_scan(const macro& scan);
};



#endif //HOOK_H
