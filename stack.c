#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

void init(struct Stack *node, size_t elem_size)
{
    node->_value = NULL;
    node->_elem_size = elem_size;
    node->_prev = NULL;

    node->empty = empty;
    node->top = top;
    node->pop = pop;
    node->push = push;
    node->print = print;
    node->clear = clear;
}

int empty(struct Stack *node)
{
    return (node->_prev == NULL) ? 1 : 0;
}

void push(struct Stack *node, const void *value)
{
    struct Stack *new_element = malloc(sizeof *new_element);
    if (!new_element)
        return;

    void *copy = malloc(node->_elem_size);
    if (!copy)
    {
        free(new_element);
        return;
    }
    memcpy(copy, value, node->_elem_size);

    new_element->_value = node->_value;
    new_element->_elem_size = node->_elem_size;
    new_element->_prev = node->_prev;

    node->_value = copy;
    node->_prev = new_element;
}

void top(struct Stack *node, void *out)
{
    if (node->_prev == NULL || !node->_value)
        return;
    memcpy(out, node->_value, node->_elem_size);
}

void pop(struct Stack *node, void *out)
{
    if (node->_prev == NULL)
        return;
    if (out)
        memcpy(out, node->_value, node->_elem_size);
    free(node->_value);

    struct Stack *tmp = node->_prev;
    node->_value = tmp->_value;
    node->_prev = tmp->_prev;
    free(tmp);
}

void print(struct Stack *node, void (*show)(const void *))
{
    int first = 1;
    for (struct Stack *cur = node; cur->_prev != NULL; cur = cur->_prev)
    {
        if (!first)
            printf(" ");
        show(cur->_value);
        first = 0;
    }
    printf("\n");
}

void clear(struct Stack *node)
{
    free(node->_value);
    node->_value = NULL;

    struct Stack *cur = node->_prev;
    while (cur)
    {
        struct Stack *next = cur->_prev;
        free(cur->_value);
        free(cur);
        cur = next;
    }
    node->_prev = NULL;
}