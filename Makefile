all: server

server.o: server.c
	gcc -c server.c -I instrumentation -o server.o

server: server.o
	gcc server.o -o server
