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

typedef intptr_t clistval_t;

typedef struct carray_t {
    clistval_t *data;
    uint32_t capacity;
    uint32_t size;
} carray_t;

carray_t carraynew(
    uint32_t cap
);

uint32_t carraypush(
    carray_t *arr,
    clistval_t value
);

uint32_t carrayinsert(
    carray_t *arr,
    clistval_t value,
    uint32_t index
);

clistval_t carraypop(
    carray_t *arr
);

clistval_t carrayremove(
    carray_t *arr,
    uint32_t index
);

void carrayfree(
    carray_t *arr
);

#ifdef __cplusplus
    }
#endif // __cplusplus
#endif // !__carray_h__
