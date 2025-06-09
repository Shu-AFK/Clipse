#ifndef ACTION_H
#define ACTION_H

#include "input.h"

#include <string>
#include <vector>
#include <chrono>
#include <winuser.h>
#include <windows.h>

namespace action {
    enum ACTION_NUM {
        KEY_PRESS,
        KEY_COMBO,
        DELAY,
        EXEC,
    };

    enum EXEC_NUM {
        CLOSE,
        OPEN,
    };

    struct EXEC_ACT {
        EXEC_NUM num;
        std::string execName;

        bool operator==(const EXEC_ACT &e) const {
            return (num == e.num) && (execName == e.execName);
        }

        bool operator!=(const EXEC_ACT &e) const {
            return !(*this == e);
        }
    };

    struct ACT {
        ACTION_NUM num;
        INPUT input;
        std::chrono::milliseconds delayTime;
        EXEC_ACT exec;

        bool operator==(const ACT &a) const {
            return (num == a.num) && (input == a.input) && (delayTime == a.delayTime) && (exec == a.exec);
        }

        bool operator!=(const ACT &a) const {
            return !(*this == a);
        }
    };

    class action {
        std::vector<ACT> inputs;

        int parseAction(const std::wstring &_action);
        int parseComboAction(const std::wstring &comboKeys);

    public:
        action(const std::wstring& _action) {
            parseAction(_action);
        }

        bool operator==(const action &a) const;
        bool operator!=(const action &a) const;

        int doAction(std::string &err);
    };
}



#endif //ACTION_H
