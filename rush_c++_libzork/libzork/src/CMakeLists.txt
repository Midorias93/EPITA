cmake_minimum_required(VERSION 3.21.2)
set(CMAKE_CXX_STANDARD 20)
project(libzork)

target_sources(libzork PRIVATE exceptions.cc)

add_subdirectory(runner)
add_subdirectory(store)
add_subdirectory(story)
add_subdirectory(vars)


