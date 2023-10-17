macro(cutils_add_int_test TESTNAME LIBNAME)
    if (CUTILS_BUNDLE_LIBS)
        set(LIB "${PROJECT_NAME}")
    else()
        set(LIB "${LIBNAME}")
    endif()

    add_executable("${TESTNAME}" "${CMAKE_CURRENT_LIST_DIR}/eg_${TESTNAME}.cpp")
    target_link_libraries("${TESTNAME}" ${LIB})
endmacro()

macro(cutils_add_unit_test TESTNAME LIBNAME)
    if (CUTILS_BUNDLE_LIBS)
        set(LIB "${PROJECT_NAME}")
    else()
        set(LIB "${LIBNAME}")
    endif()

    add_executable("unit_${TESTNAME}" "${CMAKE_CURRENT_LIST_DIR}/unit_${TESTNAME}.cpp")
    target_link_libraries("unit_${TESTNAME}" ${LIB} gtest_main)

    add_test(
        NAME "${TESTNAME}"
        COMMAND "unit_${TESTNAME}"
    )
endmacro()

if (CUTILS_CLIST)
    cutils_add_int_test("str_linked_list" clist)
    cutils_add_int_test("colours" cio)

    cutils_add_unit_test("clist" clist)
    cutils_add_unit_test("carray" carray)
endif()
