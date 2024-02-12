cmake_minimum_required(VERSION 3.15)
project(coolc
        LANGUAGES CXX)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

find_package(FLEX)
flex_target(lexer lexer/lexer.l lexer/lexer.cpp)

add_executable(lexer main.cpp
                     lexer/lexer.cpp)
