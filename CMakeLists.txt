cmake_minimum_required(VERSION 3.14)
project(libhydrocalc
    VERSION 2.0.1
    DESCRIPTION "Library of hydraulic resistances"
    LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(cmake/utils.cmake)
include(GNUInstallDirs)
# set(CMAKE_INSTALL_PREFIX "d:/Users/BARINOV/UsrCppLibs")
# set(CMAKE_INSTALL_PREFIX "c:/Users/abarinov/Documents/Work/MyCppLibs")
# set(CMAKE_INSTALL_PREFIX "d:/Users/Konovalov/MyCppLibs")
# set(CMAKE_INSTALL_PREFIX "c:/Users/jo/MyCppLibs")

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# uncomment for shared build
set(HR_SHARED_LIBS " ")

set(CMAKE_BUILD_TYPE Debug)
option(HR_BUILD_TESTS "Build libhydrocalc tests" ON)
# option(HR_BUILD_PYTHON_EXT "Build libhydrocalc python extension" ON)
option(HR_BUILD_EXAMPLES "Build libhydrocalc examples" OFF)
option(HR_BUILD_DOCS "Build libhydrocalc documentation" OFF)
option(HR_USE_DOUBLE_PRECISION "Use double precision for calculations" ON)
option(HR_BUILD_SERVICE_UTILITES "Build service utilities (e.g. table generator for approximations)" ON)
option(HR_INSTALL "Generate target for installing libhydrocalc" ON)
set_if_undefined(HR_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/libhydrocalc" CACHE STRING
    "Install path for libhydrocalc package-related CMake files")

if(DEFINED HR_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${HR_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(libhydrocalc) # initialized below
add_library(libhydrocalc::libhydrocalc ALIAS libhydrocalc)

#----------------------------------------------------------------------------------------------------------------------
# libhydrocalc dependencies
#----------------------------------------------------------------------------------------------------------------------

include(GoogleTest)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}")

set(MATH_BUILD_TESTS OFF CACHE BOOL "Build libmath tests" FORCE)
set(MATH_BUILD_EXAMPLES OFF CACHE BOOL "Build libmath examples" FORCE)
set(MATH_SHARED_LIBS FALSE CACHE BOOL "STATIC" FORCE)

find_package(libmath QUIET)

if(libmath_FOUND)
    message("-- Found libmath")
else()
    message("-- libmath not found, use local version of libmath")
    add_subdirectory(libs/libmath)
endif()
target_link_libraries(libhydrocalc PRIVATE libmath::libmath)


#----------------------------------------------------------------------------------------------------------------------
# libhydrocalc sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(libhydrocalc EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/${export_file_name})

set(sources
    libhydrocalc/settings.h
    libhydrocalc/service.h
    libhydrocalc/service.cpp
    libhydrocalc/exceptions.h
    libhydrocalc/export.h
    libhydrocalc/hydrocalc.h
    libhydrocalc/hydrocalc.cpp
    libhydrocalc/info.h

    libhydrocalc/c/c_api.h
    libhydrocalc/c/c_api.cpp

    libhydrocalc/hydraulic_resistance.h

    libhydrocalc/hydraulic_resistance_base.h
    libhydrocalc/hydraulic_resistance_base.cpp

    libhydrocalc/complex_resistance.h
    libhydrocalc/complex_resistance.cpp

    libhydrocalc/friction.h
    libhydrocalc/friction.cpp
    
    libhydrocalc/cylindrical_friction.h
    libhydrocalc/cylindrical_friction.cpp
    
    libhydrocalc/ring_friction.h
    libhydrocalc/ring_friction.cpp
    libhydrocalc/approximations/ke27.h
    libhydrocalc/approximations/ke27.cpp
    libhydrocalc/approximations/kn27.h
    libhydrocalc/approximations/kn27.cpp
    
    libhydrocalc/cylindrical_bend.h
    libhydrocalc/cylindrical_bend.cpp
    
    libhydrocalc/cylindrical_bend_niche.h
    libhydrocalc/cylindrical_bend_niche.cpp

    libhydrocalc/cylindrical_diffuser_straight_direct.h
    libhydrocalc/cylindrical_diffuser_straight_direct.cpp
    libhydrocalc/approximations/f52.h
    libhydrocalc/approximations/f52.cpp
    libhydrocalc/approximations/e59.h
    libhydrocalc/approximations/e59.cpp

    libhydrocalc/cylindrical_diffuser_straight.h
    libhydrocalc/cylindrical_diffuser_straight.cpp

    libhydrocalc/cylindrical_confuser_straight_direct.h
    libhydrocalc/cylindrical_confuser_straight_direct.cpp

    libhydrocalc/cylindrical_confuser_straight.h
    libhydrocalc/cylindrical_confuser_straight.cpp

    libhydrocalc/cylindrical_diffuser_curve_direct.h
    libhydrocalc/cylindrical_diffuser_curve_direct.cpp

    libhydrocalc/cylindrical_confuser_curve_direct.h
    libhydrocalc/cylindrical_confuser_curve_direct.cpp
    libhydrocalc/approximations/e523.h
    libhydrocalc/approximations/e523.cpp

    libhydrocalc/cylindrical_diffuser_curve.h
    libhydrocalc/cylindrical_diffuser_curve.cpp

    libhydrocalc/cylindrical_confuser_curve.h
    libhydrocalc/cylindrical_confuser_curve.cpp

    libhydrocalc/sharp_unexpected_size_change.h
    libhydrocalc/sharp_unexpected_size_change.cpp

    libhydrocalc/composite.h
    libhydrocalc/composite.cpp

)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# libhydrocalc target
#----------------------------------------------------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

target_sources(libhydrocalc PRIVATE ${sources})
target_compile_definitions(libhydrocalc 
    PUBLIC
        _USE_MATH_DEFINES=1
        "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:HR_STATIC_DEFINE>"
        "$<$<BOOL:${HR_USE_DOUBLE_PRECISION}>:HR_DOUBLE_PRECISION_DEFINE>")

target_include_directories(libhydrocalc
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>")

set_target_properties(libhydrocalc PROPERTIES
    PREFIX ""
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(HR_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/libhydrocalc-config.cmake.in libhydrocalc-config.cmake
        INSTALL_DESTINATION "${HR_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(libhydrocalc-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS libhydrocalc EXPORT libhydrocalc_export
        RUNTIME COMPONENT libhydrocalc
        LIBRARY COMPONENT libhydrocalc NAMELINK_COMPONENT libhydrocalc-dev
        ARCHIVE COMPONENT libhydrocalc-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY libhydrocalc
        TYPE INCLUDE
        COMPONENT libhydrocalc-dev
        FILES_MATCHING PATTERN "*.h")
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/libhydrocalc/${export_file_name}"
        COMPONENT libhydrocalc-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/libhydrocalc")

    set(targets_file "libhydrocalc-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "libhydrocalc-static-targets.cmake")
    endif()

    install(EXPORT libhydrocalc_export
        COMPONENT libhydrocalc-dev
        FILE "${targets_file}"
        DESTINATION "${HR_INSTALL_CMAKEDIR}"
        NAMESPACE libhydrocalc::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/libhydrocalc-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/libhydrocalc-config-version.cmake"
        COMPONENT libhydrocalc-dev
        DESTINATION "${HR_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:libhydrocalc>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:libhydrocalc>/$<TARGET_FILE_PREFIX:libhydrocalc>$<TARGET_FILE_BASE_NAME:libhydrocalc>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT libhydrocalc-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()

# ----------------------------------------------------------------------------------------------------------------------
# other targets
# ----------------------------------------------------------------------------------------------------------------------

# --------------------------------------------------------
# build static version of libhydrocalc
# --------------------------------------------------------
add_library(static-libhydrocalc STATIC ${sources})

target_link_libraries(static-libhydrocalc PRIVATE libmath::libmath)

generate_export_header(static-libhydrocalc
    EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/export_static.h
    BASE_NAME libhydrocalc
)

target_compile_definitions(static-libhydrocalc
    PUBLIC
        _USE_MATH_DEFINES=1
        HR_STATIC_DEFINE
        "$<$<BOOL:${HR_USE_DOUBLE_PRECISION}>:HR_DOUBLE_PRECISION_DEFINE>")

target_include_directories(static-libhydrocalc
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>")

set_target_properties(static-libhydrocalc PROPERTIES
    PREFIX ""
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

# --------------------------------------------------------
if(HR_BUILD_TESTS)
    enable_testing()
    set(gtest_force_shared_crt ON
        CACHE BOOL
        "Use shared (DLL) run-time lib even when Google Test is built as static lib."
        FORCE
    )
    # find_package(GTest QUIET)
    if(GTest_FOUND)
        message("-- Found GTest")
    else()
        message("-- GTest not found, use local version of GTest")
        add_subdirectory(libs/googletest)
    endif()
    add_subdirectory(tests)

    # #---------------------------------------------
    # # validation test
    # #---------------------------------------------
    # add_executable ( libhydrocalc-validation-test )    
    # if(GTest_FOUND)
    #     target_link_libraries( libhydrocalc-validation-test
    #        PRIVATE
    #            static-libhydrocalc
    #            libmath::libmath
    #            GTest::GTest
    #            GTest::Main
    #     )
    #     win_copy_deps_to_target_dir(libhydrocalc-validation-test 
    #         GTest::GTest
    #         GTest::Main
    #     )
    # else()
    #     target_link_libraries( libhydrocalc-validation-test
    #        PRIVATE
    #            static-libhydrocalc
    #            libmath::libmath
    #            gtest
    #            gtest_main
    #     )
    #     win_copy_deps_to_target_dir(libhydrocalc-validation-test 
    #         gtest
    #         gtest_main
    #     )
    # endif()
    # set(ValidationTestSources
    #     libhydrocalc/core/test_functions.h
    #     libhydrocalc/n2/n2.test.cpp
    #     libhydrocalc/o2/o2.test.cpp
    #     libhydrocalc/co2/co2.test.cpp
    #     libhydrocalc/c3h8/c3h8.test.cpp
    #     libhydrocalc/if95/if95.test.cpp
    # )
    # target_sources ( libhydrocalc-validation-test PRIVATE ${ValidationTestSources} )
    # win_copy_deps_to_target_dir(libhydrocalc-validation-test 
    #     static-libhydrocalc
    #     # libmath::libmath
    # )
endif()

if(HR_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(HR_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()

# if(HR_BUILD_PYTHON_EXT)
#     message("-- Build python library")
#     find_package(pybind11 QUIET)
#     if(pybind11_FOUND)
#         message("-- Found pybind11")
#     else()
#         message("-- pybind11 not found, use local version of pybind11")
#         add_subdirectory(libs/pybind11)
#     endif()

#     add_subdirectory(api/python)
# endif()