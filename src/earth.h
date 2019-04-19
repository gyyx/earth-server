//
//  earth.h
//  earth_server
//
//  Created by 郭海 on 2019/3/31.
//

//#ifndef earth_h
//#define earth_h

/* For sockaddr_in */
#include <netinet/in.h>
/* For socket functions */
#include <sys/socket.h>
/* For fcntl */
#include <fcntl.h>
#include <set>

#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>

#include <assert.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <syslog.h>
#include <map>

#include "s2/base/commandlineflags.h"
#include "s2/s2earth.h"
#include "s2/s1chord_angle.h"
#include "s2/s2closest_point_query.h"
#include "s2/s2point_index.h"
#include "s2/s2point.h"
#include "s2/s2cell_id.h"


#include "s2/s2cell_union.h"
#include "s2/s2region_coverer.h"
#include "s2/s2cap.h"




#include "util.h"
#include "hashtable.h"
#include "SPookyHash.h"

#define PROCESS_NAME "earth_server"
#define VERSION "1.0a"


void do_read(evutil_socket_t fd, short events, void *arg);
void do_write(evutil_socket_t fd, short events, void *arg);

struct settings {
    int port;
    int run_mode;
};

typedef struct token_s {
    char *value;
    size_t length;
} token_t;

struct state {
    uint32_t total_items;
    uint64_t total_conns;
};

//#endif /* earth_h */
