/*
 * FILE: priority_queue.c
 * Copyright (C) Lunar Eclipse
 * Description:
 */

#include "priority_queue.h"

int pq_init(pq_t* pq, pq_comparator_ptr comp, size_t size) {
    pq->queue = (void**)malloc(sizeof(void*) * (size + 1));
    if (!pq->queue) {
        LOG_ERR("pq_init: malloc failed");
        return -1;
    }
    
    pq->nalloc = 0;
    pq->size = size + 1;
    pq->comp = comp;
    
    return OK;
}

int pq_is_empty(pq_t* pq) {
    return (pq->nalloc == 0) ? 1 : 0;
}

size_t pq_size(pq_t* pq) {
    return pq->nalloc;
}

void* pq_min(pq_t* pq) {
    if (pq_is_empty(pq)) {
        return NULL;
    }
    return pq->queue[1];
}

static int resize(pq_t* pq, size_t new_size) {
    if (new_size <= pq->nalloc) {
        LOG_ERR("resize: new_size to small");
        return ERROR;
    }
    
    void** new_pq = (void**)malloc(sizeof(void*) * new_size);
    if (!new_pq) {
        LOG_ERR("resize: malloc failed");
        return ERROR;
    }
    
    memcpy(new_pq, pq->queue, sizeof(void*) * (pq->nalloc + 1));
    free(pq->queue);
    pq->queue = new_pq;
    pq->size = new_size;
    return OK;
}

//exchange two entries in the priority queue
static void exch(pq_t* pq, size_t i, size_t j) {
    void* tmp = pq->queue[i];
    pq->queue[i] = pq->queue[j];
    pq->queue[j] = tmp;
}

static void swim(pq_t* pq, size_t k) {
    while (k > 1 && pq->comp(pq->queue[k], pq->queue[k/2])) {
        exch(pq, k, k/2);
        k /= 2;
    }
}

static size_t sink(pq_t* pq, size_t k) {
    size_t j;
    size_t nalloc = pq->nalloc;
    
    while (2*k <= nalloc) {
        j = 2*k;
        if (j < nalloc && pq->comp(pq->queue[j+1], pq->queue[j])) j++;
        if (!pq->comp(pq->queue[j], pq->queue[k])) break;
        exch(pq, j, k);
        k = j;
    }
    return k;
}

int pq_delmin(pq_t* pq) {
    if (pq_is_empty(pq)) {
        return OK;
    }
    
    exch(pq, 1, pq->nalloc);
    pq->nalloc--;
    sink(pq, 1);
    if (pq->nalloc > 0 && pq->nalloc <= (pq->size - 1)/4) {
        if (resize(pq, pq->size / 2) < 0) {
            return ERROR;
        }
    }
    return OK;
}

int pq_insert(pq_t* pq, void* item) {
    if (pq->nalloc + 1 == pq->size) {
        if (resize(pq, pq->size * 2) < 0) {
            return ERROR;
        }
    }
    
    pq->queue[++pq->nalloc] = item;
    swim(pq, pq->nalloc);
    
    return OK;
}

int pq_sink(pq_t* pq, size_t i) {
    return sink(pq, i);
}
