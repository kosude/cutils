/*
 *   Copyright (c) 2023 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __clist_h__
#define __clist_h__
#ifdef __cplusplus
    extern "C" {
#endif // __cplusplus


/************************************************************************/
/*                           cutils public API                          */
/************************************************************************/

typedef struct clist_t clist_t;

int clistpush(
    clist_t **dest,
    void *value
);

void *clistpop(
    clist_t **dest
);

void clistfree(
    clist_t **dest
);

#ifdef __cplusplus
    }
#endif // __cplusplus
#endif // !__clist_h__
