cmake_minimum_required(VERSION 3.17)
project(Assignment_3)

set(CMAKE_CXX_STANDARD 23)

add_executable(Assignment_3
        main.cpp
        inc/bst.h
        src/dictionary.cpp
        inc/dictionary.h
        src/spell_checker.cpp
        inc/spell_checker.h
        inc/utils.h
        inc/timer.h
        src/utils.cpp
        inc/avl.h
        inc/node.h)
add_executable(check
        main.cpp
        inc/bst.h
        src/dictionary.cpp
        inc/dictionary.h
        src/spell_checker.cpp
        inc/spell_checker.h
        inc/utils.h
        inc/timer.h
        src/utils.cpp
        inc/avl.h
        inc/node.h)
