/*
 *   Copyright (c) 2023 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "cio.h"

#if defined(_WIN32)
#   define WIN32_LEAN_AND_MEAN
#   include <Windows.h>
#else
#   include <stdio.h>
#   include <string.h>
#endif

#if defined(__unix__) || defined(__unix)
    static const char *__getfgcode(uint8_t fg) {
        // Courtesy of ProjectPhysX on StackOverflow
        switch(fg) {
            case  0: return "30";
            case  1: return "34";
            case  2: return "32";
            case  3: return "36";
            case  4: return "31";
            case  5: return "35";
            case  6: return "33";
            case  7: return "37";
            case  8: return "90";
            case  9: return "94";
            case 10: return "92";
            case 11: return "96";
            case 12: return "91";
            case 13: return "95";
            case 14: return "93";
            case 15: return "97";
            default: return "37"; // 37 (light grey) is default
        };
    }

    static const char *__getbgcode(uint8_t bg) {
        // Courtesy of ProjectPhysX on StackOverflow
        switch(bg) {
            case  0: return  "40";
            case  1: return  "44";
            case  2: return  "42";
            case  3: return  "46";
            case  4: return  "41";
            case  5: return  "45";
            case  6: return  "43";
            case  7: return  "47";
            case  8: return "100";
            case  9: return "104";
            case 10: return "102";
            case 11: return "106";
            case 12: return "101";
            case 13: return "105";
            case 14: return "103";
            case 15: return "107";
            default: return  "40"; // 40 (black) is default
        };
    }
#endif

ciocolbuf_t ciocol(uint8_t fg, uint8_t bg) {
#   if defined(_WIN32)
        ciocolstateset(fg, bg, NULL);
        return (ciocolbuf_t) { "" };
#   endif

    ciocolbuf_t buf = { 0 };
    snprintf(buf.code, 15,
        "\033[%s%s%sm",
        (fg != 0xFF) ? __getfgcode(fg) : "0",
        (bg != 0xFF) ? ";" : "",
        (bg != 0xFF) ? __getbgcode(bg) : ""
    );
    return buf;
}

ciocolbuf_t ciocoldef() {
#   if defined(_WIN32)
        ciocolstatedef(NULL);
        return (ciocolbuf_t) { "" };
#   endif

    ciocolbuf_t buf = { 0 };
    snprintf(buf.code, 15, "\033[0m");
    return buf;
}

void ciocolstateset(uint8_t fg, uint8_t bg, FILE *stream) {
    if (fg == 0xFF && bg == 0xFF) {
        // no values given
        return;
    }

    if (!stream) {
        stream = stdout;
    }

#   if defined(_WIN32)
        // TODO: pls test

        unsigned int colourAttribute = 0;

        if (fg != 0xFF && bg != 0xFF) {
            // both values are given
            colourAttribute = bg << 4 | fg;
        } else if (fg != 0xFF && bg == 0xFF) {
            // only fg is given
            colourAttribute = fg;
        } else {
            // only bg is given
            colourAttribute = bg << 4;
        }

        static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, bg << 4 | fg);
#   elif defined(__unix__) || defined(__unix)
        fprintf(stream, ciocol(fg, bg).code);
#   endif
}

void ciocolstatedef(FILE *stream) {
    if (!stream) {
        stream = stdout;
    }

#   if defined(_WIN32)
        // TODO: pls test
        static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, 7);
#   elif defined(__unix__) || defined(__unix)
        fprintf(stream, ciocoldef().code);
#   endif
}
