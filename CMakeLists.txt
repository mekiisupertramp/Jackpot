cmake_minimum_required(VERSION 3.6)
project(jackpot)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -lpthread")

set(SOURCE_FILES libs/display.c libs/display.h libs/header.h libs/structThreads.h libs/timing.c libs/timing.h libs/wheels.c libs/wheels.h main.c)
add_executable(jackpot ${SOURCE_FILES})