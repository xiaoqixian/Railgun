/*
 * FILE: list.h
 * Copyright (C) Lunar Eclipse
 * Description:
 *   A bidirectional circle linked list with a header node
 */

#ifndef LIST_H
#define LIST_H

#ifndef NULL
#define NULL 0
#endif


struct list_head {
    struct list_head *prev, *next;
};

typedef struct list_head list_head;

#define INIT_LIST_HEAD(ptr) do {\
    struct list_head* _ptr = (struct list_head*)ptr;\
    (_ptr)->next = (_ptr);\
    (_ptr->prev) = (_ptr);\
} while (0)

/* Insert a new entry into two consecutive entries */
static inline void __list_add(struct list_head* _new, struct list_head* prev, struct list_head* next) {
    _new->next = next;
    _new->prev = prev;
    prev->next = _new;
    next->prev = _new;
}

// add a new entry after the head
static inline void list_add_head(struct list_head* _new, struct list_head* head) {
    __list_add(_new, head, head->next);
}

// add a new entry after the tail
static inline void list_add_tail(struct list_head* _new, struct list_head* head) {
    __list_add(_new, head->prev, head);
}

//delete an entry from two consecutive entries
static inline void __list_del(struct list_head* prev, struct list_head* next) {
    prev->next = next;
    next->prev = prev;
}

//delete the entry from the linked list
static inline void list_del(struct list_head* entry) {
    __list_del(entry->prev, entry->next);
}

//check whether the list is empty
static inline int list_empty(struct list_head* head) {
    return (head->next == head) && (head->prev == head);
}

//the priority of -> is higher than &
#define OFFSET_OF(TYPE, MEMBER) ((size_t) &((TYPE*)0)->MEMBER)

#define CONTAINER_OF(ptr, type, member) ({ \
    const typeof(((type*)0)->member)* __mptr = (ptr); \
    (type*)((char*)__mptr - OFFSET_OF(type, member));\
})

//
#define LIST_ENTRY(ptr, type, member) CONTAINER_OF(ptr, type, member)

#define LIST_FOR_EACH(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

#define LIST_FOR_EACH_PREV(pos, head) \
    for (pos = (head)->prev; pos != (head); pos = pos->prev)

#endif
