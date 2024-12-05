#include <stdlib.h>
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
    assert(s == NULL || s->size == stack_size(s));
    stack p = malloc(sizeof(struct _s_stack));
    p->elem = e;
    p->next = s;

    if (stack_is_empty(s)) {
        p->size = 1u;
    } else {
        p->size = s->size + 1u;
    }
    assert(p->size == stack_size(p));
    return p;
}

/* Operations */

stack stack_pop(stack s) {
    assert(!stack_is_empty(s));
    assert(s->size == stack_size(s));
    stack s_aux = s;
    s = s->next;
    if (!stack_is_empty(s)) {
        s->size = s->size - 1;
    }
    free(s_aux);
    assert(s == NULL || s->size == stack_size(s));
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
    stack_elem *arr;
    stack s_aux = s;
    unsigned int size = stack_size(s);
    int contador = size - 1;

    if (size == 0) {
        arr = NULL;
    } else {
        arr = malloc(sizeof(stack_elem) * size);
    }
    
    while (s_aux != NULL) {
        arr[contador] = s_aux->elem;
        s_aux = s_aux->next;
        contador--;
    }
    stack_destroy(s_aux);
    return arr;
}

stack stack_destroy(stack s) {
    stack s_aux = stack_empty();
    while (!stack_is_empty(s)) {
        s_aux = s;
        s = s->next;
        free(s_aux);
    }
    return s;
}