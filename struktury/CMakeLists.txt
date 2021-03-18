cmake_minimum_required(VERSION 3.10)
project(data_structures)

add_library(data_structures INTERFACE)
target_include_directories(data_structures INTERFACE include/)

add_executable(test_data_structures
  src/test_data_structures.cpp
  src/test_stl_data_structures.cpp
  )

target_link_libraries(test_data_structures data_structures)
