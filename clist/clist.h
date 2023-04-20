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

#include <stdint.h>


/************************************************************************/
/*                           cutils public API                          */
/************************************************************************/

typedef struct clist_t clist_t;
typedef void *clistitr_t;
typedef intptr_t clistval_t;

int clistpush(
    clist_t **dest,
    clistval_t value
);

int clistinsert(
    clist_t **dest,
    clistval_t value,
    unsigned int index
);

clistval_t clistpop(
    clist_t **dest
);

clistval_t clistremove(
    clist_t **dest,
    unsigned int index
);

void clistfree(
    clist_t **dest
);

unsigned int clistlen(
    clist_t *list
);

clistval_t clistget(
    clist_t *list,
    unsigned int index
);

clistitr_t clistbegin(
    clist_t *list
);

clistitr_t clistend(
    clist_t *list
);

clistitr_t clistat(
    clist_t *list,
    unsigned int index
);

clistitr_t clistitrnext(
    clistitr_t it
);

clistitr_t clistitrprev(
    clistitr_t it
);

clistval_t clistitrget(
    clistitr_t it
);

#ifdef __cplusplus
    }
#endif // __cplusplus
#endif // !__clist_h__
