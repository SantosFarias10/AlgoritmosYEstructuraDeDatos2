#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

struct s_list {
    list_elem elem;
    struct s_list *next;
};

list empty_list(){
    list l = malloc(sizeof(struct s_list));

    l = NULL;

    return l;
}

list addl(list_elem e, list l){
    list p = malloc(sizeof(struct s_list));

    p->elem = e;
    p->next = l;
    
    l = p;
    
    return l;
}

list destroy(list l){
    list aux = NULL;

    while (l != NULL) {
        aux = l;
        l = l->next;
        free(aux);
    }

    return l;
}

bool is_empty(list l) {
    return (l == NULL);
}

list_elem head(list l) {
    assert(!is_empty(l));

    return l->elem;
}

list tail(list l) {
    assert(!is_empty(l));
    
    list p = l;
    l = l->next;
    
    free(p);
    
    return l;
}

list addr(list l, list_elem e) {
    list q = malloc(sizeof(struct s_list));
    q->elem = e;
    q->next = NULL;

    if(!is_empty(l)) {
        list p = l;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = q;
    } else {
        l = q;
    }
    return l;
}

unsigned int length(list l) {
    unsigned int n = 0;
    list p = l;

    while (p != NULL) {
        n++;
        p = p->next;
    }
    
    return n;
}

list concat(list l, list lO) {
    list p = NULL;

    if (l == NULL && lO != NULL) {
        l = lO;
    } else {
        p = l;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = lO;
    }
    
    return l;
}

list_elem index(list l, unsigned int n) {
    assert(length(l) > n);
    list p = l;
    if (n > 1) {
        for (unsigned int i = 0; i < n; i++) {
            p = p->next;
        }
    }
    return p->elem;
}

list take(list l, unsigned int n) {
    list p = NULL, q = NULL;
    p = l;

    if (n == 0) {
        while (l != NULL) {
            l = l->next;
            free(p);    
        }
    } else {
        unsigned int i = 0;
        
        while (i < n && l != NULL) {
            p = p->next;
            i++;
        }

        while (p != NULL) {
            q = p;
            p = p->next;
            free(q);
        }
    }
    return l;
}

list drop(list l, unsigned int n) {
    list p = NULL;
    unsigned int i = 0;
    while (i < n && l != NULL) {
        p = l;
        l = l->next;
        free(p);
        i++;
    }
    return l;
}

list copy_list(list l) {
    list l_copy = empty_list();
    list p = l;

    while (p != NULL) {
        l_copy = addr(l_copy, p->elem);
        p = p->next;
    }
    
    return l_copy;
}