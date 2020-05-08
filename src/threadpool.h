/*
 * FILE: threadpool.h
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Railgun
 */

#ifndef THREADPOOL_H
#define THREADPOOL_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include "debug.h"
    
#define THREAD_NUM 8

typedef struct task_s {
    void (*func)(void*);  //task function pointer
    void *arg;            //function arguments
    struct task_s* next;  //points to the next task in the task queue
} task_t;

typedef struct {
    pthread_mutex_t lock; //mutex
    pthread_cond_t cond; //condition variable
    pthread_t* threads; //thread_t type array
    
    int thread_count; //thread number in the threadpool
    int queue_size;  //task number in the task queue
    int shutdown;   /*indicate if the threadpool is shutdown. Shutdown fall into two categories[immediate_shutdown, graceful_shutdown], immediate_shutdown means the threadpool has to shutdown no matter if there are tasks or not, graceful_shutdown will wait until all tasks are executed. */
    int started; //number of threads started
} threadpool_t;

typedef enum {
    tp_invalid = -1,
    tp_lock_fail = -2;
    tp_already_shutdown = -3;
    tp_cond_broadcast = -4;
    tp_thread_fail = -5;
} threadpool_error_t;

threadpool_t* threadpool_init(int thread_num);

int threadpool_add(threadpool_t* pool, void (*func)(void*), void* arg);

int threadpool_destory(threadpool_t* pool, int graceful);

#ifdef __cplusplus
}
#endif
