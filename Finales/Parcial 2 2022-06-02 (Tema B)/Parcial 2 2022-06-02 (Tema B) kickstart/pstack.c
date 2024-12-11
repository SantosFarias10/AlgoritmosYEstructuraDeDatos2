#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    struct s_node *front;
    unsigned int size;
};

struct s_node {
    pstack_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));

    assert(new_node!=NULL);
    
    new_node->elem = e;
    new_node->priority = priority;

    new_node->next = NULL;

    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);

    free(node);
    node = NULL;
    
    assert(node == NULL);
    return node;
}


static bool invrep(pstack s) {
    bool b = true;

    if(s->size > 1u){
        struct s_node *aux = s->front;
        while(aux->next != NULL){
            if(aux->priority > aux->next->priority){
                return false;
            }
            aux = aux->next;
        }
    }

    if(s->size == 0u && s->front != NULL){
        return false;
    }

    return b;
}

pstack pstack_empty(void) {
    pstack s = NULL;

    s = malloc(sizeof(struct s_pstack));

    s->front = NULL;
    s->size = 0u;

    assert(invrep(s) && pstack_is_empty(s));

    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);
    
    if(pstack_is_empty(s) || s->front->priority > priority){
        new_node->next = s->front;
        s->front = new_node;
    } else {
        struct s_node *aux = s->front;
        while(aux->next != NULL && aux->next->priority <= priority){
            aux = aux->next;
        }
        new_node->next = aux->next;
        aux->next = new_node;
    }

    s->size++;

    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    return (s->size == 0u);
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));

    pstack_elem e = s->front->elem;

    assert(invrep(s));
    return e;
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));

    priority_t priority = s->front->priority;

    assert(invrep(s));
    return priority;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    unsigned int size = 0;
    
    size = s->size;

    return size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));

    struct s_node *aux = s->front;
    s->front = s->front->next;
    aux = destroy_node(aux);

    s->size--;

    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));

    while(!pstack_is_empty(s)){
        s = pstack_pop(s);
    }

    free(s);
    s = NULL;

    assert(s == NULL);
    return s;
}

