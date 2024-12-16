#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define CHUNK_CAPACITY 5

struct s_node {
    stack_elem chunk[CHUNK_CAPACITY];
    unsigned int used;
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
    if (check!=NULL) {
        while(check!= NULL){
            if(check->used == 0){
                return false;
            }
            check = check->next;
        }
        check = s->top;
        while(check->next != NULL){
            if(check->next->used != CHUNK_CAPACITY){
                return false;
            }
            check = check->next;
        }
    }
    return valid;   
}

static bool
invrep(stack s) {
    return ((s != NULL) && valid_chunks(s));
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
    stack s = NULL;
    s = malloc(sizeof(struct _s_stack));

    s->size = 0;
    s->top = NULL;

    assert(invrep(s) && stack_is_empty(s));
    return s;
}


stack stack_push(stack s, stack_elem e) {
    assert(invrep(s));

    if(s->top == NULL || s->top->used == CHUNK_CAPACITY){
        struct s_node *new_node = create_node();
        new_node->chunk[new_node->used] = e;
        new_node->next = s->top;
        new_node->used++;
        s->top = new_node;
    } else {
        if(s->top->used != CHUNK_CAPACITY){
            s->top->chunk[s->top->used] = e;
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
        struct s_node *aux = s->top;
        s->top = s->top->next;
        aux = destroy_node(aux);
    } else {
        s->top->used--;
    }

    s->size--;

    assert(invrep(s));
    return s;
}


unsigned int stack_size(stack s) {
    assert(invrep(s));
    return s->size;
}

void stack_top(stack s, stack_elem *top) {
    assert(invrep(s) && !stack_is_empty(s) && top != NULL);
    *top = s->top->chunk[s->top->used-1];
}

bool stack_is_empty(stack s) {
    return (s->size == 0);
}

stack_elem *stack_to_array(stack s) {
    stack_elem *array = calloc(s->size, sizeof(stack_elem));
    struct s_node *aux = s->top;
    size_t count = aux->used;
    for(unsigned int i = s->size; i > 0u; i--){
        if(count == 0u){
            aux = aux->next;
            count = aux->used;
        }else{
            array[i - 1] = aux->chunk[count-1];
            count--;
        }
    }
    return array;
}


stack stack_destroy(stack s) {
    struct s_node *aux;

    while(s->top != NULL){
        aux = s->top;
        s->top = s->top->next;
        aux = destroy_node(aux);
    }

    free(s);
    s = NULL;
    return s;
}

