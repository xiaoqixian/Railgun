/*
 * FILE: epoll.c
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Railgun
 */

#include "epoll.h"
#include "debug.h"

struct epoll_event* events;

int rg_epoll_create(int flags) {
    int fd = epoll_create1(flags);
    CHECH(fd > 0, "rg_epoll_create: epoll_create1");
    
    events = (struct epoll_event*)malloc(sizeof(struct epoll_event) * MAXEVENTS);
    CHECK(events != NULL, "rg_epoll_create: malloc");
    
    return fd;
}

//add a file descriptor
void rg_epoll_add(int epfd, int fd, struct epoll_event* event) {
    int res = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, event);
    CHECH(res == 0, "rg_epoll_add: epoll_ctl");
    return ;
}

//change the mode of the file descriptor
void rg_epoll_mod(int epfd, int fd, struct epoll_event* event) {
    int res = epoll_ctl(epfd, EPOLL_CTL_MOD, fd, event);
    CHECK(res == 0, "rg_epoll_mod: epoll_ctl");
    return ;
}

//delete a file descriptor from epoll
void rg_epoll_del(int epfd, int fd, struct epoll_event* event) {
    int res = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, event);
    CHECK(res == 0, "rg_epoll_del: epoll_ctl");
    return ;
}

int rg_epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout) {
    int n = epoll_wait(epfd, events, maxevents, timeout);
    CHECK(n >= 0, "rg_epoll_wait: epoll_wait");
    return n;
}
