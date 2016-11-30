#ifndef __SIMULATION_H__
#define __SIMULATION_H__

// Project Interface
void process();
void init(int psize, int winsize);
void put(unsigned int address, int value);
int get(unsigned int address);
void done();

// Data Structures
typedef struct page {
    int* data;
    unsigned int size;
    unsigned int key;

    struct page* next;
} page;

typedef struct history_entry {
    size_t pages_used;

    struct history_entry* next;
} history_entry;

typedef struct page_map {
    page** array;
    history_entry* history_head;
    size_t entries_saved;
    size_t array_size;
    size_t pages_used;


} page_map;

// Helper functions
void parse_args(int argc, char* argv[]);
void save_state(page_map* map);

#endif
