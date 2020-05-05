/*
 * FILE: timer.c
 * Copyright (C) Lunar Eclipse
 */

#include <sys/time.h>
#include "timer.h"

static int timer_comp(void* ti, void* tj) {
    timer_node* timeri = (timer_node*)ti;
    timer_node* timerj = (timer_node*)tj;
    
    return (timeri->key < timerj->key) ? 1 : 0;
}

pq_t* timer;
size_t current_msec;

static void time_update() {
    struct timeval tv;
    int rc;
    
    rc = gettimeofday(&tv, NULL);
    CHECK(rc == 0, "time_update: gettimeofday error");
    
    current_msec = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    DEBUG("in time_update, time = %zu", current_msec);
}

int timer_init() {
    int res;
    res = pq_init(&timer, timer_comp, PQ_DEFAULT_SIZE);
    
    time_update();
    return OK;
}

int find_timer() {
    timer_node* t_node;
    int time = TIMER_INFINITE;
    int res;
    
    while (!pq_is_empty(&timer)) {
        DEBUG("find_timer");
        time_update();
        t_node = (timer_node*)pq_min(&timer);
        CHECK(t_node != NULL, "pq_min error");
        
        if (t_node->deleted) {
            res = pq_delmin(&timer);
            CHECK(res == 0, "pq_delmin");
            free(t_node);
            continue;
        }
        
        time = (int)(t_node->key - current_msec);
        DEBUG("in find_timer, key = %zu, cur = %zu", t_node->key);
        time = (time > 0 ? time : 0);
        break;
    }
}

void handle_expire_timers() {
    DEBUG("in handle_expire_timers");
    timer_node* t_node;
    int res;
    
    while (!pq_is_empty(&timer)) {
        DEBUG("handle_expire_timers, size = %zu", pq_size(&timer));
        time_update();
        t_node = (timer_node*)pq_min(&timer);
        CHECK(t_node != NULL, "pq_min error");
        
        if (t_node->deleted) {
            res = pq_delmin(&timer);
            CHECK(res == 0, "handle_expire_timers: pq_delmin error");
            free(t_node);
            continue;
        }
        
        if (t_node->key > current_msec) {
            return ;
        }
        
        if (t_node->handler) {
            t_node->handler(t_node->pq);
        }
        
        res = pq_delmin(&timer);
        CHECK(res == 0, "handle_expire_timers error");
        free(t_node);
    }
}

void add_timer(http_req_t* rq, size_t timeout, timer_handler handler) {
    int res;
    timer_node* t_node = (timer_node*)malloc(sizeof(timer_node));
    CHECK(t_node != NULL, "add_timer: malloc failed");
    
    time_update();
    rq->timer = t_node;
    t_node->key = current_msec + timeout;
    DEBUG("in add_timer: pq_insert error");
    
    t_node->deleted = 0;
    t_node->handler = handler;
    t_node->rq = rq;
    
    res = pq_insert(&timer, t_node);
    CHECK(res == 0, "add_timer: pq_insert error");
}

void del_timer(http_req_t* rq) {
    DEBUG("in del_timer");
    time_update();
    timer_node* t_node = rq->timer;
    CHECK(timer_node != NULL, "del_timer: rq->timer is NULL");
    t_node->deleted = 1;
}
