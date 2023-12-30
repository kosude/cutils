cmake_minimum_required(VERSION 3.10)
if (POLICY CMP0077)
  cmake_policy(SET CMP0077 NEW)
endif()

project("cutils" C CXX)

set(CMAKE_CONFIGURATION_TYPES Debug Release)
if (NOT CMAKE_BUILD_TYPE)
    message(WARNING "Missing build configuration type! Defaulted to RELEASE. If this is not ideal, reconfigure project with option -DCMAKE_BUILD_TYPE=(Debug|Release)")
    set(CMAKE_BUILD_TYPE Release)
endif()

option(BUILD_SHARED_LIBS "Build shared/dynamic libraries" ON)
if (BUILD_SHARED_LIBS)
    set(LIB_BUILD_TYPE SHARED)
else()
    set(LIB_BUILD_TYPE STATIC)
endif()

# treating warnings as errors may be problematic when compiling for prod use.
# we are assuming here that lib users will be compiling in release config and lib developers/contributors in debug config.
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC)
        set(CUTILS_COMPILE_OPTIONS
            /W4 /WX)
    else()
        set(CUTILS_COMPILE_OPTIONS
            -Wall -Wextra -pedantic -Werror
            -Wno-strict-prototypes)
    endif()
endif()

option(CUTILS_BUNDLE_LIBS "Bundle compiled modules into one library" ON)

if (CUTILS_BUNDLE_LIBS)
    set(BUNDLE_SRCS)
    set(BUNDLE_INCLUDE_DIRS)
endif()

# function to add a library to the compiled output.
# if CUTILS_BUNDLE_LIBS is ON, then the source is appended to one target.
# otherwise, a separate target is defined for each source module.
function(cutils_add_module LIBNAME INCLUDE_DIR SOURCES)
    if (CUTILS_BUNDLE_LIBS)
        set(BUNDLE_SRCS ${BUNDLE_SRCS} ${SOURCES} PARENT_SCOPE)
        set(BUNDLE_INCLUDE_DIRS ${BUNDLE_INCLUDE_DIRS} "${INCLUDE_DIR}" PARENT_SCOPE)
    else()
        add_library("${LIBNAME}" ${LIB_BUILD_TYPE} ${SOURCES})
        target_include_directories("${LIBNAME}" PUBLIC "${INCLUDE_DIR}")
        target_compile_options("${LIBNAME}" PRIVATE ${CUTILS_COMPILE_OPTIONS})
    endif()
endfunction()

option(CUTILS_CLIST "Build clist library" ON)
if (CUTILS_CLIST)
    cutils_add_module("clist" "${CMAKE_CURRENT_LIST_DIR}/clist"
        "clist/clist.c"
    )
endif()
option(CUTILS_CIO "Build cio library" ON)
if (CUTILS_CIO)
    cutils_add_module("cio" "${CMAKE_CURRENT_LIST_DIR}/cio"
        "cio/cio.c"
    )
endif()
option(CUTILS_CARRAY "Build carray library" ON)
if (CUTILS_CARRAY)
    cutils_add_module("carray" "${CMAKE_CURRENT_LIST_DIR}/carray"
        "carray/carray.c"
    )
endif()

if (CUTILS_BUNDLE_LIBS)
    add_library("${PROJECT_NAME}" ${LIB_BUILD_TYPE} ${BUNDLE_SRCS})
    target_include_directories("${PROJECT_NAME}" PUBLIC ${BUNDLE_INCLUDE_DIRS})
    target_compile_options("${PROJECT_NAME}" PRIVATE ${CUTILS_COMPILE_OPTIONS})
endif()

option(CUTILS_TESTS "Build cutils unit tests (only with -DCMAKE_BUILD_TYPE=Debug)" OFF)

# again assuming here that only lib developers are building in debug; users do not need tests for production use i.e. release config.
if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND CUTILS_TESTS)
    enable_testing()
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/deps/googletest")

    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/tests")
endif()

option(CUTILS_DOCS "Build static cutils HTML documentation" OFF)

if (CUTILS_DOCS)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/docs")
endif()
