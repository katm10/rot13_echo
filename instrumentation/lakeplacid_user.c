#include "lakeplacid.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

ring_buffer* create_ring_buffer(int size /*, pthread_mutex_t* lock*/) {
    ring_buffer* rb = malloc(sizeof(ring_buffer));
    // rb->lock = lock;
    rb->buffer = malloc(size * sizeof(stack));
    // explicitly zero out the buffer
    memset(rb->buffer, 0, size * sizeof(stack));
    rb->head = 0;
    rb->tail = 0;
    rb->size = size;
    return rb;
}

void free_ring_buffer(ring_buffer* rb) {
    free(rb->buffer);
    free(rb);
}

bool is_empty(ring_buffer* rb) {
    // I think this is atomic ???
    return rb->head == rb->tail;
}

void enqueue(ring_buffer* rb, stack stack) {
    // pthread_mutex_lock(rb->lock);
    rb->buffer[rb->tail] = stack;
    rb->tail = (rb->tail + 1) % rb->size;
    // pthread_mutex_unlock(rb->lock);
}

stack dequeue(ring_buffer* rb) {
    // pthread_mutex_lock(rb->lock);
    stack s = rb->buffer[rb->head];
    if (s.rsp == NULL) {
        // pthread_mutex_unlock(rb->lock);
        return s;
    }
    rb->head = (rb->head + 1) % rb->size;
    // pthread_mutex_unlock(rb->lock);
    return s;
}

void enqueue_fxn(ring_buffer* rb, void* rsp) {
    stack s = {NULL, 0, rsp};
    enqueue(rb, s);
}

int dequeue_and_dispatch(ring_buffer* rb) {
    stack s = dequeue(rb);

    if (s.rsp == NULL) {
        return 1;
    }

    resume_from_slow(s.rsp);
    return 0;
}

int mpns_likely(int condition, const char* name, int id, void* old_rsp) {
    return condition;
}

int mpns_unlikely(int condition, const char* name, int id, void* old_rsp) {
    return condition;
}

