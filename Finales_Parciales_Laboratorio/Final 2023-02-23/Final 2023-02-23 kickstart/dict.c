#include <stdlib.h>     /* malloc(), free()... */
#include <stdbool.h>    /* bool type           */
#include <assert.h>     /* assert()            */
#include "key_value.h"  /* key_t               */
#include "dict.h"       /* intarface           */

struct _s_dict {
    size_t size;
    struct _node_t * first;
};

// Internal structure
struct _node_t {
    key_t key;
    value_t value;
    struct _node_t *next;
};



struct _node_t * create_node(key_t k, value_t v) {
    struct _node_t *new_node = malloc(sizeof(struct _node_t));

    new_node->key = k;
    new_node->value = v;
    new_node->next = NULL;

    return new_node;
}

struct _node_t *destroy_node(struct _node_t *node) {
    node->key = key_destroy(node->key);
    node->value = value_destroy(node->value);
    free(node);
    node = NULL;
    return node;
}

static bool invrep(dict_t dict) {
    bool b = true;

    if (dict->size == 0) {
        b = (dict->first == NULL);
    } else {
        b = (dict->first != NULL);
    }

    return b;
}
// --- Interface functions ---

dict_t dict_empty(void) {
    dict_t dict = malloc(sizeof(struct _s_dict));

    dict->first = NULL;
    dict->size = 0;

    assert(invrep(dict) && (dict_length(dict) == 0));
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict) && (word != NULL) && (def != NULL));

    struct _node_t *new_node = create_node(word, def);
    struct _node_t *aux = dict->first;

    if(dict_exists(dict, word)){
        while(aux != NULL){
            if(string_eq(aux->key, word)){
                aux->value = def;
            }
            aux = aux->next;
        }
    } else {
        new_node->next = dict->first;
        dict->first = new_node;
    }

    dict->size++;

    assert(invrep(dict) && dict_exists(dict, word));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    assert(invrep(dict) && (word != NULL));

    struct _node_t *aux = dict->first;

    while(aux != NULL){
        if(string_eq(aux->key, word)){
            return aux->value;
        }
        aux = aux->next;
    }

    assert(dict_exists(dict, word));
    return NULL;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict) && (word != NULL));

    bool b = false;;

    struct _node_t *aux = dict->first;

    while(aux != NULL){
        if(string_eq(aux->key, word)){
            b = true;
            break;
        }
        aux = aux->next;
    }

    assert(invrep(dict));
    return b;
}

unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    return (dict->size);
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict) && (word != NULL));

    struct _node_t *aux = dict->first;

    if(!dict_exists(dict, word)){
        return dict;
    } else {
        if(string_eq(aux->key, word)){
            dict->first = aux->next;
            destroy_node(aux);
        } else {
            while(aux->next != NULL){
                if(string_eq(aux->next->key, word)){
                    struct _node_t *aux2 = aux->next;
                    aux->next = aux->next->next;
                    destroy_node(aux2);
                    break;
                }
                aux = aux->next;
            }
        }
    }

    dict->size--;

    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    for (struct _node_t *check=dict->first; check!=NULL; check=check->next) {
        fprintf(file, "key: ");
        key_dump(check->key, file);
        fprintf(file, "\n");
        fprintf(file, "value: ");
        value_dump(check->value, file);
        fprintf(file, "\n\n");
    }
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));

    struct _node_t *aux = dict->first;

    while(aux != NULL){
        struct _node_t *aux2 = aux;
        aux = aux->next;
        destroy_node(aux2);
    }

    dict->size = 0;

    free(dict);
    dict = NULL;
    
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

dict_t dict_destroy(dict_t dict) { 
    assert(invrep(dict));
    dict = dict_remove_all(dict);
    free(dict);
    dict=NULL;
    assert(dict==NULL);
    return dict;
}

