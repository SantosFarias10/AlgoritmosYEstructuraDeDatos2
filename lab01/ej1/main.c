/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Loads an array given in a file in disk and prints it on the screen."
           "\n\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

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


int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
