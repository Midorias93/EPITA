cmake_minimum_required(VERSION 3.21.2)
set(CMAKE_CXX_STANDARD 20)
project(libzork)

target_sources(libzork PRIVATE store.cc store_impl.cc)



