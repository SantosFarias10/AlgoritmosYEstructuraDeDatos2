#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "data.h"

void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

int main(void) {

    data_t messi = {"Leo Messi", 36, 169};
    print_data(messi);

/* vemos el valor decimal de una dirección de memoria es hacer */
    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n", (uintptr_t) &messi.name, (uintptr_t) &messi.age, (uintptr_t) &messi.height, (uintptr_t) &messi);

/* vemos la dirección de memoria pura */
    printf("name-direc-memo: %p\n"
           "age-direc-memo: %p\n"
           "height-direc-memo: %p\n"
           "data_t-direc-memo: %p\n\n", (void *) &messi.name, (void *) &messi.age, (void *) &messi.height, (void *) &messi);

    printf("name-size en bytes: %lu = %lu :data_t-size en bytes\n", (uintptr_t) &messi.name, (uintptr_t) &messi,
            "name-direc-memo en hexa: %p = %p :data_t-direc-memo en hexa", (void *) &messi.name, (void *) &messi);


    return EXIT_SUCCESS;
}

/*
    La direccion de memoria, al igual que la cantidad de bytes, de name y data_t son iguales.
*/