#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "matchTimeline.h"

/* ============================================================================
STRUCTS
============================================================================ */

struct s_node
{
    team team;
    event e;
    time t;
    playerNumber pn;
    struct s_node *next;
};

struct s_matchTimeline
{
    struct s_node *head;
    unsigned int homeScore;
    unsigned int awayScore;
    unsigned int registers;
};

/* ============================================================================
INVERP & VALIDATION
============================================================================ */

/* funcion que verifica la representacion de la estructura */
static bool invrep(matchTimeline mt){   
    if(mt == NULL){
        return false;
    }
    return true;
}

/* funcion que verifica si el matchTimeline es valido */
bool matchTimeline_is_time_and_score_valid(matchTimeline mt){   
    if(mt != NULL){ /* si mt tiene nodos */
        struct s_node *aux = mt->head;
        if(aux != NULL){    
            while(aux->next != NULL){
                if(aux->t > aux->next->t){  /* si el tiempo de un nodo es mayor al tiempo del siguiente nodo */
                    return false;   /* no es valido */
                } else{
                    aux = aux->next;
                }
            }
        }
        
        unsigned int home_s = 0u;   /* inicializamos los goles de los locales */
        unsigned int away_s = 0u;   /* inicializamos los goles de los visitantes */
        aux = mt->head;

        while(aux != NULL){
            if(aux->e == Goal){ /* si el evento es un gol */
                if(aux->team == Home){  /* si el gol es de los locales */
                    home_s++;   /* sumamos un gol a los locales */
                } else{ /* si el gol es de los visitantes */
                    away_s++;   /* sumamos un gol a los visitantes */
                }
            }
            aux = aux->next;
        }

        if(home_s != mt->homeScore || away_s != mt->awayScore){ /* si la cantidad de goles de los locales o visitantes no coincide con la cantidad de goles registrados */
            return false;   /* no es valido */
        }
    } else {    /* si mt no tiene nodos */
        return false;
    }

    return true;
}

/* ============================================================================
CONSTRUCTOR
============================================================================ */

matchTimeline matchTimeline_empty(void){
    matchTimeline mt = NULL;

    mt = malloc(sizeof(struct s_matchTimeline));
    mt->head = NULL;
    mt->homeScore = 0u;
    mt->awayScore = 0u;
    mt->registers = 0u;

    assert(invrep(mt));
    return mt;
}

/* ============================================================================
INSERTION
============================================================================ */

static struct s_node *create_node(team team, event e, time t, playerNumber pn){

    struct s_node *new_node = NULL;

    new_node = malloc(sizeof(struct s_node));
    new_node->team = team;
    new_node->e = e;
    new_node->t = t;
    new_node->pn = pn;
    new_node->next = NULL;

    return new_node;
}

/* ============================================================================
GOAL
============================================================================ */

matchTimeline matchTimeline_score_goal(matchTimeline mt, team team, time t, playerNumber pn)
{
    assert(invrep(mt));
    
    bool no_red_card = true;
    struct s_node *aux = mt->head;
    
    while(aux != NULL){
        if(aux->e == RedCard && aux->pn == pn && aux->team == team){    /* Si el jugador tiene tarjeta roja */
            no_red_card = false;    /* no se puede agregar el evento */
        }
        aux = aux->next;
    }
    if(t < 90u && pn > 0u && no_red_card){  /* Si el tiempo es menor a los 90 minutos Y el numero del jugador es mayor a 0 Y no tiene tarjeta roja */
        struct s_node *new_node = create_node(team, Goal, t, pn);
        if(mt->head == NULL){   /* Si la lista esta vacia */
            mt->head = new_node;    /* El nuevo nodo va a la primera posicion */
        } else {
            struct s_node *tmp = mt->head;
            while(tmp->next != NULL){   /* recorremos toda la lista hasta llegar al ultimo elemento */
                tmp = tmp->next;
            }
            tmp->next = new_node;   /* El nuevo nodo va al final de la lista */
        }   
        if(team == Home){   /* Si el gol es de los locales */
            mt->homeScore++;    /* sumamos un gol a los locales */
        } else {    /* Si el gol es de los visitantes */
            mt->awayScore++;    /* sumamos un gol a los visitantes */
        }
        mt->registers++;    /* sumamos un registro */
    }

    return mt;
}

/* ============================================================================
THE CARDS
============================================================================ */

matchTimeline matchTimeline_receive_yellowCard(matchTimeline mt, team team, time t, playerNumber pn)
{
    assert(invrep(mt));
    bool b = false;
    bool no_red = true;
    struct s_node *current = mt->head;
    while(current != NULL){
        if(current->e == RedCard && current->pn == pn && current->team == team){
            no_red = false;
        }
        current = current->next;
    }
    if(t <= 90u && pn > 0u && no_red){
        struct s_node *new_node = create_node(team, YellowCard, t, pn);
        if(mt->head == NULL){
            mt->head = new_node;
        }else{
            struct s_node *temp = mt->head;
            while(temp != NULL){
                if(temp->e == YellowCard && temp->pn == pn && temp->team == team){
                   b = true;
                }
                temp = temp->next;
            }
            temp = mt->head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = new_node;
        }
        mt->registers++;
        if(b){
            mt = matchTimeline_receive_redCard(mt, team, t, pn);
        }
    }

    return mt;
}

