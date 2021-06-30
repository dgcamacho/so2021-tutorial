cmake_minimum_required(VERSION 3.16)
project(so2021_tutorial)

set(CMAKE_CXX_STANDARD 20)


include_directories(exercise5)

add_executable(CRS
        exercise5/material/task4.cc
        exercise5/material/Vector.hh
        exercise5/material/Vector.cc)