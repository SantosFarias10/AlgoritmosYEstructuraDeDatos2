#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */

static
void show_pair(pair_t p) {
    printf("(%d, %d)\n", p.values[0], p.values[1]);
}

int main(void) {
    pair_t p, q;
    // Nuevo par p
    p = pair_new(3, 4);
    // Se muestra el par por pantalla
    printf("p = ");
    show_pair(p);
    // Nuevo para q con elementos de p intercambiados
    q = pair_swapped(p);
    // Se muestra q
    printf("q = ");
    show_pair(q);
    // Se destruyen p y q
    p = pair_destroy(p); /*¿Se libera espacio de memoria con mi implementacion de pair_destroy?*/
    q = pair_destroy(q);
    return EXIT_SUCCESS;
}

/*
    I) Falla ya que show_pair estaba definido para el TAD del ejercicio anterior, habria que cambiarlo por la nueva definicion
*/

/*
    III) No se logra el encapsulamiento ya que se deben utilizar los indices del arreglo para acceder a ellos
*/