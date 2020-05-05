/*
 * FILE: priority_queue.h
 * Copyright (C) Lunar Eclipse
 * Description:
 * 
 */

#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include "debug.h"
#include "error.h"

#define PQ_DEFAULT_SIZE 10

typedef int (*pq_comparator_ptr)(void* pi, void* pj);

typedef struct {
    void** queue;
    size_t nalloc;
    size_t size;
    pq_comparator_ptr comp;
} pq_t;

int pq_init(pq_t* pq, pq_comparator_ptr comp, size_t size);
int pq_is_empty(pq_t* pq);
size_t pq_size(pq_t* pq);
void* pq_min(pq_t* pq);
int pq_delmin(pq_t* pq);
int pq_insert(pq_t* pq, void* item);

int pq_sink(pq_t* pq, size_t size);

#endif
