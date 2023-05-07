/*
 *   Copyright (c) 2023 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include <gtest/gtest.h>

#include "carray.h"

const static std::vector<int> __default_array_vals = { 87, 23, 10, 93, 6, 9, 102, 583, 93, 55, 21 };

TEST(modifying, creation) {
    carray_t a = carraynew(__default_array_vals.size());
    ASSERT_EQ(a.capacity, __default_array_vals.size());
    ASSERT_EQ(a.size, 0);

    carrayfree(&a);
}

TEST(modifying, pushing_and_inserting) {
    carray_t a = carraynew(1);

    ASSERT_EQ(carraypush(&a, 10), 1);
    ASSERT_EQ(carraypush(&a, 55), 2);
    ASSERT_EQ(carraypush(&a, 74), 3);

    ASSERT_EQ(carrayinsert(&a, 46, 0), 4);
    ASSERT_EQ(carrayinsert(&a, 20, 3), 5);
    ASSERT_EQ(carrayinsert(&a, 99, 2), 6);

    ASSERT_EQ(a.data[0], 46);
    ASSERT_EQ(a.data[1], 10);
    ASSERT_EQ(a.data[2], 99);
    ASSERT_EQ(a.data[3], 55);
    ASSERT_EQ(a.data[4], 20);
    ASSERT_EQ(a.data[5], 74);

    carrayfree(&a);
}

TEST(modifying, popping_and_removing) {
    carray_t a = carraynew(1);

    ASSERT_EQ(carraypop(&a), 0);

    for (unsigned int i = 0; i < __default_array_vals.size(); i++) {
        ASSERT_EQ(carraypush(&a, __default_array_vals[i]), i + 1);
    }

    ASSERT_EQ(carraypop(&a), 21);
    ASSERT_EQ(carraypop(&a), 55);
    ASSERT_EQ(carraypop(&a), 93);

    ASSERT_EQ(carrayremove(&a, 0), 87);
    ASSERT_EQ(carrayremove(&a, 2), 93);
    ASSERT_EQ(carrayremove(&a, 5), 583);

    ASSERT_EQ(a.data[0], 23);
    ASSERT_EQ(a.data[1], 10);
    ASSERT_EQ(a.data[2], 6);
    ASSERT_EQ(a.data[3], 9);
    ASSERT_EQ(a.data[4], 102);

    carrayfree(&a);
}

TEST(error_checking, memory_errors) {
    // out of memory exception (capacity is unsigned, so -1 overflows to uint max)
    carray_t a = carraynew(-1);
    ASSERT_EQ(a.capacity, 0);

    // no memory errors, 3 void*-size spaces successfully allocated
    carray_t b = carraynew(3);
    ASSERT_EQ(b.capacity, 3);

    for (unsigned int i = 0; i < 150; i++) {
        ASSERT_EQ(carraypush(&b, i), i + 1);
        ASSERT_EQ(b.data[i], i);
    }

    // allocating 0 bytes is u.b., so carray prohibits it -- capacity is clamped to 1.
    carray_t c = carraynew(0);
    ASSERT_EQ(c.capacity, 1);

    // remember to note that the size is not the same as the capacity, and it can be 0.
    ASSERT_EQ(c.size, 0);

    // as array a encountered a memory error, no memory was allocated, so it doesn't need to be freed.
    // however, doing so won't result in any errors:
    carrayfree(&a);
    carrayfree(&b);
    carrayfree(&c);
}

TEST(benchmark, large_array) {
    carray_t array = carraynew(1);

    for (unsigned int i = 0; i < 999999; i++) {
        carraypush(&array, i);
        ASSERT_EQ(array.data[i], i);
    }

    std::cout << "Large array size " << array.size << ", capacity " << array.capacity << std::endl;

    carrayfree(&array);
}
