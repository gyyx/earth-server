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
    
} item;
void table_init(const int hashpower_init);
int table_insert(item *item, const uint32_t hv);
