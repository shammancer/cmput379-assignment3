#include <stdlib.h>
#include <stdio.h>

#include "simulation.h"

void process () {
    printf("Initializing\n");
    init(1, 1);
    printf("Putting 4 into address 3\n");
    put(3, 4);
    printf("Getting contents of 3\n");
    int x = get(3);
    printf("Contents found in address 3: %d\n", x);
    done();
}
