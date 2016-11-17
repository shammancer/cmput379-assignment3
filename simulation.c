#include <stdlib.h>
#include <stdio.h>

#include "simulation.h"
#include "page.h"

size_t wordsize = sizeof(unsigned int);
size_t window = 0;
int windowsize = 0;
int pagesize = 0;

page_map sim_map;

int main(int argc, char** argv){
    process();

    return 0;
}

void init(int psize, int winsize){
}

void put(unsigned int address, int value){
    int s;

    window++;
    if(window % windowsize == 0){
        s = save_state(&sim_map);
    }
}

int get(unsigned int address){
    int s;

    window++;
    if(window % windowsize == 0){
        s = save_state(&sim_map);
    }

    return 0;
}

void done(){

}

int save_state(page_map* map){
    return 0;
}
