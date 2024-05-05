cmake_minimum_required(VERSION 3.21.2)
set(CMAKE_CXX_STANDARD 20)
project(yaka)

add_library(yaka src/yaka.cc)

target_include_directories(yaka PUBLIC
        "include"
)