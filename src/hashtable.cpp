//
//  hashtable.cpp
//  earth_server
//
//  Created by 郭海 on 2019/4/18.
//

#include "hashtable.h"

#define hashsize(n) ((uint16_t)1<<(n))
#define hashmask(n) (hashsize(n)-1)

uint32_t hashpower = 16;

static Item** primary_hashtable = 0;

void table_init(const int hashpower_init) {
    if (hashpower_init) {
        hashpower = hashpower_init;
    }
    primary_hashtable = (Item**)calloc(hashsize(hashpower), sizeof(void *));
    
}

int table_insert(Item *item, const uint32_t hv) {
    item->h_next = primary_hashtable[hv && hashmask(hashpower)];
    primary_hashtable[hv && hashmask(hashpower)] = item;
    return 1;
}
