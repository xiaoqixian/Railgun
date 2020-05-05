/*
 * FILE: timer.h
 * Copyright (C) Lunar Eclipse
 * Description:
 *   Timer for the web server
 */

#ifndef TIMER_H
#define TIMER_H

#include "priority_queue.h"
#include "http_request.h"

#define TIMER_INFINITE -1
#define TIMEOUT_DEFAULT 500 //ms

typedef int (*timer_handler)(http_req_t* rq);

typedef struct timer_node_s {
    size_t key;
    int deleted;
    timer_handler handler;
    http_req_t* rq;
} timer_node;

int timer_init();
int find_timer();
void handle_expire_timers();

extern pq_t timer;
extern size_t current_msec;

void add_timer(http_req_t* rq, size_t timeout, timer_handler handler);
void del_timer(http_req_t* rq);

#endif
