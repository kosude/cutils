/*
 *   Copyright (c) 2023 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "clist.h"

int main() {
    clist_t *list = nullptr;

    std::cout << "Enter strings to add to the list (specify \"end\" to end):" << std::endl;

    std::string x;

    while (x != "end") {
        std::cin >> x;

        char *strval = (char *) malloc(sizeof(char) * (x.length() + 1));
        memset(strval, 0, sizeof(char) * (x.length() + 1));
        strncpy(strval, x.c_str(), x.length());

        clistpush(&list, (intptr_t) strval);
    }

    std::cout << std::endl << "List entries:" << std::endl;

    unsigned int i = 0;
    for (clistitr_t it = clistbegin(list); it != nullptr; it = clistitrnext(it), i++) {
        std::cout << " - " << std::to_string(i) << ": " << (const char *) clistitrget(it) << std::endl;

        free((void *) clistitrget(it));
    }

    clistfree(&list);

    return 0;
}
