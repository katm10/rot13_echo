#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "instrumentation/lakeplacid.h"

#define PORT_NUMBER (31850)

// extern void __trace_begin(const char*);
// extern void __trace_end();

extern stack fast_stack;

int sockfd;
struct sockaddr_in servaddr;
struct sockaddr_in clientaddr;
int clientlen = sizeof(clientaddr);

int handle_request(void) {
    char buffer[2048];

    int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*) &clientaddr, &clientlen);
    if (n < 0) {
        return -1;
    }

    if (buffer[0] == '?') {
        for (int i = 0; i < n; i++) {
            if (buffer[i] >= 'A' && buffer[i] <= 'Z') {
                buffer[i] = 'A' + (buffer[i] - 'A' + 13) % 26;
            } else if (buffer[i] >= 'a' && buffer[i] <= 'z') {
                buffer[i] = 'a' + (buffer[i] - 'a' + 13) % 26;
            }
        }
    }

    n = sendto(sockfd, buffer, n, 0, (struct sockaddr*) &clientaddr, clientlen);
    if (n < 0) {
        return -1;
    }

    return 0;
}

int main(int argc, char* argv[]) {
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

    while(1) {
        // __trace_begin("handle_request");
        int res = handle_request();
        // __trace_end();
        if (res < 0) {
            return -1;
        }
    }

    return 0;
}
