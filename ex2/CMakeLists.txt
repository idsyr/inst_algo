cmake_minimum_required(VERSION 3.5)

project(algo_KT3_ex2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(algo_KT3_ex2 main.cpp point.cpp point.h field.cpp field.h room.cpp room.h line.cpp line.h)

install(TARGETS algo_KT3_ex2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
