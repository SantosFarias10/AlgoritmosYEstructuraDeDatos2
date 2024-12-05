#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
struct _s_stack {
    stack_elem elem;
    struct _s_stack *next;
};

/* Constructors */

stack stack_empty(void) {
    return NULL;
}

stack stack_push(stack s, stack_elem e) {
    stack p = malloc(sizeof(struct _s_stack));
    p->elem = e;
    p->next = s;
    return p;
}

/* Operations */

stack stack_pop(stack s) {
    if (!stack_is_empty(s)) {
        stack s_aux = s;
        s = s->next;
        free(s_aux);        
    }
    return s;
}

unsigned int stack_size(stack s) {
    unsigned int size = 0u;
    stack s_aux = s;
    while (s_aux != NULL) {
        s_aux = s_aux->next;
        size++;
    }
    return size;
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