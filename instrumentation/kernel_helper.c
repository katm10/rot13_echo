
extern void *__kernel_function_table[1024];
extern void *__user_function_table[1024];

extern unsigned long long get_page_offset(void);

void* __translate_function(void* f) {
    // Just double checking we don't try to call a user function from the kernel
    if ((unsigned long long)f > get_page_offset()) {
        // This is in the kernel -- no change
        return f;
    } else {
        // This is in the user space -- translate
        char* faddr = (char*) f;
        faddr -= 12;
        int fast_index = *((int*) faddr);
        // faddr -= 4;
        // int slow_index = *((int*) faddr);

        return __kernel_function_table[fast_index];
    }
}
