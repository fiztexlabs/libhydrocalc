cmake_minimum_required( VERSION 3.20 )

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include("cmake/utils.cmake")
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

if(is_top_level)
    enable_testing()
endif()

#----------------------------------------------------------------------------------------------------------------------
# testing framework
#----------------------------------------------------------------------------------------------------------------------

#include(FetchContent)
#FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz)

#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # do not override parent project's runtime settings on Windows
#set(INSTALL_GTEST OFF)

## For simplicity, always build googletest as static library. This prevents mylib-tests executable from
## complaining about missing googletest DLLs on Windows.
# set(BUILD_SHARED_LIBS OFF)

#FetchContent_MakeAvailable(googletest)

# build gtest from source tree
# add_subdirectory(./googletest)

add_executable ( libhydrocalc-basic-test )
add_executable ( libhydrocalc-debug-test )
# add_executable ( libhydrocalc-capi-test )

#----------------------------------------------------------------------------------------------------------------------
# tests dependencies
#----------------------------------------------------------------------------------------------------------------------

if(is_top_level)
    # set(CMAKE_PREFIX_PATH "d:/Users/BARINOV/UsrCppLibs")
    # set(CMAKE_INSTALL_PREFIX "d:/Users/Konovalov/MyCppLibs")
    # find_package(math REQUIRED)
endif()

if(GTest_FOUND)
   target_link_libraries( libhydrocalc-basic-test
       PRIVATE
           static-libhydrocalc
           GTest::GTest
           GTest::Main
   )
#    target_link_libraries( libhydrocalc-capi-test
#        PRIVATE
#            libhydrocalc::libhydrocalc
#            GTest::GTest
#            GTest::Main
#    )
   if(NOT is_top_level)
        win_copy_deps_to_target_dir(libhydrocalc-basic-test 
            GTest::GTest
            GTest::Main
        )
        # win_copy_deps_to_target_dir(libhydrocalc-capi-test 
        #     GTest::GTest
        #     GTest::Main
        # )
   endif()
else()
   target_link_libraries( libhydrocalc-basic-test
       PRIVATE
           static-libhydrocalc
           gtest
           gtest_main
           libmath::libmath
    )
#    target_link_libraries( libhydrocalc-capi-test
#        PRIVATE
#            libhydrocalc::libhydrocalc
#            gtest
#            gtest_main
#     )
    if(NOT is_top_level)
        win_copy_deps_to_target_dir(libhydrocalc-basic-test 
            gtest
            gtest_main
        )
        # win_copy_deps_to_target_dir(libhydrocalc-capi-test 
        #     gtest
        #     gtest_main
        # )
    endif()
endif()

target_link_libraries( libhydrocalc-debug-test
PRIVATE
    static-libhydrocalc
)

# find_package(libmath QUIET)
# target_link_libraries(libhydrocalc-debug-test PRIVATE libmath::libmath)
# target_link_libraries(libhydrocalc-basic-test PRIVATE libmath::libmath)
# # target_link_libraries(libhydrocalc-capi-test PRIVATE libmath::libmath)


if(NOT is_top_level)
    win_copy_deps_to_target_dir(libhydrocalc-basic-test 
        static-libhydrocalc
        # libmath::libmath
    )
    win_copy_deps_to_target_dir(libhydrocalc-debug-test 
        static-libhydrocalc
        # libmath::libmath
    )
    # win_copy_deps_to_target_dir(libhydrocalc-capi-test 
    #     libhydrocalc::libhydrocalc
    #     # libmath::libmath
    # )
endif()

#----------------------------------------------------------------------------------------------------------------------
# tests sources
#----------------------------------------------------------------------------------------------------------------------

set(BasicTestSources
    #tests_main.cc 
    basics/test_curve_confuser.cpp
    basics/test_validation.cpp
)

set(DebugTestSources
    debug/test_debug.cpp
)

# set(CAPITestSources
#     c_api/test_c_api.cpp
# )

#----------------------------------------------------------------------------------------------------------------------
# tests target
#----------------------------------------------------------------------------------------------------------------------

target_sources ( libhydrocalc-basic-test PRIVATE ${BasicTestSources} )

target_include_directories( libhydrocalc-basic-test
  PUBLIC
    "$<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
  PRIVATE
    "$<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
)


target_sources ( libhydrocalc-debug-test PRIVATE ${DebugTestSources} )

target_include_directories( libhydrocalc-debug-test
  PUBLIC
    "$<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
  PRIVATE
    "$<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
)


# target_sources ( libhydrocalc-capi-test PRIVATE ${CAPITestSources} )

# target_include_directories( libhydrocalc-capi-test
#   PUBLIC
#     "$<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}>"
#     "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
#   PRIVATE
#     "$<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}>"
#     "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
# )
