#define PAGE_OFFSET 0x800000000000 // TODO: fill in based on kernel module output

void *__kernel_function_table[1024] = {0};
void *__user_function_table[1024] = {0};

int search_kernel_table(void* f) {
    // The function tables aren't necessarily sorted
    // Find the kernel function closest to f but still less than f
    int indx = -1;
    unsigned long min_diff = -1;
    for (int i = 0; i < 1024; i++) {
        if (__kernel_function_table[i] == 0) {
            return indx;
        } else if (
          // the function should be less than f
          __kernel_function_table[i] <= f &&
          // and it should be closer to f than the current closest
          (indx == -1 || f - __kernel_function_table[i] < min_diff)
        ) {
            indx = i;
            min_diff = f - __kernel_function_table[i];
        }
    }
    return indx;
}

int search_kernel_table_exact(void* f) {
    for (int i = 0; i < 1024; i++) {
        if (__kernel_function_table[i] == 0) {
            return -1;
        } else if (__kernel_function_table[i] == f) {
            return i;
        }
    }
}

void* __translate_function(void* f) {
    // Double check that f is a user function
    if (f <= PAGE_OFFSET) {
        return f;
    } else {
        int indx = search_kernel_table_exact(f);
        if (indx == -1) {
            return f;
        }
        return __user_function_table[indx];
    }
}

void* translate_return_addr(void *old_eip) {
    // The stack probably still has references to kernel addrs

    if (old_eip <= PAGE_OFFSET) {
        // This is a user address
        return old_eip;
    }

    int kernel_indx = search_kernel_table(old_eip);
    if (kernel_indx == -1) {
        return old_eip;
    }

    // TODO: there should be a mapping between user and kernel indices
    // for now, just use the same index

    void* new_fxn_start = __user_function_table[kernel_indx];
    void* res = new_fxn_start + (old_eip - __kernel_function_table[kernel_indx]);
    return res;
}
