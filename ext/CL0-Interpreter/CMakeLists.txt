cmake_minimum_required (VERSION 3.5)
project (CL0-Interpreter)

set (SRC
    src/main.c
    src/code.h
    src/debug.h)

add_executable (${PROJECT_NAME} ${SRC})