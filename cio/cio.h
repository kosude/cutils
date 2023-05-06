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

#include <stdio.h>
#include <stdint.h>


/************************************************************************/
/*                           cutils public API                          */
/************************************************************************/

/**
 * A buffer structure to hold a console colour code string. This structure is used to return console colour codes as strings from functions such as
 * ciocol().
 */
typedef struct ciocolbuf_t {
    /**
     * colour code for UNIX systems.
     */
    char code[16];
} ciocolbuf_t;

/**
 * For UNIX systems, return a ciocolbuf_t containing a string holding a colour code that can be printed to an output stream to set the following
 * output colour. For Windows systems, set the current state output colour, and return with an empty string.
 *
 * Pass 0xFF to fg or bg to skip that colour value.
 *
 * @param fg foreground colour (either integer or ciocol_t enum).
 * @param bg background colour (either integer or ciocol_t enum).
 *
 * @return A constant buffer structure with string containing a colour code.
 */
ciocolbuf_t ciocol(
    uint8_t fg,
    uint8_t bg
);

/**
 * For UNIX systems, return a ciocolbuf_t containing a string holding a colour code that can be printed to an output stream to set the following
 * output colour. For Windows systems, set the current state output colour, and return with an empty string.
 *
 * The returned colour code/state update on Windows is the default console output colour.
 *
 * @return A constant buffer structure with string containing a colour code.
 */
ciocolbuf_t ciocoldef();

/**
 * Update the colour used by the terminal emulator for output when writing to the specified stream.
 *
 * Pass 0xFF to fg or bg to skip updating that colour value. If both parameters are specified as 0xff, nothing will happen.
 *
 * @param fg foreground colour (either integer or ciocol_t enum).
 * @param bg background colour (either integer or ciocol_t enum).
 * @param stream NULL (defaults to stdout) or the stream for which to set the output colour.
 */
void ciocolstateset(
    uint8_t fg,
    uint8_t bg,
    FILE *stream
);

/**
 * Set the colour of the output sent to the specified stream to the default value.
 *
 * @param stream NULL (defaults to stdout) or the stream for which to set the output colour.
 */
void ciocolstatedef(
    FILE *stream
);

#ifdef __cplusplus
    }
#endif // __cplusplus
#endif // !__cio_h__
