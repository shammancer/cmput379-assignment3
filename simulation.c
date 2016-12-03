#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include <time.h>

#include "simulation.h"

size_t word_size = sizeof(int);
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
    sim_map->set_size = 0;

    sim_map->array_size = array_size;
    sim_map->array = malloc(sizeof(page*) * array_size);

    if(sim_map->array == NULL){
        fprintf(stderr, "Can't malloc page hashtable\n");
        exit(-1);
    }
    
}

void put(unsigned int address, int value){
    //assert_address(address);

    page * p = get_page(sim_map, address);
    if (p == NULL){
        p = allocate_page(sim_map, address);
    }

    p->data[address % page_size] = value;

    add_to_working_set(sim_map, address);
    window++;
    if(window % window_size == 0){
        save_state(sim_map);
    }
}

int get(unsigned int address){
    int s;

    //assert_address(address);

    page* p = get_page(sim_map, address);

    if(p == NULL){
        fprintf(stdout, "Segmentation fault accessing memory at %d\n", address);
        exit(-1);
    }

    s = p->data[address % page_size];

    add_to_working_set(sim_map, address);
    window++;
    if(window % window_size == 0){
        save_state(sim_map);
    }

    return s;
}

void done(){
    // Save last state
    fprintf(stdout, "Simulation Done\n");
    save_state(sim_map);
    fprintf(stdout, "Saved Last Entry\n");

    history_entry* he = sim_map->history_head;
    size_t sum = 0;
    fprintf(stdout, "=============================\n");
    fprintf(stdout, "Working Set History Size: %d\n", sim_map->entries_saved);
    fprintf(stdout, "Working Set History, ");
    while (he != NULL){
        fprintf(stdout, "%d, ", he->pages_used);
        sum += he->pages_used;
        he = he->next;
    }
    double  average = (double) sum / (double) sim_map->entries_saved;
    fprintf(stdout, "\nAverage Working Set Size, %f\n", average);

    return;
}

void parse_args(int argc, char* argv[]){
    if (argc != 3) {
        fprintf(stderr, "Arguments not passed correctly\n");
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

    ne->pages_used = map->set_size;
    ne->next = NULL;

    free_working_set(map);

    map->entries_saved += 1;

    if (map->history_head == NULL){
        map->history_head = ne;
        map->history_tail = ne;
    } else {
        map->history_tail->next = ne;
        map->history_tail = ne;
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

void free_working_set(page_map* map){
    map->set_size = 0;

    working_page* cwp = map->working_set_head;
    working_page* nwp;

    map->working_set_head = NULL;

    while(cwp != NULL){
        nwp = cwp->next;
        free(cwp);
        cwp = nwp;
    }
}

void add_to_working_set(page_map* map, unsigned int address){
    int found = 0;
    working_page* wp = malloc(sizeof(wp));
    if(wp == NULL){
        fprintf(stderr, "Unable to allocate new working page\n");
        exit(-1);
    }
    wp->page_id = address / page_size;
    wp->next = NULL;

    working_page* cwp = map->working_set_head;

    if(cwp == NULL){
        map->working_set_head = wp;
        map->set_size = 1;
    } else {
        found = 0;

        while(1){
            if (cwp->page_id == wp->page_id){
                free(wp);
                return;
            }

            if (cwp->next == NULL){
                break;
            }

            cwp = cwp->next;
        }

        if(found == 0){
            cwp->next = wp;
            map->set_size = map->set_size + 1;
        }
    }
}

// Input Assertions
// =================================================

void assert_address(unsigned int address){
    if(address <= 0 && address >= 33554431){
        fprintf(stderr, "Address is in invalid range.");
        exit(-1);
    }
}

void assert_page_size(int ps){
    if(ps <= 0){
        fprintf(stderr, "Page Size is Invalid.");
        exit(-1);
    }
}

void assert_window_size(int ws){
    if(ws <= 0){
        fprintf(stderr, "Window Size is Invalid.");
        exit(-1);
    }
}
