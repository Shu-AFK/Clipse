#ifndef KEYMAP_H
#define KEYMAP_H

#include <unordered_map>

#include <Windows.h>
#include <unordered_map>
#include <string>

enum KEY_TYPE {
    MEDIA,
    KEY_MAP,
    REGULAR,
};

struct KEY_MAP_CACHE {
    KEY_TYPE type;
    WORD key;
};

std::unordered_map<std::wstring, WORD> mediaKeys = {
    {L"VolumeUp",   VK_VOLUME_UP},
    {L"VolumeDown", VK_VOLUME_DOWN},
    {L"VolumeMute", VK_VOLUME_MUTE},
    {L"MediaPlay",  VK_MEDIA_PLAY_PAUSE},
    {L"MediaStop",  VK_MEDIA_STOP},
    {L"MediaNext",  VK_MEDIA_NEXT_TRACK},
    {L"MediaPrev",  VK_MEDIA_PREV_TRACK},
};

std::unordered_map<std::wstring, WORD> keyMap = {
    // Modifier Keys
    {L"Ctrl",       VK_CONTROL},
    {L"Control",    VK_CONTROL}, // Alias
    {L"Shift",      VK_SHIFT},
    {L"Alt",        VK_MENU},
    {L"Menu",       VK_MENU},    // Alias (Alt is technically VK_MENU)
    {L"Win",        VK_LWIN},    // Left Windows key
    {L"LWin",       VK_LWIN},    // Left Win
    {L"RWin",       VK_RWIN},    // Right Win

    // Navigation & Editing
    {L"Enter",      VK_RETURN},
    {L"Return",     VK_RETURN},  // Alias
    {L"Tab",        VK_TAB},
    {L"Backspace",  VK_BACK},
    {L"Bksp",       VK_BACK},    // Alias
    {L"Delete",     VK_DELETE},
    {L"Del",        VK_DELETE},  // Alias
    {L"Insert",     VK_INSERT},
    {L"Ins",        VK_INSERT},  // Alias
    {L"Home",       VK_HOME},
    {L"End",        VK_END},
    {L"PageUp",     VK_PRIOR},
    {L"PgUp",       VK_PRIOR},   // Alias
    {L"PageDown",   VK_NEXT},
    {L"PgDn",       VK_NEXT},    // Alias

    // Arrow Keys
    {L"Up",         VK_UP},
    {L"Down",       VK_DOWN},
    {L"Left",       VK_LEFT},
    {L"Right",      VK_RIGHT},

    // Function Keys
    {L"F1",         VK_F1},
    {L"F2",         VK_F2},
    {L"F3",         VK_F3},
    {L"F4",         VK_F4},
    {L"F5",         VK_F5},
    {L"F6",         VK_F6},
    {L"F7",         VK_F7},
    {L"F8",         VK_F8},
    {L"F9",         VK_F9},
    {L"F10",        VK_F10},
    {L"F11",        VK_F11},
    {L"F12",        VK_F12},

    // Lock Keys
    {L"CapsLock",   VK_CAPITAL},
    {L"Caps",       VK_CAPITAL}, // Alias
    {L"NumLock",    VK_NUMLOCK},
    {L"Num",        VK_NUMLOCK}, // Alias
    {L"ScrollLock", VK_SCROLL},
    {L"Scroll",     VK_SCROLL},  // Alia

    // Numpad Keys (when NumLock is OFF, these act as navigation keys)
    {L"Num0",       VK_NUMPAD0},
    {L"Num1",       VK_NUMPAD1},
    {L"Num2",       VK_NUMPAD2},
    {L"Num3",       VK_NUMPAD3},
    {L"Num4",       VK_NUMPAD4},
    {L"Num5",       VK_NUMPAD5},
    {L"Num6",       VK_NUMPAD6},
    {L"Num7",       VK_NUMPAD7},
    {L"Num8",       VK_NUMPAD8},
    {L"Num9",       VK_NUMPAD9},
    {L"Num*",       VK_MULTIPLY},
    {L"Num+",       VK_ADD},
    {L"Num-",       VK_SUBTRACT},
    {L"Num.",       VK_DECIMAL},
    {L"Num/",       VK_DIVIDE},

    // Punctuation/Symbol Keys (physical scancode positions)
    {L"Esc",        VK_ESCAPE},
    {L"PrintScreen",VK_SNAPSHOT},
    {L"PrtSc",      VK_SNAPSHOT}, // Alias
    {L"Pause",      VK_PAUSE},
    {L"Break",      VK_PAUSE},    // Alias
};

#endif //KEYMAP_H
