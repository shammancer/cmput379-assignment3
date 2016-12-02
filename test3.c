#include <stdlib.h>
#include <stdio.h>

#include "simulation.h"

void process () {
    printf("Initializing\n");
    init(1, 1);
    printf("Looping\n");
    int i;

    for(i = 0; i < 4096; i++){
        put(i, i);
    }

    int v;
    for(i = 0; i < 4096; i = i + 128){
        v = get(i);
    }
    fflush(stdout);

    done();
}
