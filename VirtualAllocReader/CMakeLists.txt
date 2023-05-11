cmake_minimum_required(VERSION 3.16.3)
project(VirtualAllocReader C)

set(CMAKE_C_STANDARD 99)

add_library(shm_lib OBJECT
        ../shm_lib/include/shm_sysv.h
        ../shm_lib/include/semun.h
        ../shm_lib/include/binary_sems.h
        ../shm_lib/src/binary_sems.c
        )

target_include_directories(shm_lib
        PUBLIC  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../shm_lib/include>
        )

add_executable(VirtualAllocReader main.c)
target_link_libraries(VirtualAllocReader PRIVATE shm_lib)
