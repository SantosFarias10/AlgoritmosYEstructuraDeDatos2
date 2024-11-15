#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    struct bound_data res;

    /* Inicializamos */
    res.is_upperbound = false;
    res.is_lowerbound = false;
    res.exists = false;
    res.where = 0;


    for (unsigned int i = 0; i < length; i++){
        if (arr[i] == value){
            res.exists = true;
            res.where = i;
        }
        if(arr[i] >= value && !res.is_lowerbound){
            res.is_upperbound = true;
        } else {
            res.is_upperbound = false;
        }
        if (arr[i] <= value && !res.is_upperbound){
            res.is_lowerbound = true;
        } else {
            res.is_lowerbound = false;
        }
    }
    return res;
}

int main(void) {
    int a[ARRAY_SIZE];
    int value;

    for (int i = 0; i < ARRAY_SIZE; i++){
        printf("Ingrese el valor para la posicion %d\n", i);
        scanf("%d", &a[i]);
    }

    printf("Ingrese el valor a comparar\n");
    scanf("%d", &value);

    struct bound_data result = check_bound(value, a, ARRAY_SIZE);

    if (result.is_upperbound && result.exists){
        printf("El valor ingresado es cota Superior y Maximo\n");
        printf("Y se encuentra en la posicion %d\n", result.where);
    } else if (result.is_upperbound){
        printf("El valor ingresado es cota superior\n");
    } else if (result.is_lowerbound && result.exists){
        printf("El valor ingresado es cota inferior y Minimo\n");
        printf("Y se encuentra en la posicion %d\n", result.where);
    } else if (result.is_lowerbound){
        printf("El valor ingresado es cota inferior\n");
    }
    
    return EXIT_SUCCESS;
}