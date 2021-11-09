#compiler
CC = gcc

#flags
CFLAGS = -Wall -Wextra -Werror -Wno-comment -Wno-error=comment

test: graphs.o graph_tester.o
	$(CC) $(CFLAGS) graphs.o graph_tester.o -o tester.out

graphs.o: graphs.c graphs.h
	$(CC) $(CFLAGS) -c graphs.c

graph_tester.o: graph_tester.c
	$(CC) $(CFLAGS) -c graph_tester.c

