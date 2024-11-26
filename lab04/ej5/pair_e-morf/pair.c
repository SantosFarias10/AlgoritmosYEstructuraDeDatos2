#include "pair.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

pair_t pair_new(int x, int y){
    pair_t p = malooc(sizeof(struct s_pair_t)); /* pedimos memoria para la struct s_pair_t */

    p->fst = x;
    p->snd = y;

    assert(p->fst == x && p->snd == y);

    return p;
}

int pair_first(pair_t p){
    assert(sizeof(p) == sizeof(pair_t));

    return p->fst;
}

int pair_second(pair_t p){
    assert(sizeof(p) == sizeof(pair_t));

    return p->snd;
}

pair_t pair_swapped(pair_t p){
    assert(sizeof(p) == sizeof(pair_t));

    pair_t q = pair_new(p->snd, p->fst);

    assert(sizeof(p) == sizeof(pair_t));

    return q;
}

pair_t pair_destroy(pair_t p){
    free(p);

    p = NULL;

    return p;
}
