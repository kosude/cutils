cmake_minimum_required(VERSION 3.10)

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

option(CUTILS_CLIST "Build clist library" ON)
if (CUTILS_CLIST)
    add_library("clist" ${LIB_BUILD_TYPE}
        "clist/clist.c"
    )

    target_include_directories("clist" PUBLIC "${CMAKE_CURRENT_LIST_DIR}/clist")
    target_compile_options("clist" PRIVATE ${CUTILS_COMPILE_OPTIONS})
endif()

option(CUTILS_CIO "Build cio library" ON)
if (CUTILS_CIO)
    add_library("cio" ${LIB_BUILD_TYPE}
        "cio/cio.c"
    )

    target_include_directories("cio" PUBLIC "${CMAKE_CURRENT_LIST_DIR}/cio")
    target_compile_options("cio" PRIVATE ${CUTILS_COMPILE_OPTIONS})
endif()

option(CUTILS_CARRAY "Build carray library" ON)
if (CUTILS_CARRAY)
    add_library("carray" ${LIB_BUILD_TYPE}
        "carray/carray.c"
    )

    target_include_directories("carray" PUBLIC "${CMAKE_CURRENT_LIST_DIR}/carray")
    target_compile_options("carray" PRIVATE ${CUTILS_COMPILE_OPTIONS})
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
