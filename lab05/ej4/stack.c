#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "stack.h"
 
struct _s_stack {
    stack_elem elem;
    struct _s_stack *next;
    unsigned int size;
};

/* Constructors */

stack stack_empty(void) {
    return NULL;
}

stack stack_push(stack s, stack_elem e) {
    stack p = malloc(sizeof(struct _s_stack));

    p->elem = e;
    p->next = s;
    p->size = stack_size(s) + 1u;

    return p;
}

/* Operations */

stack stack_pop(stack s) {
    
    stack s_aux = s;
    s = s->next;
    free(s_aux);
    
    return s;
}

unsigned int stack_size(stack s) {
    if (stack_is_empty(s)) {
        return 0u;
    }
    return s->size;
}

stack_elem stack_top(stack s) {
    assert(!stack_is_empty(s));
    return s->elem;
}

bool stack_is_empty(stack s) {
    return (s == NULL);
}

stack_elem *stack_to_array(stack s) {
    stack_elem *arr = NULL;
    stack s_aux = s;

    if (!stack_is_empty(s)) {
        arr = calloc(stack_size(s), sizeof(stack_elem));
        
        for (unsigned int i = stack_size(s); i > 0u; --i) {
            arr[i - 1u] = s_aux->elem;
            s_aux = s_aux->next;
        }
    }

    return arr;
}

stack stack_destroy(stack s) {
    stack s_aux = s;
    
    while (!stack_is_empty(s_aux)) {
        s_aux = stack_pop(s_aux);
    }
    return NULL;
}