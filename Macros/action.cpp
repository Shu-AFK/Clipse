#include "action.h"

#include <thread>

#include "keyMap.h"

int action::action::parseComboAction(const std::wstring &comboKeys) {
    std::wstringstream comboKeysStream(comboKeys);
    std::vector<std::wstring> comboKeysVector;
    comboKeysVector.reserve(comboKeys.size() / 2);
    std::wstring comboKey;

    std::vector<KEY_MAP_CACHE> cache;
    cache.reserve(comboKeys.size() / 2);

    while (getline(comboKeysStream, comboKey, L'+')) {
        comboKeysVector.push_back(comboKey);
    }

    for (int i = 0; i < comboKeysVector.size(); i++) {
        if (keyMap.find(comboKeysVector[i]) != keyMap.end()) {
            ACT keyPress = {
                KEY_PRESS,
                INPUT { .type = INPUT_KEYBOARD, .ki.wVk = keyMap[comboKeysVector[i]] },
            };

            cache.push_back(KEY_MAP_CACHE { KEY_MAP, keyMap[comboKeysVector[i]] } );
            inputs.push_back(keyPress);
        } else if (mediaKeys.find(comboKeysVector[i]) != mediaKeys.end()) {
            ACT keyPress = {
                KEY_PRESS,
                INPUT { .type = INPUT_KEYBOARD, .ki { .wVk = mediaKeys[comboKeysVector[i]], .dwFlags = KEYEVENTF_EXTENDEDKEY } },
            };

            cache.push_back(KEY_MAP_CACHE { MEDIA, mediaKeys[comboKeysVector[i]] } );
            inputs.push_back(keyPress);
        } else if (comboKeysVector[i].length() == 1) {
            ACT keyPress = {
                KEY_PRESS,
                INPUT { .type = INPUT_KEYBOARD, .ki.wVk = LOBYTE(::VkKeyScanW(comboKeysVector[i][0])) },
            };

            cache.push_back(KEY_MAP_CACHE { REGULAR } );
            inputs.push_back(keyPress);
        } else {
            return -1;
        }
    }

    for (int i = comboKeysVector.size() - 1; i >= 0; i--) {
        if (cache[i].type == KEY_MAP) {
            ACT keyRelease = {
                KEY_PRESS,
                INPUT { .type = INPUT_KEYBOARD, .ki = { .wVk = cache[i].key, .dwFlags = KEYEVENTF_KEYUP } }
            };

            inputs.push_back(keyRelease);
        }
        else if (cache[i].type == MEDIA) {
            ACT keyRelease = {
                KEY_PRESS,
                INPUT { .type = INPUT_KEYBOARD, .ki = { .wVk = cache[i].key, .dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_EXTENDEDKEY } }
            };

            inputs.push_back(keyRelease);
        }
        else {
            ACT keyRelease = {
                KEY_PRESS,
                INPUT { .type = INPUT_KEYBOARD, .ki { .wVk = LOBYTE(::VkKeyScanW(comboKeysVector[i][0])), .dwFlags = KEYEVENTF_KEYUP } },
            };

            inputs.push_back(keyRelease);
        }
    }

    return 0;
}

int action::action::parseAction(const std::wstring& _action) {
    for (auto it = _action.begin(); it != _action.end(); ++it) {
        wchar_t c = *it;

        // Combo Keys
        if (c == '{' && (it == _action.begin() || *(it - 1) != '\\')) {
            ++it;
            std::wstring comboKeys;

            while (*it != '}' && *(it - 1) != '\\') {
                comboKeys += c;
                ++it;
            }

            if (parseComboAction(comboKeys) == -1) return -1;
        }

        // Time Delay
        else if (c == '[' && (it == _action.begin() || *(it - 1) != '\\')) {
            ++it;
            std::wstring time;

            while (*it != ']') {
                time += *it;
                ++it;
            }

            int t = std::stoi(time);
            ACT delay {
                .num = DELAY,
                .delayTime = std::chrono::milliseconds(t),
            };
            inputs.push_back(delay);
        }

        // Regular Keys
        else {
            ACT keyPress = {
                KEY_PRESS,
                INPUT { .type = INPUT_KEYBOARD, .ki = { .wScan = static_cast<WORD>(c), .dwFlags = KEYEVENTF_UNICODE } }
            };
            inputs.push_back(keyPress);

            keyPress.input.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
            inputs.push_back(keyPress);
        }
    }

    return 0;
}


int action::action::doAction(std::string &err) {
    std::vector<INPUT> _actions;

    for (auto it = inputs.begin(); it != inputs.end(); ++it) {
        if (it->num == KEY_PRESS) {
            while (it != inputs.end() && it->num == KEY_PRESS) {
                _actions.push_back(it->input);
                ++it;
            }

            if (SendInput(_actions.size(), _actions.data(), sizeof(INPUT)) != _actions.size()) {
                err = "SendInput failed: " + std::to_string(HRESULT_FROM_WIN32(GetLastError()));
                return -1;
            }
            _actions.clear();

        } else if (it->num == DELAY) {
            std::this_thread::sleep_for(it->delayTime);
        } else {
            err = "Unknown action type";
            return -1;
        }
    }

    return 0;
}

bool action::action::operator==(const action &a) const {
    return inputs == a.inputs;
}

bool action::action::operator!=(const action &a) const {
    return !(*this == a);
}
