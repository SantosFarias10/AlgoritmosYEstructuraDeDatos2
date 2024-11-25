#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

/* data_from_file lo que hace leer y rellenar los arreglos indexes[] y letters[] con los datos leidos del archivo indicado por path, ademas devuelva cuántos elementos efectivamente contenía dicho archivo */
unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size){
    unsigned int length = 0u;

    FILE *file = NULL;
    file = fopen(path, "r");

    if(file == NULL){
        printf("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    while(length < max_size && feof(file) == 0){ /* feof es igual a 0 cuando no es la ultima linea leida, cuando llega al final del archivo devuelve un numero distinto de 0, entonces sale del bucle */
        int res = fscanf(file, "%u -> *%c*\n", &indexes[length], &letters[length]); /* fscanf Retorna el número de campos que ha convertido y asignado correctamente (2) */

        if(res != 2){
            printf("Error: formato no valido\n");
            exit(EXIT_FAILURE);
        }
        
        if(indexes[length] > max_size){
            printf("Error: el indice es mayor al tamaño maximo\n");
            exit(EXIT_FAILURE);
        }

        if(ferror(file) != 0){  /* ferror retorna un valor distinto de cero para indicar un error en la ruta especificada. Un valor de retorno de 0 significa que no se ha producido ningún error. */
            printf("Error al leer el archivo\n");
            exit(EXIT_FAILURE);
        }

        length++;
    }

    fclose(file);

    return length;
}

void sort_letters(unsigned int indexes[], char letters[], char sorted[], unsigned int length){  /* En char sorted[] vamos a ir guardando los valores ya ordenados */
    for(unsigned int i = 0; i < length; i++){
        sorted[indexes[i]] = letters[i];  /* En la posicion indexes[i] de sorted[] guardamos el valor de letters[i] */
    }
}

/* La funcion *parce_filepath se va a encargar de leer correctamente los argumentos */
char *parce_filepath(int argc, char *argv[]) { 
    char *result = NULL;

    if (argc < 2){
        exit(EXIT_FAILURE);
    }
    
    result = argv[1];
    
    return result;
}

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

int main(int argc, char *argv[]) {  /* int argc es la cantidad de argumentos que toma main u *argv[] son los valores de los argumentos */
    const char *filePath = parce_filepath(argc, argv);
    
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    
    unsigned int length = data_from_file(filePath, indexes, letters, MAX_SIZE);

    if(length == 0u){
        printf("Error: archivo vacio\n");
        exit(EXIT_FAILURE);
    }

    sort_letters(indexes, letters, sorted, length);

    dump(sorted, length);

    return EXIT_SUCCESS;
}

