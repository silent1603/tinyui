cmake_minimum_required(VERSION 3.22)
project(tinyui)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

add_subdirectory(sources)