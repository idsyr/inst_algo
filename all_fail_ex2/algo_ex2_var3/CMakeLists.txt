cmake_minimum_required(VERSION 3.5)

project(algo_ex2_var3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(algo_ex2_var3 main.cpp)

install(TARGETS algo_ex2_var3
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
