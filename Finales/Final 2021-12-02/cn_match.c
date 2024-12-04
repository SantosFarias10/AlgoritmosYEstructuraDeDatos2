#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "cn_match.h"
#include "card.h"

struct _s_match {
  card card;
  struct _s_match *next;
};

cn_match match_new(void) {
    cn_match new = NULL;

    return new;
}

cn_match match_add(cn_match match, card c) {
    if(match == NULL){
        match = malloc(sizeof(struct _s_match));
        match->card = c;
        match->next = NULL;
    } else {
        cn_match aux = match;
        
        while(aux->next != NULL){
            aux = aux->next;
        }

        aux->next = malloc(sizeof(struct _s_match));
        aux->next->card = c;
        aux->next->next = NULL;
    }
    return match;
}

unsigned int match_size(cn_match match) {
    assert(match != NULL);

    unsigned int size = 0u;
    cn_match aux = match;

    while(aux != NULL){
        size++;
        aux = aux->next;
    }

    return size;
}

unsigned int match_length(cn_match match) {
    assert(match != NULL);

    unsigned int length = 0u;
    if(is_match_correct(match)){    /* si la partida esta correctamente formada */
        length = match_size(match) / 2;   /* la longitud es la mitad de la cantidad de cartas */
    }

    return length;
}

bool is_match_correct(cn_match match) {
    assert(match != NULL);

    bool correct = true;
    if(card_player(match->card) != 1){  /* si la primer carta no es del jugador 1 */
        correct = false;
    } else {
        if(match_size(match) % 2 != 0){ /* si la cantidad de cartas es impar */
            correct = false;
        } else {
            cn_match aux = match;
            while(aux->next != NULL){
                if((card_player(aux->card) == 1 && card_player(aux->next->card) != 2) || (card_player(aux->card) == 2 && card_player(aux->next->card) != 1)){
                    correct = false;
                    break;
                }
                aux = aux->next;
            }
        }
    }

    return correct;
}

unsigned int winner_total_points(cn_match match) {
    assert(match != NULL);

    unsigned int points = 0u;

    if(!is_match_correct(match)){
        return 0;
    } else {
        unsigned int p1 = 0u;
        unsigned int p2 = 0u;
        cn_match aux = match;

        p1 += card_pair_points(aux->card, aux->next->card, 1);  /* sumo los puntos de la primer pareja */
        p2 += card_pair_points(aux->card, aux->next->card, 2);  /* sumo los puntos de la primer pareja */
        while(aux->next->next != NULL){
            aux = aux->next->next;
            p1 += card_pair_points(aux->card, aux->next->card, 1);
            p2 += card_pair_points(aux->card, aux->next->card, 2);
        }

        if(p1 > p2){
            points = p1;
        } else {
            points = p2;
        }
    }

    return points;
}

card * match_to_array(cn_match match) {
    assert(match != NULL);
    
    card *array = calloc(match_size(match), sizeof(card));  /* reservo memoria para el array de cartas */
    cn_match aux = match;

    for(unsigned int i = 0u; i < match_size(match); i++){
        array[i] = aux->card;
        aux = aux->next;
    }

    assert(array != NULL);
    return array;
}

void match_dump(cn_match match) {
  card *array = match_to_array(match);
  for (unsigned int i=0u; i < match_size(match); i++) {
    card_dump(array[i]);
  }
  free(array);
}

cn_match match_destroy(cn_match match) {
    assert(match != NULL);

    cn_match killme = match;
    while(match != NULL){
        killme = match;
        match = match->next;
        killme->card = card_destroy(killme->card);
        free(killme);
    }
    
    assert(match == NULL);
    return match;
}