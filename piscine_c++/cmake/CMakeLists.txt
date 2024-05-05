cmake_minimum_required(VERSION 3.21.2)
set(CMAKE_CXX_STANDARD 20)
project(hello_yaka)

add_executable(hello_yaka src/main.cc)
add_subdirectory(libyaka)

target_link_libraries(hello_yaka PUBLIC yaka)
target_include_directories(hello_yaka PUBLIC
        "libyaka/include"
)