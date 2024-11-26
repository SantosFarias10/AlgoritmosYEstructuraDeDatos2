#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

int main(){
    int x = 0, y = 0;
    x = 6;
    y = 4;

    printf("x = %d, y = %d\n", x,y);

    swap(&x, &y);   /* tenes que pasar como parametros la direcciones de memoria de x e y */

    printf("x = %d, y = %d\n", x,y);

    return 0;
}