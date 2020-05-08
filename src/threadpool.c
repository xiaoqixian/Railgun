/*
 * FILE: threadpool.c
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Railgun
 */

#include "threadpool.h"

typedef enum {
    immediate_shutdown = 1,
    graceful_shutdown = 2
} threadpool_st_t;

static int threadpool_free(threadpool_t* pool);
static void* threadpool_worker(void* arg);

threadpool_t* threadpool_init(int thread_num) {
    if (thread_num <= 0) {
        LOG_ERR("the arg of the threadpool_init must greater than 0");
        return NULL;
    }
    
    threadpool_t* pool;
    if ((pool = (threadpool_t*)malloc(sizeof(struct threadpool_t))) == NULL) {
        goto ERR;
    }
    
    pool->thread_count = 0;
    pool->queue_size = 0;
    pool->shutdown = 0;
    pool->started = 0;
    pool->threads = (pthread_t*)malloc(sizeof(pthread_t) * thread_num);
    pool->head = (task_t*)malloc(sizeof(struct task_t)); //dummy head
    
    if ((pool->threads == NULL) || (pool->head == NULL)) {
        goto ERR;
    }
    
    pool->head->func = NULL;
    pool->head->arg = NULL;
    pool->head->next = NULL;
    
    if (pthread_mutex_init(&(pool->lock), NULL) != 0) {
        goto ERR;
    }
    
    if (pthread_cond_init(&(pool->cond), NULL) != 0) {
        pthread_mutex_destory(&(pool->lock));
        goto ERR;
    }
    
    int i;
    for (i = 0; i < thread_num; i++) {
        if (pthread_create(&(pool->threads[i]), NULL, threadpool_worker, (void*)pool) != 0) {
            threadpool_destory(pool, 0);
            return NULL;
        }
        //output the thread id as an 8-bit hexadecimal number
        LOG_INFO("thread: %08x started", (uint32_t)pool->threads[i]);
        
        pool->thread_count++;
        pool->started++;
    }
    return pool;
    
ERR:
    if (pool) {
        threadpool_free(pool);
    }
    return NULL;
}

//add a task to the threadpool, not thread
int threadpool_add(threadpool_t* pool, void (*func)(void*), void* arg) {
    int res, err = 0;
    if (pool == NULL || func == NULL) {
        LOG_ERR("pool = NULL or func = NULL");
        return -1;
    }
    
    if (pthread_mutex_lock(&(pool->lock)) != 0) {
        LOG_ERR("pthread_mutex_lock");
        return -1;
    }
    
    if (pool->shutdown) {
        err = tp_already_shutdown;
        goto OUT;
    }
    
    //TODO: use a memory pool
    task_t* task = (task_t*)malloc(sizeof(task_t));
    if (task == NULL) {
        LOG_ERR("malloc task fail");
        goto OUT;
    }
    
    //TODO: use a memory pool
    task->func = func;
    task->arg = arg;
    task->next = pool->head->next;
    pool->head->next = task;
    
    pool->queue_size++;
    
    res = pthread_cond_signal(&(pool->cond));
    CHECK(res == 0, "pthread_cond_signal");
    
OUT:
    if (pthread_mutex_unlock(&pool->lock) != 0) {
        LOG_ERR("pthread_mutex_unlock");
        return -1;
    }
    
    return err;
}

//free all threads in the threadpool
int threadpool_free(threadpool_t* pool) {
    if (pool == NULL || pool->started > 0) {
        return -1;
    }
    
    if (pool->threads) {
        free(pool->threads);
    }
    
    task_t* node;
    while (pool->head->next) {
        node = pool->head->next;
        pool->head->next = pool->head->next->next;
        free(node);
    }
    
    return 0;
}

//destory the threadpool
int threadpool_destory(threadpool_t* pool, int graceful) {
    int err = 0;
    
    if (pool == NULL) {
        LOG_ERR("pool is NULL");
        return tp_invald; //tp_invalid is in enum
    }
    
    if (pthread_mutex_lock(&(pool->lock)) != 0) {
        return tp_lock_fail;
    }
    
    do {
        if (pool->shutdown) {
            err = tp->already_shutdown;
            break;
        }
        
        pool->shutdown = (graceful) ? graceful_shutdown : immediate_shutdown;
        
        if (pthread_cond_broadcast(&(pool->cond)) != 0) {
            err = tp_cond_broadcast;
            break;
        }
        
        if (pthread_mutex_unlock(&(pool->lock)) != 0) {
            err = tp_lock_fail;
            break;
        }
        
        int i;
        for (i = 0; i < pool->thread_count; i++) {
            if (pthread_join(pool->threads[i], NULL) != 0) {
                err = tp_thread_fail;
            }
            LOG_INFO("thread %08x exit", (uint32_t)pool->threads[i]);
        }
    } while (0);
     
    if (!err) {
        pthread_mutex_destory(&(pool->lock));
        pthread_cond_destory(&(pool->cond));
        threadpool_free(pool);
    }
    
    return err;
}

static void* threadpool_worker(void* arg) {
    if (arg == NULL) {
        LOG_ERR("arg should be type threadpool_t");
        return NULL;
    }
    
    threadpool_t* pool = (threadpool_t*)arg;
    task_t* task;
    
    while (1) {
        pthread_mutex_lock(&(pool->lock));
        
        //wait on condition variable, check for fake wakeups
        while ((pool->queue_size == 0) && !(pool->shutdown)) {
            pthread_cond_wait(&(pool->cond), &(pool->lock));
        }
        
        if (pool->shutdown == immediate_shutdown) {
            break;
        }
        else if ((pool->shutdown == graceful_shutdown) && pool->queue_size == 0) {
            break;
        }
        
        task = pool->head->next;
        if (task == NULL) {
            pthread_mutex_unlock(&(pool->lock));
            continue;
        }
        
        pool->head->next = task->next;
        pool->queue_size--;
        
        pthread_mutex_unlock(&(pool->lock));
        
        (*(task->func))(task->arg);
        //TODO: memory pool
        free(task);
    }
    
    pool->started--;
    pthread_mutex_unlock(&(pool->lock));
    pthread_exit(NULL);
    
    return NULL;
}
