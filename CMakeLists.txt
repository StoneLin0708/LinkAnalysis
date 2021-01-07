cmake_minimum_required(VERSION 3.10)

project(linkanalysis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -fsanitize=address")
add_subdirectory(fmt EXCLUDE_FROM_ALL)

add_subdirectory(src)