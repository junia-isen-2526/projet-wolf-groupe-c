cmake_minimum_required(VERSION 3.30)
project(wolf C)

set(CMAKE_C_STANDARD 11)

add_executable(wolf main.c
        wolf.c
        wolf.h
        child.c
        child.h
        forest.h
        forest.c)
