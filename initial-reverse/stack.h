/**
 * A linked list based stack of char *
 */

#ifndef STACK_H
#define STACK_H

typedef struct Stack Stack;

// Linked List based implementation of stack of char *
struct Stack
{
    char *buf;
    Stack *next;
};

void push(Stack **headptr, char *buf);

char *pop(Stack **headptr);

void *mmalloc(size_t size);

#endif // STACK_H