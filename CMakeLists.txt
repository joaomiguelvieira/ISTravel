cmake_minimum_required(VERSION 3.15)
project(ISTravel C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(ISTravel
        src/Bridge.c
        src/Bridge.h
        src/Defs.c
        src/Defs.h
        src/Graph.c
        src/Graph.h
        src/Heap.c
        src/Heap.h
        src/ISTravel.c
        src/LinkedList.c
        src/LinkedList.h
        src/Utilities.c
        src/Utilities.h)
