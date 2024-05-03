cmake_minimum_required(VERSION 3.28)
project(travellingsalesperson)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(travellingsalesperson
        src/Menu.cpp
        src/Menu.h
        main.cpp
        src/Graph.h
        src/Graph.cpp
        src/Manager.h
        src/Manager.cpp
)
