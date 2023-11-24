/**
 * A linked list based stack of char *
 */

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

void push(Stack **headptr, char *buf)
{
    Stack *item = (Stack *)mmalloc(sizeof(Stack));
    item->buf = buf;
    item->next = *headptr;
    *headptr = item;
}

char *pop(Stack **headptr)
{
    if (*headptr == NULL)
        return NULL;
    Stack *item = *headptr;
    *headptr = item->next;
    char *buf = item->buf;
    free(item);
    return buf;
}

void *mmalloc(size_t size)
{
    void *item = malloc(size);
    if (item)
        return item;
    fprintf(stderr, "malloc failed\n");
    exit(1);
}