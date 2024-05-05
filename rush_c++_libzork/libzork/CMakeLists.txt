cmake_minimum_required(VERSION 3.21.2)
set(CMAKE_CXX_STANDARD 20)
project(libzork)

add_compile_options(-Wall -Wextra -Werror -std=c++20 -g)

find_library(YAML-CPP NAMES yaml-cpp libyaml-cpp REQUIRED)

add_library(libzork SHARED)

target_include_directories(libzork PUBLIC include)
target_include_directories(libzork PRIVATE src)

target_link_libraries(libzork PRIVATE ${YAML-CPP})
set_target_properties(libzork PROPERTIES OUTPUT_NAME zork)


add_subdirectory(src)
#add_subdirectory(zorkxplorer)
add_subdirectory(tests)

