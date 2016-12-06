#include <stdlib.h>
#include <stdio.h>

#include <time.h>

#include "simulation.h"

void process () {
    /* This process function generates a number of integer */
    /* keys and sorts them using bubblesort.               */
    int N, i, j, k, t, min, f;
    clock_t start, diff;
    double msec;

    N = 4096;
    //scanf ("%d", &N);
    printf ("Sorting %1d keys\n", N);
    init (128, 1000);

    /* Generate the sorting problem (just random numbers) */
    for (i = 0; i < N; i++) put (i, lrand48 ());

    /* Sort the numbers */
    start = clock();
    for (i = 0; i < N-1; i++) {
        for (j = i+1, f = min = get (i), k = i; j < N; j++)
            if ((t = get (j)) < min) {
                k = j;
                min = t;
            }
            put (i, min);
            put (k, f);
    }
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("T1 %f ms\n", msec);
    fflush(stdout);

    done();
}
