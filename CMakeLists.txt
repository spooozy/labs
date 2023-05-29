cmake_minimum_required(VERSION 3.24)
project(labs C)

set(CMAKE_C_STANDARD 11)

add_executable(laba1 labs/laba1/main.c labs/laba1/Header.h labs/laba1/Source.c)
add_executable(list labs/laba2/list/main.c labs/laba2/list/Header.h labs/laba2/list/Source.c)
add_executable(rearhive labs/laba2/rearhive/main.c labs/laba2/rearhive/Header.h labs/laba2/rearhive/Source.c)
add_executable(laba3 labs/laba3/main.c labs/laba3/Header.h labs/laba3/Source.c)
add_executable(laba4 labs/laba4/main.c labs/laba4/Header.h labs/laba4/Source.c)
add_executable(laba5 labs/laba5/main.c labs/laba5/Header.h labs/laba5/Source.c)
