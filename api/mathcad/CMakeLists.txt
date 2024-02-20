cmake_minimum_required(VERSION 3.14)
include("cmake/utils.cmake")
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

set(MATHCAD_ROOT "c:/Program Files (x86)/Mathcad/Mathcad 15/")

set(ext_sources
    src/mathcad_api.cpp
)
add_library(mcadhydrocalc SHARED ${ext_sources})

if(NOT WIN32)
  message(FATAL_ERROR "[${PROJECT_NAME}] - MATHCAD_MODULE can only be used on windows host")
endif()
if( "${MATHCAD_ROOT}" STREQUAL "")
    message(FATAL_ERROR "[${PROJECT_NAME}] - You must provide the path to MathCAD Root directory using something like -DMATHCAD_ROOT=\"c:/Program Files (x86)/Mathcad/Mathcad 15\"")
else()
    message(STATUS "[${PROJECT_NAME}] - MATHCAD_ROOT: ${MATHCAD_ROOT}")
endif()

target_include_directories( mcadhydrocalc
  PUBLIC
    "$<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    "${MATHCAD_ROOT}/userefi/microsft/include"
  PRIVATE
    "$<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "${MATHCAD_ROOT}/userefi/microsft/include"
)
target_link_libraries(mcadhydrocalc
    PRIVATE
    static-libhydrocalc
    "${MATHCAD_ROOT}/userefi/microsft/lib/mcaduser.lib"
)

set_target_properties(mcadhydrocalc PROPERTIES LINK_FLAGS "/ENTRY:\"DllEntryPoint\"")
set_target_properties(mcadhydrocalc PROPERTIES SUFFIX ".dll" PREFIX "")

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

generate_export_header(mcadhydrocalc EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/export_shared.h)