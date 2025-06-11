#include "hook.h"

std::vector<wchar_t> buffer;

// TODO: Finish scanning for all macro triggers
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        const auto* pKeyStruct = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);

    }

    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

void hook::messageLoop() {
    MSG msg;
    while (running && GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

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

hook::hook(const std::vector<macro> &macros) {
    scans = macros;
    running = true;

    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(nullptr), NULL);
    if (hKeyboardHook == nullptr) {
        throw std::runtime_error("Failed to hook Keyboard");
    }

    messageThread = std::thread(&hook::messageLoop, this);
}

hook::~hook() {
    running = false;

    PostThreadMessage(GetThreadId(reinterpret_cast<HANDLE>(messageThread.native_handle())), WM_QUIT, 0, 0);

    if (messageThread.joinable()) {
        messageThread.join();
    }

    if (hKeyboardHook != nullptr) {
        UnhookWindowsHookEx(hKeyboardHook);
    }
}