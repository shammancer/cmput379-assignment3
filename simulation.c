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
    const size_t array_size = 256;

    sim_map = malloc(sizeof(page_map));
    if(sim_map == NULL){
        fprintf(stderr, "Can't malloc page map\n");
        exit(-1);
    }

    sim_map->history_head = NULL;
    sim_map->entries_saved = 0;
    sim_map->set_size = 0;
    sim_map->page_count = 0;

    sim_map->array_size = array_size;
    sim_map->array = malloc(sizeof(page*) * array_size);

    if(sim_map->array == NULL){
        fprintf(stderr, "Can't malloc page hashtable\n");
        exit(-1);
    }

    sim_map->current_working_set = malloc(sizeof(int) * window_size);

    if(sim_map->array == NULL){
        fprintf(stderr, "Can't malloc working set array\n");
        exit(-1);
    }
}

void put(unsigned int address, int value){
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
    save_state(sim_map);

    history_entry* he = sim_map->history_head;
    size_t sum = 0;
    FILE* fhist = fopen("sim_history.csv", "w+");
    while (he != NULL){
        fprintf(fhist, "%zd\n", he->pages_used);
        sum += he->pages_used;
        he = he->next;
    }
    fflush(fhist);
    fclose(fhist);

    double  average = (double) sum / (double) sim_map->entries_saved;

    fprintf(stdout, "=============================\n");
    fprintf(stdout, "Working Set History Size: %zd\n", sim_map->entries_saved);
    fprintf(stdout, "Average Working Set Size: %f\n", average);
    fprintf(stdout, "Page Count: %zd\n\n", sim_map->page_count);

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

    map->set_size = 0; // free current working set

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
        if (cp->key >= address / page_size){
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

    int key = address / page_size; 
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
        while(1){
            if(cp->next == NULL || cp->next->key > key){
                break;
            }
            cp = cp->next;
        }
        p->next = cp->next;
        cp->next = p;
    }

    map->page_count = map->page_count+1;

    return p;
}

void add_to_working_set(page_map* map, unsigned int address){
    int key = address / page_size;
    int found = 0;
    int i = 0;

    for(i = 0; i < map->set_size; i++){
        if(map->current_working_set[i] == key){
            found = 1;
            break;
        }
    }

    if(found == 0){
        map->current_working_set[i] = key;
        map->set_size = map->set_size + 1;
    }
}

page_map * get_map() {
    return sim_map;
}

// Input Assertions
// =================================================
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
