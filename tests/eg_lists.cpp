/*
 *   Copyright (c) 2023 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include <gtest/gtest.h>

#include "clist.h"

int __ptoi(void *ptr) {
    return static_cast<int>(reinterpret_cast<std::uintptr_t>(ptr));
}

TEST(lists, list_creation) {
    clist_t *list = NULL;

    ASSERT_EQ(clistpush(&list, (void *) 77), 1);
    ASSERT_EQ(clistpush(&list, (void *) 12), 2);
    ASSERT_EQ(clistpush(&list, (void *) 35), 3);

    ASSERT_EQ(__ptoi(clistpop(&list)), 35);
    ASSERT_EQ(__ptoi(clistpop(&list)), 12);
    ASSERT_EQ(__ptoi(clistpop(&list)), 77);

    ASSERT_EQ(clistpush(&list, (void *) 235), 1);
    ASSERT_EQ(clistpush(&list, (void *) 120), 2);

    ASSERT_EQ(__ptoi(clistpop(&list)), 120);
    ASSERT_EQ(__ptoi(clistpop(&list)), 235);

    clistfree(&list);
}
