#ifndef _STRFUNCS_H
#define _STRFUNCS_H

#include <stdbool.h>

/* Calcula la longitud de la cadena apuntada por str */
size_t string_length(const char *str);

/* Devuelve una cadena en una nueva cadena en memoria dinamica, los caracteres diferentes a c */
char *string_filter(const char *str, char c);

/* Indica si la cadena es simetrica en cuanto a los caracteres */
bool string_is_symmetric(const char *str);

#endif