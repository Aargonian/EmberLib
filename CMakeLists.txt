cmake_minimum_required(VERSION 3.15)
project(EmberLib C)

set(CMAKE_C_STANDARD 11)

set(SOURCE src/main.c
           include/arraylist.h)

add_executable(EmberLib ${SOURCE})

target_include_directories(EmberLib PRIVATE ${CMAKE_SOURCE_DIR}/include)