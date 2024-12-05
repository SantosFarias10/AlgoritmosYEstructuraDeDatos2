#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "unogame.h"
#include "card.h"

#define NO_PLAYER -1

struct s_ugame {
    player_t player;
    card_t card;
    struct s_ugame *next;
};

unogame_t
uno_newgame(card_t card) {
    unogame_t uno = NULL;
    uno = malloc(sizeof(struct s_ugame));

    uno->card = card;
    uno->next = NULL;
    uno->player = NO_PLAYER;

    return uno;
}

card_t
uno_topcard(unogame_t uno) {
    assert(uno != NULL);
    return uno->card;
}

unogame_t
uno_addcard(unogame_t uno, card_t c) {
    unogame_t new = malloc(sizeof(struct s_ugame));
    new->card = c;
    new->player = uno_nextplayer(uno);
    new->next = uno;

    return new;
}

unsigned int uno_count(unogame_t uno) {
    unsigned int res = 0u;
    unogame_t aux = NULL;
    aux = uno;
    while(aux != NULL){
        res++;
        aux = aux->next;
    }

    return res;
}

bool
uno_validpile(unogame_t uno) {
    bool b = true;
    assert(uno != NULL);

    unogame_t aux = uno;

    while(aux->next != NULL && b){
        if(!card_compatible(aux->card, aux->next->card)){
            b = false;
        }
        aux = aux->next;
    }
    if(card_get_type(aux->card) == change_color){
        b = false;
    }

    return b;
}

color_t
uno_currentcolor(unogame_t uno) {
    assert(uno != NULL);
    return card_get_color(uno->card);
}

player_t
uno_nextplayer(unogame_t uno) {
    player_t nextp;
    assert(uno != NULL);

    if(uno->player == NUM_PLAYERS - 1){
        if(card_get_type(uno->card) == skip){
            nextp = 1;
        } else {
            nextp = 0;
        }
    } else {
        if(card_get_type(uno->card) == skip){
            if(uno->player + 1 == NUM_PLAYERS - 1){
                nextp = 0;
            } else {
                nextp = uno->player + 2;
            }
        } else {
            nextp = uno->player + 1;
        }
    }

    assert(nextp < NUM_PLAYERS && nextp >= 0);

    return nextp;
}

card_t *
uno_pile_to_array(unogame_t uno) {
    card_t *array = calloc(uno_count(uno), sizeof(card_t));
    unogame_t aux = uno;

    for (unsigned int i = uno_count(uno); i > 0u && aux != NULL; i--){
        array[i - 1] = aux->card;
        aux = aux->next;
    }

    return array;
}

unogame_t
uno_destroy(unogame_t uno) {
    unogame_t killme;
    while(uno != NULL){
        killme = uno;
        uno = uno->next;
        killme->card = card_destroy(killme->card);
        free(killme);
    }
    return uno;
}