cmake_minimum_required(VERSION 3.5)
project(CL0-Interpreter)

include_directories(include)

set(SRC src/main.c
    src/debug.h)

add_executable(${PROJECT_NAME} ${SRC})