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
    ciocolset(CIOCOL_GREEN, 0xff, nullptr);

    std::cout << "Hello world" << std::endl;

    ciocoldef(nullptr);
}
