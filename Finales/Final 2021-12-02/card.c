#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "card.h"

struct _s_card {
  unsigned int number;
  char suit;
  unsigned int player;
};

#define DIAMANTE  "DIAMANTE"
#define TREBOL    "TREBOL"
#define CORAZON   "CORAZON"
#define PICA      "PICA"

#define ROJO      "ROJO"
#define NEGRO     "NEGRO"

static const char *suit_str(char p) {
    const char *str;
    if (p == 'd') {
        str = DIAMANTE;
    } else if (p=='t') {
        str = TREBOL;
    } else if (p=='c') {
        str = CORAZON;
    } else {
        str = PICA;
    }
    return str;
}

/* Representation invariant */

static bool valid_suit(char p) {
  return p=='d' || p=='t' || p=='c' || p=='p';
}

static bool valid_player(int p) {
  return p==1 || p==2;
}

static bool invrep(card c) {
    bool valid_card=false;
    valid_card = c!=NULL &&
                  1 <= c->number && c->number <= 13 &&
                  valid_suit(c->suit) &&
                  valid_player(c->player);
    return valid_card;
}

/* Public functions */

card card_new(unsigned int num, char suit, unsigned int player) {
    assert(1 <= num && num <= 13 && valid_suit(suit) && valid_player(player));

    card new = malloc(sizeof(struct _s_card));  /* Reservo memoria */

    new->number = num;
    new->suit = suit;
    new->player = player;

    return new;
}

unsigned int card_player(card c) {
  return c->player; /* Retorno el numero del jugador que utilizo la carta */
}

unsigned int card_number(card c) {
  return c->number; /* Retorno el numero de la carta c */
}

char card_color(card c) {
  char color = 'n';     /* Inicializo el color de la carta en "negra" */
  if (card_suit(c) == 'c' || card_suit(c) == 'd') { /* Si el palo de la carta es CORAZON o DIAMANTE */
    color = 'r';    /* La carta es de color rojo */
  }
  return color;  /* Retorno el color de la carta */
}

char card_suit(card c) {
  return c->suit;   /* Retorno el palo/suit de la carta */
}

bool card_equal_color(card fst, card snd) {
    bool b;
    return b = (card_color(fst) == card_color(snd)); /* Retorno true si las cartas fst y snd son del mismo color */
}

unsigned int card_pair_points(card fst, card snd, unsigned int player) {
    unsigned int point = 0u;

    if(player == 1){
        if(card_equal_color(fst, snd)){
            point = 1u;
        }
    } else if (player == 2){ 
        if(card_number(fst) == card_number(snd)){
            point = 10u;
        }
    }

    return point;
}

void card_dump(card c) {
  assert(invrep(c));
  printf("(%2d, %-7s, %2d)", c->number, suit_str(c->suit), c->player);
}

card card_destroy(card c) {
    free(c);    /* Libero la memoria reservada para la carta c */

    c = NULL;   /* Apunto c a NULL */
    return c;   /* Retorno c */
}