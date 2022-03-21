cmake_minimum_required(VERSION 3.21)
project(imgui)

set(CMAKE_CXX_STANDARD 14)

include_directories(lotto)

add_executable(imgui
        BallsArray.h
        Ball.h
        ../examples/example_win32_directx11/main.cpp
        BallsLogic.cpp)
