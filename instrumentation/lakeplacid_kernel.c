#include "lakeplacid.h"

extern void* stack_space;
extern stack fast_stack;
unsigned short used_stacks[32] = {0};

void enqueue(ring_buffer* rb, stack stack) {
    // pthread_mutex_lock(rb->lock);
    rb->buffer[rb->tail] = stack;
    rb->tail = (rb->tail + 1) % rb->size;
    // pthread_mutex_unlock(rb->lock);
}

void enqueue_fxn(ring_buffer* rb, void* rsp) {
    stack s = {0, 0, rsp};
    enqueue(rb, s);
}

stack alloc_stack() {
    stack s = {0};
    unsigned int size = 8 * 1024 * 1024;
    int i, j = 0;
    for (i = 0; i < 32; i++) {
        if (used_stacks[i] == 0) {
            used_stacks[i] = 1;
            unsigned long long stack_bottom = (unsigned long long)stack_space + (size * i);
            stack s = {stack_bottom, size, stack_bottom + size};
            for (j = 0; j < size / 8; j++) {
                ((unsigned long long*)stack_bottom)[j] = 0;
            }
            return s;
        }
    }
    // TODO: error
    return s;
}

void free_stack(stack s) {
    // sometimes bottom and size get corrupted, so just use rsp here
    unsigned int indx = ((unsigned long long)s.rsp - (unsigned long long)stack_space) / 8 / 1024 / 1024;
    used_stacks[indx] = 0;
}

int switch_and_dispatch(dispatch_fxn_t handler){
    // Allocate a new stack
    stack s = alloc_stack();

    int res = save_and_switch(handler, s.rsp, &fast_stack.rsp);

    // Free the stack ONLY if this succeeded!
    if (res == 0) {
        free_stack(s);
    }

    return res;
}

