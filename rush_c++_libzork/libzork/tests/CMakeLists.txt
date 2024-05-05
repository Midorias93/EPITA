cmake_minimum_required(VERSION 3.21.2)
set(CMAKE_CXX_STANDARD 20)
project(libzork)

add_executable(test main.cc)
target_link_libraries(test PRIVATE libzork)
