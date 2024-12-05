#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

stack stack_empty(void) {
    stack s = malloc(sizeof(struct _s_stack));
    s->elems = NULL;
    s->size = 0u;
    s->capacity = 0u;
    return s;
}

stack stack_push(stack s, stack_elem e) {
    if (s->elems == NULL) {
        s->capacity = 1u;
        s->elems = malloc(sizeof(stack_elem));
    } else if (s->size >= s->capacity) {
            s->capacity = s->capacity * 2u;
            s->elems = realloc(s->elems, sizeof(stack_elem) * s->capacity);
    }
    s->elems[s->size] = e;
    s->size = s->size + 1u;    
    return s;    
}

stack stack_pop(stack s) {
    assert(!stack_is_empty(s));
    s->size = s->size - 1;
    return s;
}

unsigned int stack_size(stack s) {
    return s->size;
}

stack_elem stack_top(stack s) {
    assert(!stack_is_empty(s));
    return s->elems[s->size - 1u];
}

bool stack_is_empty(stack s) {
    return (s->size == 0u);
}

stack_elem *stack_to_array(stack s) {
    if (stack_is_empty(s)) {
        return NULL;
    }
    return s->elems;
}

stack stack_destroy(stack s) {
    free(s->elems);
    s->elems = NULL;
    free(s);
    s = NULL;
    return s;
}