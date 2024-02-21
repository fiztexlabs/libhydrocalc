cmake_minimum_required(VERSION 3.14)
include("cmake/utils.cmake")
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# set(MATHCAD_ROOT "d:\\Users\\Mathcad\\Mathcad 14\\")

set(ext_sources
    src/mathcad_api.cpp
)
add_library(libhydrocalcmcad SHARED ${ext_sources})

if(NOT WIN32)
  message(FATAL_ERROR "[${PROJECT_NAME}] - MATHCAD_MODULE can only be used on windows host")
endif()
if( "${MATHCAD_ROOT}" STREQUAL "")
    message(FATAL_ERROR "[${PROJECT_NAME}] - You must provide the path to MathCAD Root directory using something like -DMATHCAD_ROOT=\"c:/Program Files (x86)/Mathcad/Mathcad 15\"")
else()
    message(STATUS "[${PROJECT_NAME}] - MATHCAD_ROOT: ${MATHCAD_ROOT}")
endif()

target_include_directories( libhydrocalcmcad
  PUBLIC
    "$<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    "${MATHCAD_ROOT}/userefi/microsft/include"
  PRIVATE
    "$<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    "${MATHCAD_ROOT}/userefi/microsft/include"
)
target_link_libraries(libhydrocalcmcad
    PRIVATE
    #static-libhydrocalc
    libhydrocalc::libhydrocalc
    "${MATHCAD_ROOT}/userefi/microsft/lib/mcaduser.lib"
)

if(NOT is_top_level)
    win_copy_deps_to_target_dir(libhydrocalcmcad
        libhydrocalc::libhydrocalc
        #static-libhydrocalc
    )
endif()

set_target_properties(libhydrocalcmcad PROPERTIES LINK_FLAGS "/ENTRY:\"DllMain\"")
set_target_properties(libhydrocalcmcad PROPERTIES PREFIX "")

# target_compile_options(libhydrocalcmcad PUBLIC "-MT")
