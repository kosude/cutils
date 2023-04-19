macro(cutils_add_test TESTNAME LIBNAME)
    add_executable("${TESTNAME}" "${CMAKE_CURRENT_LIST_DIR}/eg_${TESTNAME}.cpp")
    target_link_libraries("${TESTNAME}" ${LIBNAME} gtest_main)

    add_test(
        NAME "${TESTNAME}"
        COMMAND "${TESTNAME}"
    )
endmacro()

if (CUTILS_CLIST)
    cutils_add_test("lists" clist)
endif()
