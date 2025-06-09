cmake_minimum_required(VERSION 3.30)
project(Clipse)

set(CMAKE_CXX_STANDARD 20)

add_executable(Clipse main.cpp
        Macros/macro.cpp
        Macros/macro.h
        Macros/action.cpp
        Macros/action.h
        Macros/keyMap.h
        KeyboardHook/hook.cpp
        KeyboardHook/hook.h
        Macros/input.h)
