/*
 *   Copyright (c) 2023 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "carray.h"

#include <stdlib.h>

uint32_t __carray_expand_factor(uint32_t cap) {
    // DON'T CHANGE THIS! I don't know why, but for some reason changing this value makes a completely different part of the program crash. :)
    return (cap * 1.5) + 1;
}
uint32_t __carray_shrink_factor(uint32_t cap) {
    return cap / 2;
}

uint32_t __carray_expand(carray_t *arr) {
    uint32_t temp_cap = __carray_expand_factor(arr->capacity);
    carrayval_t *temp = realloc(arr->data, sizeof(carrayval_t) * temp_cap); // realloc() retains data: https://stackoverflow.com/a/9142813/12980669

    // 0 is returned if there was a memory allocation error - arr not changed, no data lost
    if (!temp) {
        return 0;
    }

    arr->capacity = temp_cap;
    arr->data = temp;

    return 1;
}
uint32_t __carray_shrink(carray_t *arr) {
    if (arr->capacity <= 1) {
        return 1;
    }

    uint32_t temp_cap = __carray_shrink_factor(arr->capacity);
    carrayval_t *temp = realloc(arr->data, sizeof(carrayval_t) * temp_cap); // realloc() retains data: https://stackoverflow.com/a/9142813/12980669

    // 0 is returned if there was a memory allocation error - arr not changed, no data lost
    if (!temp) {
        return 0;
    }

    arr->capacity = temp_cap;
    arr->data = temp;

    return 1;
}


/************************************************************************/
/*                           cutils public API                          */
/************************************************************************/

carray_t carraynew(uint32_t cap) {
    // min clamp to 1
    uint32_t c = (cap > 0) ? cap : 1;

    // we return with a capacity of 0 if there was a memory allocation error
    carrayval_t *data = malloc(sizeof(carrayval_t) * cap);
    if (!data) {
        c = 0;
    }

    return (carray_t) {
        .data = data,
        .capacity = c,
        .size = 0
    };
}

uint32_t carraypush(carray_t *arr, carrayval_t value) {
    // using the last allocated space
    if (arr->size == arr->capacity) {
        // expand
        if (!__carray_expand(arr)) {
            return 0;
        }
    }

    arr->data[arr->size++] = value;

    return arr->size;
}

uint32_t carrayinsert(carray_t *arr, carrayval_t value, uint32_t index) {
    // using the last allocated space
    if (arr->size == arr->capacity) {
        // expand
        if (!__carray_expand(arr)) {
            return 0;
        }
    }

    // shift all following elements to the right
    for (uint32_t i = arr->size; i > index; i--) {
        arr->data[i] = arr->data[i - 1];
    }

    arr->data[index] = value;

    return ++arr->size;
}

carrayval_t carraypop(carray_t *arr) {
    carrayval_t ret = 0;

    // no elements
    if (arr->size <= 0) {
        carrayfree(arr);
        return 0;
    }

    ret = arr->data[--arr->size];

    // removed final element
    if (arr->size <= 0) {
        carrayfree(arr);
        return ret;
    }

    // other element(s) remaining after pop: shrink when possible
    if ((4 * arr->size) < arr->capacity) {
        if (!__carray_shrink(arr)) {
            return 0;
        }
    }

    return ret;
}

carrayval_t carrayremove(carray_t *arr, uint32_t index) {
    // last value
    if (index >= arr->size - 1) {
        return carraypop(arr);
    }

    carrayval_t ret = arr->data[index];

    // shift all following elements to the left
    for (uint32_t i = index + 1; i < arr->size; i++) {
        arr->data[i - 1] = arr->data[i];
    }

    arr->size--;

    // other element(s) remaining after pop: shrink when possible
    if ((4 * arr->size) < arr->capacity) {
        if (__carray_shrink(arr)) {
            return 0;
        }
    }

    return ret;
}

void carrayfree(carray_t *arr) {
    free(arr->data);
    arr->data = NULL;

    arr->capacity = 0;
    arr->size = 0;
}
