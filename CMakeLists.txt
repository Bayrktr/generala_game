cmake_minimum_required(VERSION 3.29)
project(generala_game)

set(CMAKE_CXX_STANDARD 20)

add_executable(generala_game main.cpp
        project/tasks/choose_who_start_first/choose_who_start_first.cpp
        project/tasks/print_score_sheet/print_score_sheet.cpp
        project/tasks/print_score_sheet/print_score_sheet.h)
