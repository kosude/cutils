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
    clist_t *list = NULL;

    for (int val : __default_list_vals) {
        clistpush(&list, (clistval_t) val);
    }

    return list;
}

TEST(modifying, list_creation) {
    clist_t *list = NULL;

    ASSERT_EQ(clistpush(&list, 77), 1);
    ASSERT_EQ(clistpush(&list, 12), 2);
    ASSERT_EQ(clistpush(&list, 35), 3);

    ASSERT_EQ(clistpop(&list), 35);

    ASSERT_EQ(clistpush(&list, 235), 3);

    ASSERT_EQ(clistpop(&list), 235);
    ASSERT_EQ(clistpop(&list), 12);

    ASSERT_EQ(clistpush(&list, 120), 2);

    clistfree(&list);
}

TEST(modifying, copy_list_from_array) {
    clist_t *list = __default_list();

    for (unsigned int i = 0; i < __default_list_vals.size(); i++) {
        ASSERT_EQ(clistget(list, i), __default_list_vals[i]);
    }
}

TEST(iteration, with_iterator) {
    std::vector<int> vals1 = { 59, 24, 20 };
    std::vector<int> vals2 = { 59, 49, 76 };

    clist_t *list = NULL;

    // recreating vals1 vector in a clist_t
    clistpush(&list, 59);
    clistpush(&list, 24);
    clistpush(&list, 20);

    unsigned int i = 0;

    for (clistiter_t it = clistbegin(list); it != NULL; it = clistitrnext(it), i++) {
        ASSERT_EQ(clistitrget(it), vals1[i]);
    }

    // modifying the clist_t struct to be the same as the vals2 vector
    clistpop(&list);
    clistpop(&list);
    clistpush(&list, 49);
    clistpush(&list, 76);

    i = 0;

    for (clistiter_t it = clistbegin(list); it != NULL; it = clistitrnext(it), i++) {
        ASSERT_EQ(clistitrget(it), vals2[i]);
    }
}

TEST(iteration, with_index) {
    std::vector<int> vals1 = { 59, 24, 20 };
    std::vector<int> vals2 = { 59, 49, 76 };

    clist_t *list = NULL;

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
}

TEST(benchmark, large_list) {
    clist_t *list = NULL;

    for (unsigned int i = 0; i < 999999; i++) {
        ASSERT_EQ(clistpush(&list, i), i + 1);
    }
}
