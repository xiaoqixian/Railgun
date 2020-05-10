/*
 * FILE: epoll.h
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Railgun
 */

#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>

#define MAXEVENTS 1024
/*
 * In order to not to repeat the function names that have been defined in <epoll.h>, add a "rg" prefix, rg for railgun
 */
int rg_epoll_create(int flags);
void rg_epoll_add(int epfd, int fs, struct epoll_event* event);
void rg_epoll_mod(int epfd, int fs, struct epoll_event* event);
void rg_epoll_del(int epfd, int fs, struct epoll_event* event);
int rg_epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout);

#endif
