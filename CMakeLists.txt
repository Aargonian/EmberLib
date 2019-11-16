cmake_minimum_required(VERSION 3.15)
project(EmberLib C)

set(CMAKE_C_STANDARD 11)

set(SOURCE src/main.c
        include/arraylist_old.h include/arraylist_new.h)

add_executable(EmberLib ${SOURCE})

target_include_directories(EmberLib PRIVATE ${CMAKE_SOURCE_DIR}/include)