#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"
#include "fixstring.h"


static unsigned int partition(fixstring a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv, i, j;
    ppiv = izq;
    i = izq + 1u;
    j = der;

    while (i <= j) {
        if (goes_before(a[i],a[ppiv])) {
            i = i + 1u;
        } else if (goes_before(a[ppiv],a[j])) {
            j = j - 1u;
        } else if (goes_before(a[ppiv],a[i]) && goes_before(a[j],a[ppiv])) {
            swap(a,i,j);
            i = i+1;
            j = j-1;
        }
    }
    swap(a,ppiv,j);
    ppiv = j;

    return ppiv;
}

static void quick_sort_rec(fixstring a[], unsigned int izq, unsigned int der) {
    unsigned int pivot = partition(a, izq, der);

    if (izq < pivot){
        quick_sort_rec(a, izq, pivot-1);
    }
    if (pivot < der) {
        quick_sort_rec(a, pivot+1, der);
    }
}

void quick_sort(fixstring a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}


