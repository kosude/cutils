add_library("clist" ${LIB_BUILD_TYPE}
    "clist.c"
)

target_include_directories("clist" PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_compile_options("clist" PRIVATE ${CUTILS_COMPILE_OPTIONS})
