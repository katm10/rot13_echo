extern void* __kernel_function_table[1024];
extern void* handle_request__addr(void);
void init_kernel_function_table(void) {
    __kernel_function_table[0] = handle_request__addr();
}