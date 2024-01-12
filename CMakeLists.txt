cmake_minimum_required(VERSION 3.5)
project(PL0-Compiler LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

file(GLOB LIB_SRC src/pl0compiler/*.cpp src/pl0compiler/common/*.cpp)
add_library(${PROJECT_NAME} SHARED ${LIB_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ext/CL0-Interpreter/include)

add_executable("${PROJECT_NAME}-App" app/MainApp.cpp)
target_link_libraries ("${PROJECT_NAME}-App" ${PROJECT_NAME})

add_executable("${PROJECT_NAME}-Test" app/TestApp.cpp test/pl0compiler/CompilerTest.cpp)
target_link_libraries ("${PROJECT_NAME}-Test" ${PROJECT_NAME})
target_include_directories("${PROJECT_NAME}-Test" PRIVATE src/pl0compiler)
