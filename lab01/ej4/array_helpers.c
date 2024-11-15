#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

unsigned int array_from_file(int array[], unsigned int max_size, const char *filepath) {
    FILE *file = fopen(filepath, "r");
    /* Definimos el file y con la función `fopen` le damos como argumento el filepath (dirección del archivo) y como segundo argumento le pedimos que solamente lea. */

    if (file == NULL){
        printf("No se pudo abrir el archivo \n");
        fclose(file);
        exit(EXIT_FAILURE); /* finalizamos la ejecucion a causa de un error (EXIT_FAILURE) */
    }

    unsigned int size;

    fscanf(file, "%u", &size);
    /* Escaneamos file, especificamos el formato para leer números sin signo (unsigned int) (%u) y guardándolo en la variable size. */

    if (size > 0){
        printf("El tamaño del array es: %u \n", size);
    } else {
        printf("El tamaño del array no es válido \n");
        fclose(file);
        exit(EXIT_FAILURE); /* finalizamos la ejecucion a causa de un error (EXIT_FAILURE) */
    }

    if (size > max_size){
        printf("El tamaño del array es mayor al máximo permitido \n");
        fclose(file);
        exit(EXIT_FAILURE); /* finalizamos la ejecucion a causa de un error (EXIT_FAILURE) */
    }

    for (unsigned int  i = 0; i < size; i++){
        if ((fscanf(file, "%d", &array[i])) != 1) {
            printf("La longitud del array y el número de elementos no coinciden\n"); 
            fclose(file);
            exit(EXIT_FAILURE); 
        }
    }
    /* hacemos un bucle para ir guardando los elementos en el array, usamos fscanf() para leer los elementos y almacenarlos en array[i] en su respectiva posición y ademas comprobamos si fscanf no pudo leer un entero (fscanf devuelve 1 si la lectura es exitosa) si es que falla entonces imprimimos un mensaje de error, cerramos el file y terminamos el programa */

    fclose(file);
    /* Cerramos la ruta */

    printf("Datos recolectados correctamente \n"); 
    /* mostramos un mensaje para verificar que los datos se guardaron correctamente */

    return size;
}

void array_dump(int a[], unsigned int length) {
    printf("[");

    for (unsigned int i = 0; i < length; i++){
        if(i > 0){
            printf(", ");
        }
        printf("%d", a[i]);
    }

    printf("] \n");
}

bool array_is_sorted(int a[], unsigned int length){
    bool sort = true;

    if (length == 0){
        return sort;
    }

    for (unsigned int i = 0; i < length - 1; i++){
        sort = sort && (a[i] <= a[ i + 1]);
    }

    return sort;
}