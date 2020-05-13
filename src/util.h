/*
 * FILE: util.h
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Railgun
 */

#ifndef UTIL_H
#define UTIL_H

//max number of listen queue
#define MAX_LISTEN_QUEUE 1024

#define BUFLEN 1024

#define DELIM "="

#define CONF_OK 0
#define CONF_ERROR 100

#define MIN(a,b) ((a) < (b) ? (a) : (b))

struct conf_s {
    void* root; //root is a html type file
    int port;
    int thread_num;
};

typedef struct conf_s conf_t;

int open_listenfd(int port);
int make_socket_non_blocking(int fd);

int read_conf(char* filename, conf_t* cf, char* buf, int len);

#endif
