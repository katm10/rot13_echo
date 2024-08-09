#ifndef LAKE_PLACID_H
#define LAKE_PLACID_H

// TODO: replace this or find lockfree alternative
// #include <pthread.h>

#define LP_IOCTL_SET_PARAMS 0
#define LP_IOCTL_INIT 1

// TODO: define custom arguments for user space transition
// typedef struct handle_request_t dispatch_args_t;
typedef int (dispatch_fxn_t)(void); 

typedef struct stack {
    void* bottom;
    unsigned int size;
    void* rsp;
} stack;

typedef struct ring_buffer {
    // pthread_mutex_t* lock;
    stack* buffer;
    int head;
    int tail;
    int size;
} ring_buffer;

typedef struct lp_params {
    void* globals_table_addr;
    void* user_function_table_addr;
    ring_buffer* rb_addr;
    void* stack_space;
} lp_params;

// Defined in asm
extern int save_and_switch(dispatch_fxn_t handler, void* rsp, void** old_rsp);
extern void resume_from_slow(void* rsp);

int dequeue_and_dispatch(ring_buffer* rb);
int switch_and_dispatch(dispatch_fxn_t handler);

// extern int save_and_switch(dispatch_args_t event, dispatch_fxn_t handler, void* rsp, void** old_rsp);
// extern int save_and_switch_slow(dispatch_args_t event, dispatch_fxn_t handler, void* rsp, void** old_rsp);

// void* __attribute__((weak)) save_and_switch__addr(void) { return (void*)&save_and_switch;}
// void* __attribute__((weak)) save_and_switch_slow__addr(void) { return (void*)&save_and_switch_slow;}

typedef void (*packet_handler_t)(void*);

stack alloc_stack(void);
void free_stack(stack s);

ring_buffer* create_ring_buffer(int size /*, pthread_mutex_t* lock*/);

#endif