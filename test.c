#include <stdlib.h>
#include <stdio.h>

#include "simulation.h"

void process () {
    /* This process function generates a number of integer */
    /* keys and sorts them using bubblesort.               */
    int N, i, j, k, t, min, f;
    scanf ("%d", &N);
    printf ("Sorting %1d keys\n", N);
    init (128, 1000);
    /* Generate the sorting problem (just random numbers) */
    for (i = 0; i < N; i++) put (i, lrand48 ());
    /* Sort the numbers */
    for (i = 0; i < N-1; i++) {
        for (j = i+1, f = min = get (i), k = i; j < N; j++)
            if ((t = get (j)) < min) {
                k = j;
                min = t;
            }
            put (i, min);
            put (k, f);
    }
    done ();
}
