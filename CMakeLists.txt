cmake_minimum_required(VERSION 3.12)
project(pipeline_bindings)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(pybind11)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(pipeline SHARED src/Pipeline.cpp src/pipeline_bindings.cpp)
target_link_libraries(pipeline PRIVATE pybind11::module)
