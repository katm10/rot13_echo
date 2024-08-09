#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "lakeplacid.h"

#define PORT_NUMBER (31850)

ring_buffer* rb;
stack slow_stack, fast_stack = {0};
extern int sockfd;
extern struct sockaddr_in servaddr;
extern struct sockaddr_in clientaddr;
extern int clientlen;

extern void* __globals_table[1024];
void* __user_function_table[1024];

extern void init_user_function_table(void);

int main() {
    // Do the application setup
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return -1;
    }

    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int));

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons((unsigned short)PORT_NUMBER);

    if (bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0)
        return -1;

    clientlen = sizeof(clientaddr);

    // Create the ring buffer
    rb = create_ring_buffer(256);

    // Allocate space for the stacks
    void* stack_space = mmap(NULL, 1024 * 1024 * 256, 
        PROT_READ | PROT_WRITE, 
        MAP_POPULATE | MAP_SHARED | MAP_ANONYMOUS, 
        -1, 0);

    // Populate the user function table
    init_user_function_table();

    // Connect to the kernel driver
    int driver_fd = open("/dev/rot13_driver", 0);
    if(driver_fd < 0) {
        printf("Opening was not possible!\n");
        return -1;
    }

    lp_params params = {
        .globals_table_addr = &__globals_table,
        .user_function_table_addr = &__user_function_table,
        .rb_addr = rb,
        .stack_space = stack_space,
    };

    // Tell it where globals/function addrs are
    ioctl(driver_fd, LP_IOCTL_SET_PARAMS, &params);
    // Start it up
    ioctl(driver_fd, LP_IOCTL_INIT, NULL);
    // TODO: Allocate shared memory and override malloc/free

    // Check the ring buffer for new tasks
    while (1) {
        if (is_empty(rb)) {
            // Wait a bit
            usleep(1000);
            continue;
        }

        dequeue_and_dispatch(rb); 
    }

    close(driver_fd);
    return 0;
}
