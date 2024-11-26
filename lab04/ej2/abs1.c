#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    if(x >= 0){
        y = x;
    } else {
        y = -x;
    }
}

int main(void) {
    int a=0, res=0;
    
    a = -10;

    absolute(a, res);

    printf("El valor abosuluto de A = %d es %d\n", a, res);

    return EXIT_SUCCESS;
}

/*
    El valor que se muestra en la pantalla es 
        El valor abosuluto de A = -10 es 0
    O sea es el valor al cual se inicializa la variable res
*/
/*
    No coincide el programa con el lenguaje de la materia
*/