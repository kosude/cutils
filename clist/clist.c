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
    clistval_t value;

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

int clistpush(clist_t **dest, clistval_t value) {
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

int clistinsert(clist_t **dest, clistval_t value, unsigned int index) {
    clist_t *list = (*dest);

    if (!list || index == list->length) {
        return clistpush(dest, value);
    }

    __clistnode_t *node = malloc(sizeof(__clistnode_t));
    if (!node) {
        return 0;
    }

    node->value = value;

    // node after the newly inserted node
    __clistnode_t *after_new = clistat(list, index);
    node->next = after_new;
    node->prev = after_new->prev;

    if (after_new->prev) {
        after_new->prev->next = node;
    }
    after_new->prev = node;

    if (after_new == list->head) {
        list->head = node;
    }

    return ++list->length;
}

clistval_t clistpop(clist_t **dest) {
    clistval_t buf = 0;

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
    buf = cur_tail->value;

    free(cur_tail);
    cur_tail = NULL;

    return buf;
}

clistval_t clistremove(clist_t **dest, unsigned int index) {
    clistval_t buf = 0;

    clist_t *list = (*dest);

    __clistnode_t *node = clistat(list, index);

    if (!node) {
        return buf;
    }

    list->length--;

    if (list->length <= 0) {
        // detaching final node, i.e. clearing the list ... we can free the list
        free(list);
        (*dest) = NULL; // ensure that *dest is also set to NULL so the list can be 'reused' by the user
    } else {
        if (node->prev) {
            node->prev->next = node->next;
        }
        if (node->next) {
            node->next->prev = node->prev;
        }
    }

    if (list->head == node) {
        list->head = node->next;
    }
    if (list->tail == node) {
        list->tail = node->prev;
    }

    buf = node->value;

    free(node);
    node = NULL;

    return buf;
}

void clistfree(clist_t **dest) {
    clist_t *list = (*dest);

    if (!list) {
        return;
    }

    // store len in buffer as clistpop() decrements it
    unsigned int lenbuf = list->length;

    // list is silently freed when the last element is detached
    for (unsigned int i = 0; i < lenbuf; i++) {
        clistpop(dest);
    }
}

unsigned int clistlen(clist_t *list) {
    if (!list) {
        return 0;
    }
    return list->length;
}

clistval_t clistget(clist_t *list, unsigned int index) {
    return ((__clistnode_t *) clistat(list, index))->value;
}

clistitr_t clistbegin(clist_t *list) {
    if (!list) {
        return NULL;
    }
    return (clistitr_t) list->head;
}

clistitr_t clistend(clist_t *list) {
    if (!list) {
        return NULL;
    }
    return (clistitr_t) list->tail;
}

clistitr_t clistat(clist_t *list, unsigned int index) {
    if (!list) {
        return NULL;
    }

    __clistnode_t *headptr = list->head;

    for (unsigned int i = 0; i < index && headptr != NULL; i++) {
        headptr = headptr->next;
    }

    return headptr;
}

clistitr_t clistitrnext(clistitr_t it) {
    return (clistitr_t) ((__clistnode_t *) it)->next;
}

clistitr_t clistitrprev(clistitr_t it) {
    return (clistitr_t) ((__clistnode_t *) it)->prev;
}

clistval_t clistitrget(clistitr_t it) {
    return ((__clistnode_t *) it)->value;
}
