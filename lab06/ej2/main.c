#include <stdio.h>
#include "string.h"

int main() {
    // Ejemplo de uso de string_less()
    string str1 = string_create("Hola");
    string str2 = string_create("Mundo");

    if (string_less(str1, str2)) {
        printf("%s es menor que %s\n", string_ref(str1), string_ref(str2));
    } else {
        printf("%s no es menor que %s\n", string_ref(str1), string_ref(str2));
    }

    string_destroy(str1);
    string_destroy(str2);

    //Intercambiamos los strings

    str1 = string_create("Mundo");
    str2 = string_create("Hola");

    if (string_less(str1, str2)) {
        printf("%s es menor que %s\n", string_ref(str1), string_ref(str2));
    } else {
        printf("%s no es menor que %s\n", string_ref(str1), string_ref(str2));
    }
    
    string_destroy(str1);
    string_destroy(str2);

    // Ejemplo de uso de string_eq()
    str1 = string_create("Iguales");
    str2 = string_create("Iguales");
    
    if (string_eq(str1, str2)) {
        printf("%s es igual a %s\n", string_ref(str1), string_ref(str2));
    } else {
        printf("%s no es igual a %s\n", string_ref(str1), string_ref(str2));
    }

    string_destroy(str1);
    string_destroy(str2);

    str1 = string_create("Diferentes1");
    str2 = string_create("Diferentes2");

    if (string_eq(str1, str2)) {
        printf("%s es igual a %s\n", string_ref(str1), string_ref(str2));
    } else {
        printf("%s no es igual a %s\n", string_ref(str1), string_ref(str2));
    }

    string_destroy(str1);
    string_destroy(str2);

    return 0;
}