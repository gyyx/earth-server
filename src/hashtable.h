//
//  hashtable.hpp
//  earth_server
//
//  Created by 郭海 on 2019/4/18.
//
#include <cstdint>
#include <cstdlib>
#include <syslog.h>
#include <string.h>
struct Item {
    Item *next;
    Item *prev;
    Item *h_next;
    char *key;
    uint32_t keylen;
    uint64_t data_cell;
};
void table_init(const int hashpower_init);
int table_insert(Item *item, const uint32_t hv);
Item *table_find(const char *key, const size_t nkey, const uint32_t hv) ;
