cmake_minimum_required(VERSION 3.17)
project(Buffering_with_Memory C)

set(CMAKE_C_STANDARD 99)

add_executable(Buffering_with_Memory main.c buffer.c buffer.h io.c io.h memory.c memory.h)