cmake_minimum_required(VERSION 3.24)
project(term2 C)

set(CMAKE_C_STANDARD 11)

add_executable(laba1 term2/laba1/main.c term2/laba1/Header.h term2/laba1/Source.c)
add_executable(list term2/laba2/list/main.c term2/laba2/list/Header.h term2/laba2/list/Source.c)
add_executable(rearhive term2/laba2/rearhive/main.c term2/laba2/rearhive/Header.h term2/laba2/rearhive/Source.c)
add_executable(laba3 term2/laba3/main.c term2/laba3/Header.h term2/laba3/Source.c)
add_executable(laba4 term2/laba4/main.c term2/laba4/Header.h term2/laba4/Source.c)
add_executable(laba5 term2/laba5/main.c term2/laba5/Header.h term2/laba5/Source.c)