matchTimeline matchTimeline_receive_redCard(matchTimeline mt, team team, time t, playerNumber pn){
    assert(invrep(mt));

    bool no_red_cart = true;
    struct s_node *aux = mt->head;
    while(aux != NULL){
        if(aux->e == RedCard && aux->pn == pn && aux->team == team){    /* Si el jugador ya tiene tarjeta roja */
            no_red_cart = false;
        }
        aux = aux->next;
    }
    if(t <= 90u && pn > 0u && no_red_cart){ /* Si el tiempo es menor o igual a los 90 minutos Y el numero del jugador es mayor a 0 Y no tiene tarjeta roja */
        struct s_node *new_node = create_node(team, RedCard, t, pn);
        if(mt->head == NULL){
            mt->head = new_node;
        }else{
            struct s_node *tmp = mt->head;
            while(tmp->next != NULL){   /* recorremos toda la lista hasta llegar al ultimo elemento */
                tmp = tmp->next;
            }
            tmp->next = new_node;   /* El nuevo nodo va al final de la lista */
        }
        mt->registers++;    /* sumamos un registro */
    }

    return mt;
}

matchTimeline matchTimeline_receive_WhiteCard(matchTimeline mt, team team, time t, playerNumber pn){
    assert(invrep(mt));

    bool no_red_or_yellow = true;
    struct s_node *current = mt->head;
    
    while(current != NULL){
        if((current->e == RedCard || current->e == YellowCard) && current->pn == pn && current->team == team){  /* Si el jugador tiene tarjeta roja o amarilla */
            no_red_or_yellow = false;   /* no se puede agregar el evento */
        }
        current = current->next;
    }
    
    if(t > 75u && t <= 90u && pn > 0u && no_red_or_yellow){ /* Si el tiempo es mayor a 75 minutos Y menor o igual a 90 minutos Y el numero del jugador es mayor a 0 Y no tiene tarjeta roja o amarilla */
        struct s_node *new_node = create_node(team, WhiteCard, t, pn);  /* creamos un nuevo nodo */

        if(mt->head == NULL){
            mt->head = new_node;
        } else {
            struct s_node *temp = mt->head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = new_node;
        }
        mt->registers++;
    }
    return mt;
}

/* ============================================================================
SCORE
============================================================================ */

unsigned int matchTimeline_get_score(matchTimeline mt, team team){
    assert(invrep(mt));

    unsigned int score = 0u;
    
    if(team == Home){
        score = mt->homeScore;
    } else {
        score = mt->awayScore;
    }

    return score;
}

/* ============================================================================
SIZE
============================================================================ */

unsigned int matchTimeline_size(matchTimeline mt){
    assert(invrep(mt));

    return mt->registers;
}

/* ============================================================================
PRINT
============================================================================ */

void matchTimeline_print(matchTimeline mt)
{
    fprintf(
        stdout, "            Home %u -  %u Away \n", 
        matchTimeline_get_score(mt, Home), 
        matchTimeline_get_score(mt, Away)
    );

    struct s_node *aux = mt->head;
    while (aux != NULL)
    {
        unsigned int t = aux->t;
        char *e;
        switch (aux->e)
        {
        case Goal:
            e = "    Goal   ";
            break;
        case YellowCard:
            e = "Yellow Card";
            break;
        case RedCard:
            e = "  Red Card ";
            break;
        case WhiteCard:
            e = "White Card ";
            break;
        }
        unsigned int pn = aux->pn;

        if (aux->team == Home) {
            fprintf(stdout, "%u - %s - %u' \n", pn, e, t);
        }
        else {
            fprintf(stdout, "                   %u' - %s - %u \n", t, e, pn);
        }

        aux = aux->next;
    }
}

/* ============================================================================
ARRAY
============================================================================ */

event *matchTimeline_events_array(matchTimeline mt){
    event *array = NULL;
    
    array = calloc(matchTimeline_size(mt), sizeof(event));
    struct s_node *temp = mt->head;

    for(unsigned int i = 0u; i < matchTimeline_size(mt); i++){  /* recorremos la lista */
        array[i] = temp->e; /* guardamos el evento en el arreglo */
        temp = temp->next;  /* avanzamos al siguiente nodo */
    }

    return array;
}

/* ============================================================================
DESTRUCTOR!
============================================================================ */

static struct s_node *destroy_node(struct s_node *node){
    free(node);
    node = NULL;
    return node;
}

matchTimeline matchTimeline_destroy(matchTimeline mt)
{
    assert(invrep(mt));

    struct s_node *temp = mt->head;
    struct s_node *killme;
    
    while(temp != NULL){
        killme = temp;
        temp = temp->next;
        killme = destroy_node(killme);
    }
    
    free(mt);
    mt = NULL;

    return mt;
}