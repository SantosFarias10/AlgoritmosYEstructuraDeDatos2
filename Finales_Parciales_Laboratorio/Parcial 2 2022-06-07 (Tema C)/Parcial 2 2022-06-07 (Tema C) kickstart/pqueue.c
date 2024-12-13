#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"
#include <stdio.h>

#define MIN_PRIORITY 10u

struct s_pqueue {
    priority_t min_priority;
    struct s_node *array[MIN_PRIORITY];
    size_t size;
};

struct s_node {
    pqueue_elem elem;
    struct s_node *next;
};  

/* Creamos un nuevo nodo con el elemento e el siguiente NULL */
static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);

    new_node->elem = e;
    new_node->next = NULL;

    return new_node; 
}

/* Destruimos un nodo liberando la memoria y apuntandolo a un lugar NULL */
static struct s_node * destroy_node(struct s_node *node) {
    free(node);
    node = NULL;
    return node;
}

/* Nos preguntamos ¿Que hace que una pqueue no sea una cola de prioridades? */
static bool invrep(pqueue q) {
    return (q != NULL);
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue q = NULL;
    q = malloc(sizeof(struct s_pqueue));

    q->min_priority = min_priority;
    q->size = 0u;

    for (unsigned int i = 0u; i < MIN_PRIORITY; i++) {
        q->array[i] = NULL;
    }
    
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q));

    if(priority > q->min_priority){
        printf("La prioridad del elemento que se quiere agregar es mayor al permitido\n");
        return q;
    } else {
        struct s_node *new_node = create_node(e);   /* Creamos un nodo con los datos que quermos agregar */
    
        if(pqueue_is_empty(q)){
            q->array[priority] = new_node;
            new_node->next = NULL;
        } else {
            struct s_node *aux = q->array[priority];     /* Creamos un nodo auxiliar para recorrer la lista */
            q->array[priority] = new_node;               /* Agregamos el nodo a la lista */
            new_node->next = aux;                        /* El nuevo nodo apunta al nodo que estaba en la lista */
        }

        q->size++;                                   /* Aumentamos el tamaño de la cola */
    }

    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    return (q->size == 0u);
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));

    pqueue_elem max = MIN_PRIORITY;

    for(unsigned int i = q->min_priority; i > 0; i--){
        if(q->array[i] != NULL){
            if(i <= max){
                max = i;
            }
        }
    }

    pqueue_elem e = q->array[max]->elem;

    assert(invrep(q));
    return e;
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    
    priority_t max = MIN_PRIORITY;

    for(unsigned int i = q->min_priority; i > 0; i--){
        if(q->array[i] != NULL){
            if(i <= max){
                max = i;
            }
        }
    }

    priority_t priority = max;

    assert(invrep(q));
    return priority;
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));
    return (q->size);
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));

    priority_t max = MIN_PRIORITY;

    for(unsigned int i = q->min_priority; i > 0; i--){
        if(q->array[i] != NULL){
            if(i <= max){
                max = i;
            }
        }
    }

    struct s_node *aux = q->array[max];
    q->array[max] = q->array[max]->next;
    aux = destroy_node(aux);

    q->size--;

    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));

    if (q == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < MIN_PRIORITY; i++) {
        while (q->array[i] != NULL) {
            struct s_node *aux = q->array[i];
            q->array[i] = q->array[i]->next;
            aux = destroy_node(aux);
        }
    }

    free(q);
    q = NULL;

    assert(q == NULL);
    return q;
}

/*
    ERROR: El programa con el ejemplo hospital_b.in no funciona y tira un segmentation fault ya que todos los elementos de la cola tienen prioridad 0 y falla no se porque (seguramente el problema este en los for ya que va a iterar cuando i > 0 xd)
*/