extern void* __globals_table[1024];
void* sockfd__addr(void){return __globals_table[0];}
void* servaddr__addr(void){return __globals_table[1];}
void* clientaddr__addr(void){return __globals_table[2];}
void* clientlen__addr(void){return __globals_table[3];}
