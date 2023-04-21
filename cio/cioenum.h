/*
 *   Copyright (c) 2023 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __cioenum_h__
#define __cioenum_h__
#ifdef __cplusplus
    extern "C" {
#endif // __cplusplus


/************************************************************************/
/*                           cutils public API                          */
/************************************************************************/

/**
 * An enumerator containing available console output colour options. This type is separately provided by <cioenum.h>.
 */
typedef enum ciocol_t {
    CIOCOL_BLACK =  0x0,
    CIOCOL_DKBLUE =  0x1,
    CIOCOL_DKGREEN =  0x2,
    CIOCOL_LTBLUE =  0x3,
    CIOCOL_DKRED =  0x4,
    CIOCOL_MAGENTA =  0x5,
    CIOCOL_ORANGE =  0x6,
    CIOCOL_LTGREY =  0x7,
    CIOCOL_GREY =  0x8,
    CIOCOL_BLUE =  0x9,
    CIOCOL_GREEN =  0xa,
    CIOCOL_CYAN =  0xb,
    CIOCOL_RED =  0xc,
    CIOCOL_PINK =  0xd,
    CIOCOL_YELLOW =  0xe,
    CIOCOL_WHITE =  0xf,
} ciocol_t;

#ifdef __cplusplus
    }
#endif // __cplusplus
#endif // !__cioenum_h__
