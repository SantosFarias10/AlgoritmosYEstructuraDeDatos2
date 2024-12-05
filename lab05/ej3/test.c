#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main(void) {
    stack s = stack_empty();
    stack_elem *arr = stack_to_array(s);
    s = stack_push(s, 1);
    
    unsigned int size = stack_size(s);
    printf("Stack Size = %u\n\n",size);

    s = stack_pop(s);
    printf("Stack Poped Successfully\n");
    size = stack_size(s);
    printf("Stack Size = %u\n\n",size);


    s = stack_push(s, 1);
    printf("Stack Pushed from Empty Successfully\n");
    size = stack_size(s);
    printf("Stack Size = %u\n\n",size);

    printf("stack_to_array(s) devuelve NULL si el Stack esta Vacio?\n");
    if (arr == NULL) {
        printf("True\n\n");
    } else {
        printf("False\n\n");
    }

    for (size_t i = 2; i <= 10; i++) {
        s = stack_push(s, i);
    }
    size = stack_size(s);
    printf("Stack Size = %u\n\n",size);
    arr = stack_to_array(s);
    printf("Array: ");
    for (unsigned int i = 0u; i < size; i++) {
        printf("%u ",arr[i]);
    }
    printf("\n");
    
    stack_destroy(s);

    return (EXIT_SUCCESS);
}