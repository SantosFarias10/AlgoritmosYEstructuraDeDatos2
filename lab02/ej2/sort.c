#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    unsigned int pivot = partition(a, izq, der);
    /* Permuta los elementos de a[izq..der] y devuelve el pivote tal que:
        - izq <= pivote <= der
        - los elementos en a[izq,pivote) todos 'van antes' (según la función goes_before) de a[pivote]
        - a[pivote] 'va antes' de todos los elementos en a(pivote,der] 
    */

    if (pivot > izq) {
        quick_sort_rec(a, izq, pivot - 1u);
    }
    if(pivot < der) {
        quick_sort_rec(a, pivot + 1u, der);
    }
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u);
}