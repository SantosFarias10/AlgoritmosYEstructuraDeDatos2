/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    /*dumping the tree*/
    abb_dump(tree, ABB_IN_ORDER);
    if (!abb_is_empty(tree)) {
        printf("\n raiz: %d\n minimo: %d\n maximo: %d\n", abb_root(tree),
                                                       abb_min(tree),
                                                       abb_max(tree));
    } else {
        printf("\nÁrbol vacío\n");
    }

    unsigned int opcion = 0u;
    while (opcion != 7) {
        printf("\nSelecciona una Opción:\n1 ........ Mostrar árbol por pantalla\n2 ........ Agregar un elemento\n3 ........ Eliminar un elemento\n4 ........ Chequear existencia de elemento\n5 ........ Mostrar longitud del árbol\n6 ........ Mostrar raiz, máximo y mínimo del árbol\n7 ........ Salir\n");
        printf("Opción: ");
        scanf("%u", &opcion);
        
        abb_elem elem;

        if (opcion > 7 || opcion < 1) {
            printf("Opción Invalida\n");
        } else if (opcion == 1){
            if (abb_is_empty(tree)) {
                printf("Árbol Vacío\n");
            } else {
                printf("Selecciona el Orden:\n1 ........ In Order\n2 ........ Pre Order\n3 ........ Post Order\n");
                printf("Opción: ");
                scanf("%d", &elem);
                if (elem <= 3 && elem >= 1) {
                    printf("Árbol:\n");
                    abb_dump(tree, elem - 1);
                    printf("\n");
                } else {
                    printf("Opción Invalida\n");
                }
            }
        } else if (opcion == 2){
            printf("Elemento a Agregar: ");
            scanf("%d", &elem);
            tree = abb_add(tree, elem);
        } else if (opcion == 3){
            printf("Elemento a Eliminar: ");
            scanf("%d", &elem);
            if (abb_exists(tree, elem)) {
                tree = abb_remove(tree, elem);
            } else {
                printf("El elemento %d no existe en el árbol\n", elem);
            }
        } else if (opcion == 4){
            printf("Elemento a Chequear Existencia: ");
            scanf("%d", &elem);
            if (abb_exists(tree, elem)) {
                printf("El elemento %d existe en el árbol\n", elem);
            } else {
                printf("El elemento %d no existe en el árbol\n", elem);
            }
        } else if (opcion == 5){
            printf("La Longitud del Árbol es: %d\n", abb_length(tree));
        } else if (opcion == 6){
            printf("La Raiz del Árbol es: %d\nEl Máximo es: %d\nEl Mínimo es: %d\n", abb_root(tree), abb_max(tree), abb_min(tree));
        } else if (opcion == 7){
            tree = abb_destroy(tree);          
        }
    }
    
    return (EXIT_SUCCESS);
}
