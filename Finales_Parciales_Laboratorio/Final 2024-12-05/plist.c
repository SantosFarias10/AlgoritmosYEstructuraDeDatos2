#include <stdlib.h>   /* malloc(), free(), NULL  */
#include <stdbool.h>  /* Definition of bool      */
#include <stdio.h>    /* printf()                */
#include <assert.h>   /* assert()                */

#include "plist.h"      /* Iterface */

struct s_node {
    t_elem elem;
    struct s_node *next;
};

typedef struct s_node * node_t;

struct s_plist {
    unsigned int length;
    node_t lft;
    node_t rgt;
    t_elem pivot;
};

/* Creates a single node in dynamic memory containing the element <e>. */
static node_t create_node(t_elem e) {
    node_t new_node = malloc(sizeof(struct s_node));
    new_node->elem = e;
    new_node->next = NULL;

    return new_node;
}

/* Destroys a single node */
static node_t destroy_node(node_t node) {
    free(node);
    node = NULL;
    return node;
}

/* Representation invariant */
static bool invrep(plist l) {
    bool b = true;

    node_t aux = l->lft;
    while(aux != NULL){
        if((aux->elem == l->pivot) || (aux->elem > l->pivot)){
            b = false;
            break;
        }
        aux = aux->next;
    }

    aux = l->rgt;
    while(aux != NULL){
        if((aux->elem == l->pivot) || (aux->elem < l->pivot)){
            b = false;
            break;
        }
        aux = aux->next;
    }

    if(l->length < 1){
        return false;
    } 

    return b;
}

/* CONSTRUCTORS */

plist plist_create(t_elem pivot) {
    plist l = malloc(sizeof(struct s_plist));

    l->pivot = pivot;
    l->length = 1;
    l->lft = NULL;
    l->rgt = NULL;

    assert(invrep(l) && plist_is_empty(l));
    return l;
}

plist plist_add(plist l, t_elem e) {
    assert(invrep(l) && !t_elem_eq(e, l->pivot));

    node_t new_node = create_node(e);

    if(plist_is_empty(l)){
        if(t_elem_less(e, l->pivot)){
            l->lft = new_node;
        } else {
            l->rgt = new_node;
        }
        l->length++;
    } else {
        if(t_elem_less(e, l->pivot)){
            node_t aux = l->lft;
            while(aux->next != NULL){
                aux = aux->next;
            }
            aux->next = new_node;
            l->length++;
        } else {
            new_node->next = l->rgt;
            l->rgt = new_node;
            l->length++;
        }
    }

    assert(invrep(l) && !plist_is_empty(l));
    return l;
}

/* OPERATIONS   */
unsigned int plist_length(plist l) {
    assert(invrep(l));

    unsigned int length = l->length;

    assert((length == 1) == plist_is_empty(l));
    return length;
}

bool plist_is_empty(plist l) {
    assert(invrep(l));
    return (l->length == 1);
}

t_elem plist_get_pivot(plist l) {
    assert(invrep(l));
    return (l->pivot);
}

plist plist_delete_prev(plist l) {
    assert(invrep(l));

    if (plist_is_empty(l) || l->lft == NULL) {  /* Si la lista esta vacia o no hay ningun elemento a la izquierda */
        return l;                            /* no se hace nada */
    } else {                              /* Si hay elementos a la izquierda */
        node_t aux = l->lft;    /* creamos un nuevo nodo que apunte a la lista de la izquierda */
        if (aux->next == NULL) {    /* Si solo hay un elemento en la lista de la izquierda */
            l->lft = destroy_node(aux);   /* se elimina el nodo */
        } else {                  /* Si hay mas de un elemento en la lista de la izquierda */
            node_t prev = NULL;   /* creamos un nodo previo */
            while (aux->next != NULL) { /* mientras el nodo auxiliar no sea el ultimo */
                prev = aux;         /* el nodo previo sera el nodo auxiliar */
                aux = aux->next;    /* el nodo auxiliar sera el siguiente nodo */
            }
            prev->next = destroy_node(aux); /* el nodo previo apuntara al nodo siguiente del nodo auxiliar */
        }
        l->length--;    /* se disminuye la longitud de la lista */
    }

    assert(invrep(l));
    return l;
}

plist plist_delete_next(plist l) {
    assert(invrep(l));

    if (plist_is_empty(l) || l->rgt == NULL) {  /* Si la lista esta vacia o no hay ningun elemento a la derecha */
        return l;                         /* no se hace nada */
    } else {                       /* Si hay elementos a la derecha */
        node_t aux = l->rgt;    /* creamos un nuevo nodo que apunte a la lista de la derecha */
        l->rgt = aux->next;     /* la lista de la derecha sera el siguiente nodo del nodo auxiliar */
        destroy_node(aux);    /* se elimina el nodo auxiliar */
        l->length--;    /* se disminuye la longitud de la lista */
    }

    assert(invrep(l));
    return l;
}

unsigned int plist_count(plist l, t_elem e) {
    assert(invrep(l) && !plist_is_empty(l));

    unsigned int count = 0;

    if(t_elem_less(e, l->pivot)){
        node_t aux = l->lft;
        while(aux != NULL){
            if(t_elem_eq(e, aux->elem)){
                count++;
            }
            aux = aux->next;
        }
    } else {
        node_t aux = l->rgt;
        while(aux != NULL){
            if(t_elem_eq(e, aux->elem)){
                count++;
            }
            aux = aux->next;
        }
    }

    if(t_elem_eq(e, l->pivot)){
        count++;
        return count;
    }
    assert(invrep(l));
    return count;
}

t_elem * plist_to_array(plist l) {
    assert(invrep(l));

    t_elem *array = malloc(sizeof(t_elem) * l->length);

    unsigned int index = 0;
    node_t aux = l->lft;
    while (aux != NULL) {
        array[index++] = aux->elem;
        aux = aux->next;
    }

    array[index++] = l->pivot;

    aux = l->rgt;
    while (aux != NULL) {
        array[index++] = aux->elem;
        aux = aux->next;
    }

    assert(!plist_is_empty(l));
    return array;
}

void plist_dump(plist l) {
    assert(invrep(l));
    if (plist_is_empty(l)) {
        printf("[]");
    } else {
        t_elem *elems = plist_to_array(l);
        printf("[ ");
        t_elem_dump(elems[0]);
        for (unsigned int i=1; i < plist_length(l); i++) {
            printf(", ");
            t_elem_dump(elems[i]);
        }
        printf(" ]");
        free(elems);
    }
}

plist plist_destroy(plist l) {
    assert(invrep(l));

    node_t aux = l->lft;
    while(aux != NULL){
        node_t tmp = aux;
        aux = aux->next;
        tmp = destroy_node(tmp);
    }

    aux = l->rgt;
    while(aux != NULL){
        node_t tmp = aux;
        aux = aux->next;
        tmp = destroy_node(tmp);
    }

    free(l);
    l = NULL;

    assert(l == NULL);
    return l;
}

