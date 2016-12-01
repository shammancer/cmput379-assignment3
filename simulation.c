#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "simulation.h"

size_t word_size = sizeof(unsigned int);
size_t window = 0;
int window_size = 0;
int page_size = 0;

page_map* sim_map;

int main(int argc, char* argv[]){
    parse_args(argc, argv);
    process();

    return 0;
}

void init(int psize, int winsize){
    // ignore psize and winsize
    const size_t array_size = 1024;

    sim_map = malloc(sizeof(page_map));
    if(sim_map == NULL){
        fprintf(stderr, "Can't malloc page map\n");
        exit(-1);
    }

    sim_map->history_head = NULL;
    sim_map->entries_saved = 0;
    sim_map->pages_used = 0;

    sim_map->array_size = array_size;
    sim_map->array = malloc(sizeof(page*) * array_size);

    if(sim_map->array == NULL){
        fprintf(stderr, "Can't malloc page hashtable\n");
        exit(-1);
    }
    
}

void put(unsigned int address, int value){
    page * p = get_page(sim_map, address);
    if (p == NULL){
        p = allocate_page(sim_map, address);
    }

    p->data[address % page_size] = value;

    window++;
    if(window % window_size == 0){
        save_state(sim_map);
    }
}

int get(unsigned int address){
    int s;

    page* p = get_page(sim_map, address);

    if(p == NULL){
        fprintf(stdout, "Segmentation fault accessing memory at %d\n", address);
        exit(-1);
    }

    s = p->data[address % page_size];

    window++;
    if(window % window_size == 0){
        save_state(sim_map);
    }

    return s;
}

void done(){
    history_entry* he = sim_map->history_head;
    size_t sum = 0;
    fprintf(stdout, "Working Set Size History, ");
    while (he != NULL){
        fprintf(stdout, "%d, ", he->pages_used);
        sum += he->pages_used;
    }
    size_t average = sum / sim_map->entries_saved;
    fprintf(stdout, "Average Working Set Size, %d\n", average);

    return;
}

void parse_args(int argc, char* argv[]){
    if (argc != 4) {
        fprintf(stderr, "Must be invoked using: sim <psize> <winsize> <process>\n");
        exit(-1);
    }
    
    errno = 0;
    page_size = strtol(argv[1], NULL, 10);
    window_size = strtol(argv[2], NULL, 10);

    if (errno != 0) {
        fprintf(stderr, "Unable to parse arguments\n");
        exit(-1);
    }
    return;
}

void save_state(page_map* map){
    history_entry* ne = malloc(sizeof(history_entry));

    if (ne == NULL){
        fprintf(stderr, "Unable to malloc new history entry.\n");
        exit(-1);
    }

    ne->pages_used = map->pages_used;
    ne->next = NULL;

    map->entries_saved += 1;

    if (map->history_head == NULL){
        map->history_head = ne;
    } else {
        history_entry* ce = map->history_head;
        while (ce->next != NULL){
            ce = ce->next;
        }
        ce->next = ne;
    }

    return;
}

page* get_page(page_map* map, unsigned int address){
    page* cp = map->array[(address / page_size) % map->array_size];

    while (cp != NULL) {
        if (cp->key == address / page_size){
            break;
        }

        cp = cp->next;
    }

    return cp;
}

page* allocate_page(page_map* map, unsigned int address){
    // Alocate ressources for the page
    page* p = malloc(sizeof(page));
    if (p == NULL){
        fprintf(stderr, "Unable to malloc new page.\n");
        exit(-1);
    }

    p->key = address / page_size;
    p->next = NULL;

    p->data = malloc(page_size * word_size);
    if (p->data == NULL){
        fprintf(stderr, "Unable to malloc page data.\n");
        exit(-1);
    }


    // Add it to the hashmap
    page* cp = map->array[(address / page_size) % map->array_size];
    if(cp == NULL){
        map->array[(address / page_size) % map->array_size] = p;
    } else {
        while(cp->next != NULL){
            cp = cp->next;
        }
        cp->next = p;
    }

    return p;
}
