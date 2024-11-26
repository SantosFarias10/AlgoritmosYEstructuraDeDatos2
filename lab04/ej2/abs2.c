#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void absolute(int x, int *y) {
    if(x >= 0){
        *y = x;
    } else {
        *y = -x;
    }
}

int main(void) {
    int a=0, res=0;  // No modificar esta declaración
    // --- No se deben declarar variables nuevas ---

    a = -10;

    absolute(a, &res);

    printf("El valor abosuluto de A = %d es %d\n", a, res);

    assert(res >= 0 && (res == a || res == -a));
    return EXIT_SUCCESS;
}

/*
     Si se muestra el valor correcto ya que no estamos cambiando los valores permanentemente
*/

/*
    El parametro *y es de tipo 0UT ya que estamos modificando el valor, osea almacenar el valor de x dependiendo si es menor o mayor igual que cero
*/

/*
    Los parametros 'in' serian int x.
    Los 'out' serian int *x si lo unico que hacemos en la funcion es usar esa direccion para guardar algo.
    Los 'in/out' serian int *x pero en esta accedemos a la direccion de memoria para sacar datos para despues guardar y devolver datos en el puntero x.
*/