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
    int key;

    struct page* next;
} page;

typedef struct history_entry {
    size_t pages_used;

    struct history_entry* next;
} history_entry;

typedef struct working_page {
    unsigned int page_id;
    
    struct working_page* next;
} working_page;

typedef struct page_map {
    page** array;
    size_t array_size;
    size_t page_count;

    struct working_page* working_set_head;
    size_t set_size;

    struct history_entry* history_head;
    struct history_entry* history_tail;
    size_t entries_saved;
} page_map;

// Helper functions
void parse_args(int argc, char* argv[]);

void add_to_working_set(page_map* map, unsigned int address);
void free_working_set(page_map* map);
void save_state(page_map* map);

page* get_page(page_map* map, unsigned int address);
page* allocate_page(page_map* map, unsigned int address);

page_map * get_map();

void assert_page_size(int ps);
void assert_window_size(int ws);

#endif
