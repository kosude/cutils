/*
 *   Copyright (c) 2023 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "cio.h"
#include "cioenum.h"

#include <iostream>

int main() {
    std::cout << ciocol(CIOCOL_RED, 0xff).code << "Hello world" << ciocoldef().code << std::endl;
}
