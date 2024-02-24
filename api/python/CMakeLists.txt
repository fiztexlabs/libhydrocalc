cmake_minimum_required(VERSION 3.14)
include("cmake/utils.cmake")
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

find_package(Python COMPONENTS Interpreter Development REQUIRED)

set(ext_sources
    src/py_api.cpp
    src/wrappers/hydraulic_resistance.h
    src/opaque_types.h
)

pybind11_add_module(hydrocalc ${ext_sources})

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(hydrocalc
    PRIVATE VERSION_INFO="${CMAKE_PROJECT_VERSION}")

target_link_libraries(hydrocalc
    PRIVATE
    static-libhydrocalc
)

if(NOT is_top_level)
    win_copy_deps_to_target_dir(hydrocalc static-libhydrocalc)
endif()

if(CMAKE_BUILD_TYPE EQUAL Debug)
    target_compile_definitions(hydrocalc
        PUBLIC
        "PYBIND11_DETAILED_ERROR_MESSAGES")
endif()

target_include_directories( hydrocalc
  PUBLIC
    "$<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
  PRIVATE
    "$<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
)