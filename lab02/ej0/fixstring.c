#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    unsigned int length = 0u;
    while (length < FIXSTRING_MAX){
        if(s[length] == '\0'){
            break;
        }
        length++;
    }

    return length;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    bool eq = true;

    if(fstring_length(s1) != fstring_length(s2)){
        eq = false;
        return eq;
    }

    for(unsigned int i = 0u; i < FIXSTRING_MAX; i++){
        if(s1[i] != s2[i]){
            eq = false;
            break;
        }
    }

    return eq;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    unsigned int less_eq = 0u;

    while (s1[less_eq] != '\0' && s2[less_eq] != '\0' && s1[less_eq] == s2[less_eq]){
        less_eq++;
    }
    
    return s1[less_eq] <= s2[less_eq];
}