#ifndef MACRO_H
#define MACRO_H

#include "action.h"

#include <string>
#include <utility>

class macro {
    std::string name;
    std::string trigger;
    action::action action;

public:
    macro(std::string _name, std::string _trigger, const std::wstring& _action)
    : name(std::move(_name)), trigger(std::move(_trigger)), action(_action) {}

    bool operator==(const macro& m) const;
    bool operator!=(const macro& m) const;

    std::string get_name() { return name; }
    std::string get_trigger() { return trigger; }
    action::action get_action() { return action; }
};



#endif //MACRO_H
