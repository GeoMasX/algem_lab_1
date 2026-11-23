#ifndef STACK_H
#define STACK_H

#include <stddef.h>

struct Stack
{
    void *_value;      /* копия текущего элемента (владеет стек) */
    size_t _elem_size; /* размер одного элемента в байтах */
    struct Stack *_prev;

    int (*empty)(struct Stack *);
    void (*top)(struct Stack *, void *out);
    void (*pop)(struct Stack *, void *out);
    void (*push)(struct Stack *, const void *value);
    void (*print)(struct Stack *, void (*show)(const void *));
    void (*clear)(struct Stack *);
};

void init(struct Stack *node, size_t elem_size);
int empty(struct Stack *node);
void top(struct Stack *node, void *out);
void pop(struct Stack *node, void *out);
void push(struct Stack *node, const void *value);
void print(struct Stack *node, void (*show)(const void *));
void clear(struct Stack *node);

#endif