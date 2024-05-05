cmake_minimum_required(VERSION 3.21.2)
set(CMAKE_CXX_STANDARD 20)
project(libzork)

target_sources(libzork PRIVATE node.cc node_impl.cc story.cc story_impl.cc choice.cc)


