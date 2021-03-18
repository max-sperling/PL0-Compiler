cmake_minimum_required(VERSION 3.5)
project(PL0-Compiler)

include_directories(ext/CL0-Interpreter/include)

file(GLOB SRC app/Main.cpp
     src/pl0compiler/*.cpp
     src/pl0compiler/*.hpp
     src/pl0compiler/common/*.cpp
     src/pl0compiler/common/*.hpp)

add_executable(${PROJECT_NAME} ${SRC})