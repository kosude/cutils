/*
 *   Copyright (c) 2023 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __cio_h__
#define __cio_h__
#ifdef __cplusplus
    extern "C" {
#endif // __cplusplus

#include <stdint.h>

typedef struct _IO_FILE FILE;


/************************************************************************/
/*                           cutils public API                          */
/************************************************************************/

void ciocolset(
    uint8_t fg,
    uint8_t bg,
    FILE *stream
);

void ciocoldef(
    FILE *stream
);

#ifdef __cplusplus
    }
#endif // __cplusplus
#endif // !__cio_h__
