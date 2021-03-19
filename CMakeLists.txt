cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
project(PL0-Compiler LANGUAGES CXX)

include_directories(ext/CL0-Interpreter/include)

file(GLOB SOURCE
    app/App.cpp
    src/pl0compiler/*.cpp
    src/pl0compiler/common/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})
