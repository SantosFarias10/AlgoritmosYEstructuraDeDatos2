#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    unsigned int size;
    struct s_node *front;
};

struct s_node {
    pqueue_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = NULL; /* Inicializamos un nuevo nodo */

    new_node = malloc(sizeof(struct s_node));   /* Guardamos memoria */

    assert(new_node!=NULL); /* Verificamos que se haya guardado memoria */

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

/* aca hay que verificar que " q " sea una pqueue, entonces hay que preguntarnos ¿Cuando una pqueue no es valida? una pqueue no es valida si tenemos un elemento de prioridad menor antes que uno de prioridad mayor, si tiene un tamaño negativo, o si el tamaño es 0 pero el front no es null */
static bool invrep(pqueue q) {
    bool b = true;

    if(q->size > 1u){
        struct s_node *aux = q->front;
        while(aux->next != NULL){
            if(aux->priority > aux->next->priority){
                return false;
            }
            aux = aux->next;
        }
    }

    if(q->size == 0u && q->front != NULL){
        return false;
    }

    return b;
}

/* Inicializamos una pqueue */
pqueue pqueue_empty(void) {
    pqueue q = NULL;

    q = malloc(sizeof(pqueue));
    q->size = 0u;
    q->front = NULL;

    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    
    if(pqueue_is_empty(q) || q->front->priority > priority){    /* Si pqueue es vacia o la prioridad del primer elemento es mas grande que la prioridad del elemento que queremos agregar */
        new_node->next = q->front;  /* El nuevo nodo apunta al primer nodo */
        q->front = new_node;    /* El primer nodo ahora es el nuevo nodo */
    } else {
        struct s_node *aux = q->front;  /* Creamos un nodo auxiliar que apunta al primer nodo */
        while(aux->next != NULL && aux->next->priority <= priority){    /* Mientras el siguiente nodo no sea nulo y la prioridad del siguiente nodo sea menor o igual a la prioridad del nodo que queremos agregar */
            aux = aux->next;    /* Avanzamos al siguiente nodo */
        }
        new_node->next = aux->next; /* El nuevo nodo apunta al siguiente nodo */
        aux->next = new_node;   /* El nodo actual apunta al nuevo nodo */
    }

    q->size++;  /* Aumentamos el tamaño de la pqueue */

    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    return (q->size == 0u && q->front == NULL);
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    
    pqueue_elem e = q->front->elem;
    
    assert(invrep(q));
    return e;
}

unsigned int pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));

    unsigned int priority = q->front->priority;

    assert(invrep(q));
    return priority;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    unsigned int size = 0u;

    size = q->size;

    return size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));

    struct s_node *aux = q->front;  /* Creamos un nodo auxiliar que apunta al primer nodo */
    q->front = q->front->next;  /* El primer nodo ahora es el siguiente nodo */
    aux = destroy_node(aux);    /* Destruimos el nodo auxiliar */
    q->size--;  /* Disminuimos el tamaño de la pqueue */

    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    
    while(!pqueue_is_empty(q)){   /* Mientras la pqueue no este vacia */
        q = pqueue_dequeue(q);  /* Desencolo la pqueue */
    }

    free(q);    /* Libero la memoria de la pqueue */
    q = NULL;   /* La pqueue ahora es NULL */

    assert(q == NULL);
    return q;
}
