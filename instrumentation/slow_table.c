extern void* __user_function_table[1024];
extern void* handle_request__addr(void);
void init_user_function_table(void) {
    __user_function_table[0] = handle_request__addr();
}