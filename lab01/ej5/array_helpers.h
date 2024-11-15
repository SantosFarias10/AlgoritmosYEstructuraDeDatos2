#ifndef ARRAY_HELPERS_H /* Verificamos si ARRAY_HELPERS_H no ha sido definido previamente*/
#define ARRAY_HELPERS_H /* Definimos ARRAY_HELPERS_H para que las siguientes inclusiones de este archivo no vuelvan a incluir su contenido */

#include "mybool.h"

unsigned int array_from_file(int array[], unsigned int max_size, const char *filepath); 

void array_dump(int a[], unsigned int length);

mybool array_is_sorted(int a[], unsigned int length);

#endif  /* Finaliza la condicion iniciada por ifndef */