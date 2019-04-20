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
static Item* linkHead = 0;

/**
 初始化hash表

 @param hashpower_init <#hashpower_init description#>
 */
void table_init(const int hashpower_init) {
    if (hashpower_init) {
        hashpower = hashpower_init;
    }
    uint32_t arraysize = hashsize(hashpower);
    primary_hashtable = (Item**)calloc(arraysize, sizeof(void *));
    linkHead = (Item*)calloc(1, sizeof(void *));
    
}

/**
 查找一个节点

 @param key 要查找的KEY
 @param nkey KEY的长度
 @param hv hash值
 @return 查找的结果，无法找到返回NULL
 */
Item *table_find(const char *key, const size_t nkey, const uint32_t hv) {
    Item *it;
    uint32_t posit = hv & hashmask(hashpower);
//    取出指定桶的位置
    it = primary_hashtable[posit];
    Item *ret = nullptr;
    
    while (it) {
        if ( nkey == it->keylen && memcmp(key,it->key,nkey)==0) {
            ret = it;
            break;
        }
        it = it->h_next;
    }
    
    return ret;
}

/**
 在表内插入新的数据

 @param item 数据
 @param hv hash值
 @return 1成功
 */
int table_insert(Item *item, const uint32_t hv) {
    uint32_t posit = hv & hashmask(hashpower);
    item->h_next = primary_hashtable[posit];
    primary_hashtable[posit] = item;
    //构建双向链表
    item->next = linkHead;
    linkHead->prev = item;
    linkHead = item;
    return 1;
}

static Item **_table_before(const char *key, const size_t nkey, const uint32_t hv) {
    Item **pos = &primary_hashtable[hv & hashmask(hashpower)];
    while (*pos && ((nkey != (*pos)->keylen )|| memcmp(key, (*pos)->key, nkey))) {
        pos = &(*pos)->h_next;
    }
    return pos;
}


/**
 删除表内指定成员

 @param key 要删除的KEY
 @param nkey <#nkey description#>
 @param hv <#hv description#>
 @return <#return value description#>
 */
int table_delete(const char *key,const size_t nkey,const uint32_t hv) {
    Item **it = _table_before(key, nkey, hv);
    if ( *it) {
        Item *nxt,*cur;
        cur = *it;
        
        // 从哈希表里删除元素
        nxt = (*it)->h_next;
        (*it)->h_next = nullptr;
        *it = nxt;
        
        // 从双向链表里删除元素
        if (cur->prev != nullptr) {
            cur->prev->next = cur->next;
        }
        if (cur->next != nullptr ) {
            cur->next->prev = cur->prev;
        }
        
        delete []cur->key;
        delete cur;
    }
    return 0;
}
