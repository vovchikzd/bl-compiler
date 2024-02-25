cmake_minimum_required(VERSION 3.15)
project(bl-lang
        LANGUAGES CXX)

set(CMAKE_CXX_COMPILER clang++)
# set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

find_package(FLEX REQUIRED)
flex_target(lexer scanners/flex/scanner.l scanners/flex/scanner.cpp)

add_executable(lexer main.cpp
                     scanners/flex/scanner.cpp)
