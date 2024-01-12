cmake_minimum_required(VERSION 3.5)
project(CL0-Interpreter LANGUAGES C)

include_directories(include)

set(SOURCE src/main.c)

add_executable(${PROJECT_NAME} ${SOURCE})
