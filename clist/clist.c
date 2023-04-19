/*
 *   Copyright (c) 2023 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "clist.h"

#include <stdlib.h>

// opaque def for internal list node struct
typedef struct __clistnode_t {
    void *value;

    struct __clistnode_t *next;
    struct __clistnode_t *prev;
} __clistnode_t;

// opaque def for list struct
typedef struct clist_t {
    __clistnode_t *head;
    __clistnode_t *tail;

    unsigned int length;
} clist_t;


/************************************************************************/
/*                           cutils public API                          */
/************************************************************************/

int clistpush(clist_t **dest, void *value) {
    __clistnode_t *node = malloc(sizeof(__clistnode_t));
    if (!node) {
        return 0;
    }

    node->value = value;

    // will be set to 1 if the list was newly alloc'd in this function
    char is_new = 0;

    // direct deref needed for malloc
    if (!(*dest)) {
        if (!((*dest) = malloc(sizeof(clist_t)))) {
            return 0;
        }

        is_new = 1;
    }

    clist_t *list = (*dest);

    if (is_new) {
        list->head = node;
        list->tail = NULL;
        list->length = 0;
    } else {
        if (list->tail) {
            list->tail->next = node;
        }
    }

    node->next = NULL;
    node->prev = list->tail;

    list->tail = node;

    return ++list->length;
}

void *clistpop(clist_t **dest) {
    void *buf = NULL;

    clist_t *list = (*dest);

    if (!list->head) {
        return buf;
    }

    list->length--;

    __clistnode_t *cur_tail = list->tail;
    __clistnode_t *new_tail = (cur_tail)->prev;

    if (list->length <= 0) {
        // detaching final node, i.e. clearing the list ... we can free the list
        free(list);
        (*dest) = NULL; // ensure that *dest is also set to NULL so the list can be 'reused' by the user
    }
    else {
        // still existing nodes: detach current tail from the node before (the new tail)
        new_tail->next = NULL;
        list->tail = new_tail;
    }

    // current tail now detached, will be freed, data to be returned.
    buf = (cur_tail)->value;

    free(cur_tail);
    cur_tail = NULL;

    return buf;
}

void clistfree(clist_t **dest) {
    if (!(*dest)) {
        return;
    }

    // list is silently freed when the last element is detached
    for (unsigned int i = 0; i < (*dest)->length; i++) {
        clistpop(dest);
    }
}
