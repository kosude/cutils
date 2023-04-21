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

/**
 * An opaque doubly linked list structure. The values stored within a clist_t are of clistval_t type.
 *
 * @note  If a list is empty, its pointer (as it is heap-allocated) is set to NULL. Therefore, you can safely guarantee a list is empty if its handle
 * is equal to NULL.
 */
typedef struct clist_t clist_t;

/**
 * An iterator type for traversing a clist_t list. This type refers to a void pointer; however, in practice, clistitr_t instances point to a
 * node within the list they are iterating. This node structure is not accessible, but its value can be accessed with clistitrget().
 */
typedef void *clistitr_t;

/**
 * The type of data stored within clist_t lists.
 */
typedef intptr_t clistval_t;

/**
 * Push a value to the end of a linked list, returning its new length. If the list is currently empty, necessary memory will be allocated for
 * it within this function.
 *
 * @param dest location of the clist_t pointer to push to.
 * @param value value to push to the list.
 *
 * @return Normally, the new length of the list.
 * @return If there is a memory error when allocating space for the new value, 0 is returned. 0 is never returned otherwise.
 */
int clistpush(
    clist_t **dest,
    clistval_t value
);

/**
 * Insert a value into a linked list at the given index, returning its new length. If the list is currently empty, necessary memory will be
 * allocated for it within this function. The index given refers to the location the new item will be at. For example, if an index of 0 is given, the
 * value is inserted at the beginning of the list.
 *
 * @param dest location of the clist_t pointer to insert into.
 * @param value value to insert into the list.
 * @param index index within the list that the value will be inserted at.
 *
 * @return Normally, the new length of the list.
 * @return If there is a memory error when allocating space for the new value, 0 is returned. 0 is never returned otherwise.
 */
int clistinsert(
    clist_t **dest,
    clistval_t value,
    unsigned int index
);

/**
 * @brief Detach the last value in the given list. The heap-allocated internal copy of the value is freed, and a stack copy of this value is returned.
 *
 * @note If the list is empty after this function call (i.e. the last value is popped), the list is automatically freed, and *dest is set to NULL.
 *
 * @param dest location of the clist_t pointer to pop from.
 *
 * @return The value 'popped off' from (detached from) the end of the list.
 * @return If the list is empty, 0 is returned.
 */
clistval_t clistpop(
    clist_t **dest
);

/**
 * Detach the value at the given index from the list. The heap-allocated internal copy of the value is freed, and a stack copy of this value is
 * returned.
 *
 * @note If the list is empty after this function call (i.e. the last value is removed), the list is automatically freed, and *dest is set to NULL.
 *
 * @param dest location of the clist_t pointer to remove a value from.
 * @param index index of the value to remove from the list.
 *
 * @return The value removed from the list.
 * @return If the list is empty or if the index is outside the range of the list, 0 is returned.
 */
clistval_t clistremove(
    clist_t **dest,
    unsigned int index
);

/**
 * Free memory allocated for the given list. This is equivalent to individually popping each value from the end of the list until it is empty. (*dest)
 * is set to NULL. Re-using the list pointer can be done by simply pushing new values to it again.
 *
 * @param dest location of the clist_t pointer to deallocate/free memory for.
 */
void clistfree(
    clist_t **dest
);

/**
 * Get and return the length of the given list. If the list pointer is NULL, then the list is presumed empty and 0 is returned.
 *
 * @param list the clist_t pointer to get the length of.
 *
 * @return The length of the list.
 */
unsigned int clistlen(
    clist_t *list
);

/**
 * Get and return the value from the list at the given index.
 *
 * @warning If the list is empty, or if the given index is outside the bounds of the list range, similar to an array, a segmentation fault will occur.
 *
 * @param list the clist_t pointer to get the value from.
 * @param index the index of the value to retrieve.
 *
 * @return The value at the specified index within the given list.
 */
clistval_t clistget(
    clist_t *list,
    unsigned int index
);

/**
 * Return an iterator pointing to the first node within the list.
 *
 * @param list the clist_t pointer to iterate.
 *
 * @return An iterator pointing to the first node within the list.
 * @return If the list is empty, NULL is returned.
 */
clistitr_t clistbegin(
    clist_t *list
);

/**
 * Return an iterator pointing to the last node within the list.
 *
 * @param list the clist_t pointer to iterate.
 *
 * @return An iterator pointing to the last node within the list.
 * @return If the list is empty, NULL is returned.
 */
clistitr_t clistend(
    clist_t *list
);

/**
 * Return an iterator pointing to the node at the specified index within the list.
 *
 * @param list the clist_t pointer to iterate.
 * @param index the index of the list node to iterate from.
 *
 * @return An iterator pointing to the node at the specified index within the list.
 * @return If the list is empty, or if the index is outside the bounds of the list range, NULL is returned.
 */
clistitr_t clistat(
    clist_t *list,
    unsigned int index
);

/**
 * Return an iterator pointing to the node after the given iterator.
 *
 * @warning Note that lists are terminated with NULL; this means that advancing from the last node within a list will return NULL. Therefore, ensure
 * that iterator `it` is not NULL, or a segmentation fault will occur.
 *
 * @param it the iterator to advance from.
 *
 * @return An iterator pointing to the list node after the one that `it` is pointing to.
 */
clistitr_t clistitrnext(
    clistitr_t it
);

/**
 * Return an iterator pointing to the node before the given iterator.
 *
 * @warning Note that lists are initiated with NULL; this means that reducing from the first node within a list will return NULL. Therefore, ensure
 * that iterator `it` is not NULL, or a segmentation fault will occur.
 *
 * @param it the iterator to reduce from.
 *
 * @return An iterator pointing to the list node before the one that `it` is pointing to.
 */
clistitr_t clistitrprev(
    clistitr_t it
);

/**
 * Return the value stored in the list at the node pointed to by the given iterator.
 *
 * @warning If iterator `it` is NULL, a segmentation fault will occur.
 *
 * @param it the iterator to read the value from.
 *
 * @return The value held by iterator it.
 */
clistval_t clistitrget(
    clistitr_t it
);

#ifdef __cplusplus
    }
#endif // __cplusplus
#endif // !__clist_h__
