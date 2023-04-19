add_library("clist" ${LIB_BUILD_TYPE} "clist/clist.c")

target_include_directories("clist" PUBLIC "clist/")
target_compile_options("clist" PRIVATE ${CUTILS_COMPILE_OPTIONS})
