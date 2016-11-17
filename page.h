#ifndef __PAGE_H__
#define __PAGE_H__

#define MAP_SIZE 2048

typedef struct page {
    int* data;
    unsigned int size;
    unsigned int key;

    page* next;
} page;

typedef struct history_entry {
    size_t pages_used;
    size_t key;

    history_entry* next;
} history_entry;

typedef struct page_map {
    page* array[MAP_SIZE];
    history_entry* history_head;
    size_t pages_used;


} page_map;

int save_state(page_map* map);

#endif
