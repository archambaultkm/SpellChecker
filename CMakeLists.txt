cmake_minimum_required(VERSION 3.17)
project(Assignment_3)

set(CMAKE_CXX_STANDARD 23)

add_executable(Assignment_3
        src/main.cpp
        src/binary_search_tree.h
        src/dictionary.cpp
        src/dictionary.h
        src/spell_checker.cpp
        src/spell_checker.h
        inc/utils.h
        inc/timer.h)
add_executable(check
        src/main.cpp
        src/binary_search_tree.h
        src/dictionary.cpp
        src/dictionary.h
        src/spell_checker.cpp
        src/spell_checker.h
        inc/utils.h
        inc/timer.h)
