/*
 *   Copyright (c) 2023 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include <gtest/gtest.h>

#include "clist.h"

const static std::vector<int> __default_list_vals = { 23, 12, 54, 6, 29, 69, 99, 0, 1, 423, 104, 293 };

static clist_t *__default_list() {
    clist_t *list = nullptr;

    for (int val : __default_list_vals) {
        clistpush(&list, (clistval_t) val);
    }

    return list;
}

static void __print_list(clist_t *list) {
    std::cout << "Post-test list state: [ ";

    for (clistitr_t it = clistbegin(list); it != nullptr; it = clistitrnext(it)) {
        std::cout << std::to_string(clistitrget(it));

        if (clistitrnext(it)) {
            std::cout << ", ";
        } else {
            std::cout << " ";
        }
    }

    std::cout << "]" << std::endl;
}

TEST(modifying, pushing_and_inserting) {
    clist_t *list = nullptr;

    ASSERT_EQ(clistpush(&list, 77), 1);
    ASSERT_EQ(clistpush(&list, 12), 2);
    ASSERT_EQ(clistpush(&list, 35), 3);
    ASSERT_EQ(clistpush(&list, 120), 4);

    ASSERT_EQ(clistinsert(&list, 81, 0), 5);
    ASSERT_EQ(clistinsert(&list, 52, 5), 6);
    ASSERT_EQ(clistinsert(&list, 99, 3), 7);
    ASSERT_EQ(clistinsert(&list, 26, 2), 8);

    __print_list(list);
    clistfree(&list);
}

TEST(modifying, copy_list_from_array) {
    clist_t *list = __default_list();

    for (unsigned int i = 0; i < __default_list_vals.size(); i++) {
        ASSERT_EQ(clistget(list, i), __default_list_vals[i]);
    }

    __print_list(list);
    clistfree(&list);
}

TEST(modifying, popping_and_removing) {
    clist_t *list = __default_list();

    ASSERT_EQ(clistpop(&list), 293);
    ASSERT_EQ(clistpop(&list), 104);
    ASSERT_EQ(clistpop(&list), 423);
    ASSERT_EQ(clistpop(&list), 1);

    ASSERT_EQ(clistremove(&list, 0), 23);
    ASSERT_EQ(clistremove(&list, 4), 69);
    ASSERT_EQ(clistremove(&list, 2), 6);
    ASSERT_EQ(clistremove(&list, 4), 0);

    __print_list(list);
    clistfree(&list);
}

TEST(modifying, index_of) {
    clist_t *list = __default_list();

    // it is not possible to have an 'indexof' function in clist due to the unknown possibility of having to check for string equality
    // instead of normal equality for a node value match. therefore, lib users must perform this check themselves, knowing what type of data is being
    // stored in the list.
    unsigned int i = 0;
    for (clistitr_t it = clistbegin(list); it != nullptr; it = clistitrnext(it), i++) {
        if (clistitrget(it) == 54) {
            it = clistitrprev(it);
            ASSERT_EQ(clistremove(&list, i), 54);
            i--;
        }

        if (clistitrget(it) == 423) {
            it = clistitrprev(it);
            ASSERT_EQ(clistremove(&list, i), 423);
            i--;
        }

        if (clistitrget(it) == 99) {
            it = clistitrprev(it);
            ASSERT_EQ(clistremove(&list, i), 99);
            i--;
        }

        if (clistitrget(it) == 99) {
            it = clistitrprev(it);
            ASSERT_EQ(clistremove(&list, i), 0);
            i--;
        }
    }

    __print_list(list);
    clistfree(&list);
}

TEST(iteration, with_iterator) {
    std::vector<int> vals1 = { 59, 24, 20 };
    std::vector<int> vals2 = { 59, 49, 76 };

    clist_t *list = nullptr;

    // recreating vals1 vector in a clist_t
    clistpush(&list, 59);
    clistpush(&list, 24);
    clistpush(&list, 20);

    unsigned int i = 0;

    for (clistitr_t it = clistbegin(list); it != nullptr; it = clistitrnext(it), i++) {
        ASSERT_EQ(clistitrget(it), vals1[i]);
    }

    // modifying the clist_t struct to be the same as the vals2 vector
    clistpop(&list);
    clistpop(&list);
    clistpush(&list, 49);
    clistpush(&list, 76);

    i = 0;

    for (clistitr_t it = clistbegin(list); it != nullptr; it = clistitrnext(it), i++) {
        ASSERT_EQ(clistitrget(it), vals2[i]);
    }

    __print_list(list);
    clistfree(&list);
}

TEST(iteration, with_index) {
    std::vector<int> vals1 = { 59, 24, 20 };
    std::vector<int> vals2 = { 59, 49, 76 };

    clist_t *list = nullptr;

    // recreating vals1 vector in a clist_t
    clistpush(&list, 59);
    clistpush(&list, 24);
    clistpush(&list, 20);

    for (unsigned int i = 0; i < 3; i++) {
        ASSERT_EQ(clistget(list, i), vals1[i]);
    }

    // modifying the clist_t struct to be the same as the vals2 vector
    clistpop(&list);
    clistpop(&list);
    clistpush(&list, 49);
    clistpush(&list, 76);

    for (unsigned int i = 0; i < 3; i++) {
        ASSERT_EQ(clistget(list, i), vals2[i]);
    }

    __print_list(list);
    clistfree(&list);
}

TEST(benchmark, large_list) {
    clist_t *list = nullptr;

    for (unsigned int i = 0; i < 9999999; i++) {
        clistpush(&list, i);
    }

    clistinsert(&list, 0, 9823944);

    clistfree(&list);
}
