cmake_minimum_required(VERSION 3.14)
include("cmake/utils.cmake")
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# set(MATHCAD_ROOT "d:\\Users\\Mathcad\\Mathcad 14\\")

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "Mathcad wrapper must be 32 bit")
endif()

set(ext_sources
    src/libhydrocalcmcad.rc

    src/mathcad_api.h
    src/mathcad_api.cpp
    src/create_hydraulic_resistance.h
    src/create_composite.h
    src/delete.h
    src/clear.h
    src/evaluate.h

    src/get_diagram.h
    src/get_friction_part_coeff.h
    src/get_geometry.h
    src/get_geometry_part_coeff.h
    src/get_id.h
    src/get_length.h
    src/get_local_resistance_coeff.h
    src/get_name.h
    src/get_re.h
    src/get_rel_friction_coeff.h
    src/get_rou.h
    src/get_type.h
    src/get_viscosity.h

    src/set_geometry.h
    src/set_length.h
    src/set_name.h
    src/set_re.h
    src/set_rou.h
    src/set_viscosity.h

    src/composite_erase.h
    src/composite_get.h
    src/composite_getall.h
    src/composite_pushback.h
    src/composite_size.h

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
    static-libhydrocalc
    #libhydrocalc::libhydrocalc
    "${MATHCAD_ROOT}/userefi/microsft/lib/mcaduser.lib"
)

if(NOT is_top_level)
    win_copy_deps_to_target_dir(libhydrocalcmcad
        #libhydrocalc::libhydrocalc
        static-libhydrocalc
    )
endif()

set_target_properties(libhydrocalcmcad PROPERTIES VERSION 0.0.1)

# set_target_properties(libhydrocalcmcad PROPERTIES LINK_FLAGS "/ENTRY:\"DllMain\"")
# set_target_properties(libhydrocalcmcad PROPERTIES PREFIX "")

# target_compile_options(libhydrocalcmcad PUBLIC "-MT")
