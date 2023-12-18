/*
 *   Copyright (c) 2023 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __carray_h__
#define __carray_h__
#ifdef __cplusplus
    extern "C" {
#endif // __cplusplus

#include <stdint.h>


/************************************************************************/
/*                           cutils public API                          */
/************************************************************************/

/**
 * The type of data stored within carray_t arrays.
 */
typedef intptr_t carrayval_t;

/**
 * A structure representing a dynamically resizable array.
 *
 * To check if a carray_t is empty, check the size, not the capacity. The capacity will always be at least 1 in most cases - usually, it is larger
 * than the size. When the array is resized (i.e. when it is added to and the size exceeds the capacity), its capacity is increased by a multiplier
 * of 1.5, and a constant of 1 is added.
 */
typedef struct carray_t {
    /**
     * the array of data (stored as carrayval_t type)
     */
    carrayval_t *data;
    /**
     * the allocated size of array data.
     */
    uint32_t capacity;
    /**
     * the defined, accessible length of array data.
     */
    uint32_t size;
} carray_t;

/**
 * Populate a carray_t struct and return it on the stack.
 *
 * The array is clamped to a minimum capacity of 1, for memory allocation purposes. Therefore, if 0 is passed to the cap parameter, the array will be
 * initialised with a capacity of 1. There will be no data set, however, and so the length is 0 (regardless of the value passed to cap).
 *
 * The array structure is stack-allocated, but the data member of the array (the actual array of data) is on the heap.
 *
 * @param cap the initial capacity of the array.
 *
 * @return Normally, the new stack-allocated array.
 * @return If there was a memory allocation error, the capacity member of the array will be 0. Otherwise, the capacity is always at least 1.
 */
carray_t carraynew(
    uint32_t cap
);

/**
 * Append the given value onto the end of array arr.
 *
 * In cases where the new length of the array exceeds its capacity, it will be resized by a certain factor and additional constant. See the
 * documentation for carray_t for more information.
 *
 * @param arr the array to manipulate.
 * @param value the value to push onto the end of the array.
 *
 * @return Normally, the new length of the array.
 * @return If the array had to be expanded in capacity and there was a memory error, 0 is returned.
 */
uint32_t carraypush(
    carray_t *arr,
    carrayval_t value
);

/**
 * Insert the given value into array arr at the given index. The new value will be accessible at that index. In cases where the new length of the
 * array exceeds its capacity, it will be resized by a certain factor and additional constant. See the documentation for carray_t for more
 * information.
 *
 * @param arr the array to manipulate.
 * @param value the value to insert into the array.
 * @param index the index at which to insert the given value.
 *
 * @return Normally, the new length of the array.
 * @return If the array had to be expanded in capacity and there was a memory error, 0 is returned.
 */
uint32_t carrayinsert(
    carray_t *arr,
    carrayval_t value,
    uint32_t index
);

/**
 * Remove ('pop') the last value from the end of the given array arr and return it. If the new length of the array is less than a quarter of the
 * array's capacity, the array's allocated memory is shrunk by half in order to avoid using empty space.
 *
 * @note If the array is empty when this function is called, or as the result of this function, any remaining capacity is freed and the array's data
 * is set to NULL. The array can still be used as normal, and explicitly free'ing it is still fine to do.
 *
 * @param arr the array to manipulate.
 *
 * @return The value popped from the end of the array.
 * @return If the array was shrunk in capacity and there was a memory error, 0 is returned. 0 is also returned if the array is empty.
 */
carrayval_t carraypop(
    carray_t *arr
);

/**
 * Remove the value at index from the given array arr and return it. If the new length of the array is less than a quarter of the array's capacity,
 * the array's allocated memory is shrunk by half in order to avoid using empty space.
 *
 * @note If the array is empty when this function is called, or as the result of this function, any remaining capacity is freed and the array's data
 * is set to NULL. The array can still be used as normal, and explicitly free'ing it is still fine to do.
 *
 * @param arr the array to manipulate.
 * @param index the index of the value to remove from the array.
 *
 * @return The value removed from the array.
 * @return If the array was shrunk in capacity and there was a memory error, 0 is returned. 0 is also returned if the array is empty.
 */
carrayval_t carrayremove(
    carray_t *arr,
    uint32_t index
);

/**
 * Free memory allocated for the array data.
 *
 * @param arr the array to deallocate memory from.
 */
void carrayfree(
    carray_t *arr
);

#ifdef __cplusplus
    }
#endif // __cplusplus
#endif // !__carray_h__
