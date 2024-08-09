extern int sockfd;
extern int servaddr;
extern int clientaddr;
extern int clientlen;
void * __globals_table[1024] = {
(void*)&sockfd,
(void*)&servaddr,
(void*)&clientaddr,
(void*)&clientlen,
};
