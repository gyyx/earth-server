//
//  hashtable.hpp
//  earth_server
//
//  Created by 郭海 on 2019/4/18.
//
#include <cstdint>
#include <cstdlib>
typedef struct _item {
    struct _item *h_next;
    char *key;
    uint64_t data_cell;
} Item;
void table_init(const int hashpower_init);
int table_insert(Item *item, const uint32_t hv);
