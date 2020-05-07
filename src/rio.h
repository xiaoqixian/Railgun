/*
 * FILE: rio.h
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Railgun
 */

#ifndef RIO_H
#define RIO_H

#include <sys/types.h>

#define RIO_BUFF_SIZE 8192

// refernce to the implementation of CSAPP


typedef struct {
    int rio_fd; //decriptor for this internal buffer
    ssize_t rio_cnt; //unread bytes in the internal buf
    char* rio_bufptr; //next unread byte in internal buf
    char rio_buf[RIO_BUFF_SIZE]; //internal buf
} rio_t;

ssize_t rio_readn(int fd, void* buf, size_t n);
ssize_t rio_writen(int fd, void* buf, size_t n);
void rio_init(rio_t* rp, int fd);
ssize_t rio_readnb(rio_t* rp, void* buf, size_t n);
ssize_t rio_readlineb(rio_t* rp, void* buf, size_t maxlen);

#endif
