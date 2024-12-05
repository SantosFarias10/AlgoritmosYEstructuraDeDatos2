#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define CHUNK_CAPACITY 5

struct s_node {
    stack_elem datos[CHUNK_CAPACITY];
    size_t used;
    struct s_node *next;
};

struct _s_stack {
    struct s_node *top;
    size_t size;
};

static bool
valid_chunks(stack s) {
    bool valid=true;
    struct s_node *check=s->top;
    if (check!=NULL) {  // Si la pila no está vacía
        while(check != NULL){   // Recorro todos los nodos de la pila
            if(check->used == 0){    // Si el nodo no tiene ningun elemento
                return false;   // La pila no es válida
            }
            check = check->next;
        }
        check = s->top; // Vuelvo a apuntar al primer nodo
        while(check->next != NULL){ // Recorro todos los nodos de la pila
            if(check->next->used > CHUNK_CAPACITY){ // Si el nodo siguiente tiene más elementos de los que debería
                return false;   // La pila no es válida
            }
            check = check->next;
        }
    }

    return valid;
}

static bool
invrep(stack s) {
    return (s!=NULL && valid_chunks(s));
}

static struct s_node *
create_node(void) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));

    new_node->used = 0;
    new_node->next = NULL;

    return new_node;
}


static struct s_node *
destroy_node(struct s_node *node) {
    free(node);
    node = NULL;
    return node;
}

stack stack_empty(void) {
    stack pila = NULL;
    pila = malloc(sizeof(struct _s_stack));

    pila->size = 0;
    pila->top = NULL;

    assert(invrep(pila) && stack_is_empty(pila));
    return pila;
}

stack stack_push(stack s, stack_elem e) {
    assert(invrep(s));
    if(s->top == NULL || s->top->used == CHUNK_CAPACITY){
        struct s_node *new_node = create_node();
        new_node->datos[new_node->used] = e;
        new_node->next = s->top;
        new_node->used++;
        s->top = new_node;
    } else {
        if(s->top->used != CHUNK_CAPACITY){
            s->top->datos[s->top->used] = e;
            s->top->used++;
        }
    }
    s->size++;

    assert(invrep(s) && !stack_is_empty(s));
    return s;
}


stack stack_pop(stack s) {
    assert(invrep(s) && !stack_is_empty(s));

    if(s->top->used == 1u){
        struct s_node *killme = s->top;
        s->top = s->top->next;
        killme = destroy_node(killme);
    } else {
        s->top->used--;
    }

    s->size--;

    assert(invrep(s));
    return s;
}


unsigned int stack_size(stack s) {
    return s->size;
}

void stack_top(stack s, stack_elem *top) {
    assert(invrep(s) && !stack_is_empty(s) && top != NULL);
    *top = s->top->datos[s->top->used-1];
}

bool stack_is_empty(stack s) {
    return s->size == 0u;
}

stack_elem *stack_to_array(stack s) {
    stack_elem *array = calloc(s->size, sizeof(stack_elem));
    struct s_node *aux = s->top;
    size_t i = aux->used;

    for (unsigned int j = s->size; j > 0u; j--){
        if(i == 0){
            aux = aux->next;
            i = aux->used;
        } else {
            array[j - 1] = aux->datos[i - 1];
            i--;
        }
    }

    return array;
}


stack stack_destroy(stack s) {
    struct s_node *killme;
    while(s->top != NULL){
        killme = s->top;
        s->top = s->top->next;
        killme = destroy_node(killme);
    }
    free(s);
    s = NULL;
    return s;
}