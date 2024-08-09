// Client side implementation of UDP client-server model                                                                                                                                                            
#include <stdio.h>                                                                                                                                                                                                  
#include <stdlib.h>                                                                                                                                                                                                 
#include <unistd.h>                                                                                                                                                                                                 
#include <string.h>                                                                                                                                                                                                 
#include <sys/types.h>                                                                                                                                                                                              
#include <sys/socket.h>                                                                                                                                                                                             
                                                                                                                                                                                                                    
#include <arpa/inet.h>                                                                                                                                                                                              
#include <netinet/in.h>                                                                                                                                                                                             
#include <sys/time.h>                                                                                                                                                                                               
                                                                                                                                                                                                                    
#define PORT     31850                                                                                                                                                                                              
#define MAXLINE 2048                                                                                                                                                                                                
#define TOTAL_REQUESTS (10000)                                                                                                                                                                                      
//#define TOTAL_REQUESTS (1)                                                                                                                                                                                        

#define DEBUG 1                                                                                                                                                                                   
                                                                                                                                                                                                                    
long long time_log[TOTAL_REQUESTS];                                                                                                                                                                                 
                                                                                                                                                                                                                    
long long get_time_in_us(void) {                                                                                                                                                                                    
        struct timeval tv;                                                                                                                                                                                          
        gettimeofday(&tv, NULL);                                                                                                                                                                                    
        return tv.tv_sec * 1000000 + tv.tv_usec;                                                                                                                                                                    
}                                                                                                                                                                                                                   
                                                                                                                                                                                                                    
void sort_time_array(void) {                                                                                                                                                                                        
        int i, j;                                                                                                                                                                                                   
        if (time_log == NULL)                                                                                                                                                                                       
                return;                                                                                                                                                                                             
        for (i = 0; i < TOTAL_REQUESTS; i++) {                                                                                                                                                                      
                for (j = i+1; j < TOTAL_REQUESTS; j++) {                                                                                                                                                            
                        if (time_log[i] > time_log[j]) {                                                                                                                                                            
                                long long temp = time_log[i];                                                                                                                                                       
                                time_log[i] = time_log[j];                                                                                                                                                          
                                time_log[j] = temp;                                                                                                                                                                 
                        }                                                                                                                                                                                           
                }                                                                                                                                                                                                   
        }                                                                                                                                                                                                           
}                                                                                                                                                                                                                   
                                                                                                                                                                                                                    
int main(int argc, char* argv[]) {                                                                                                                                                                                  
        int sockfd;                                                                                                                                                                                                 
        char buffer[MAXLINE];                                                                                                                                                                                       
        char buffer_send[MAXLINE];                                                                                                                                                                                  
                                                                                                                                                                                                                    
        struct sockaddr_in servaddr;                                                                                                                                                                                
                                                                                                                                                                                                                    
        if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
                perror("socket creation failed"); 
                exit(EXIT_FAILURE); 
        } 
        int disable = 1;
/*
        if (setsockopt(sockfd, SOL_SOCKET, SO_NO_CHECK, (void*)&disable, sizeof(disable)) < 0) {
                perror("Error disabling socket checksum");
                exit(EXIT_FAILURE);
        }
*/
        memset(&servaddr, 0, sizeof(servaddr)); 
     
        // Filling server information 
        servaddr.sin_family = AF_INET; 
        servaddr.sin_port = htons(PORT); 
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

#ifdef DEBUG
        // Send a message from argv to the server instead
        if (argc < 2) {
                printf("Usage: %s <message>\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        sendto(sockfd, (const char *)argv[1], strlen(argv[1]), 
                        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
                        sizeof(servaddr));

        int n, len;
        len = sizeof(servaddr);
        n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, (struct sockaddr *) &servaddr, 
                &len);

        buffer[n] = '\0';
        printf("response : %s\n", buffer);
#else
        int n, len, out_len;
        len = sizeof(servaddr);
        out_len = 1024;
        //memset(buffer_send, 'x', 1024);
        for (int i = 0; i < 1024; i++) {
                buffer_send[i] = i % 26 + 'a';
        }
    
        for (int i = 0; i < TOTAL_REQUESTS; i++) { 
                long long start = get_time_in_us(); 
                sendto(sockfd, (const char *)buffer_send, out_len, 
                                MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
                                sizeof(servaddr)); 
                n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                        MSG_WAITALL, (struct sockaddr *) &servaddr, 
                        &len);

                long long end = get_time_in_us();
                time_log[i] = end-start;
        }
#endif
        close(sockfd);

#ifndef DEBUG
        int i;
        printf("Received = %d\n", n);
        for (i = 0; i < n; i++) {
                printf("%c", buffer[i]);
        }
        printf("\n");
        sort_time_array();

        for (i = 0; i < TOTAL_REQUESTS; i++) {
                printf("%lld\n", time_log[i]);
        }
#endif
        return 0;
}
