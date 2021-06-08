cmake_minimum_required(VERSION 3.16)
project(so2021_tutorial)

set(CMAKE_CXX_STANDARD 20)


include_directories(exercise5)

add_executable(CRS
        exercise5/task4.cpp
        exercise5/CRS.h
        exercise5/Vector.hh
        exercise5/Vector.cc)