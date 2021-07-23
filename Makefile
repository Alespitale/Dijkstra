CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99 -g

all: main.o dijkstra.o cost.o set.o graph.o
		$(CC) $(CFLAGS) -o dijkstra main.o graph.o cost.o dijkstra.o set.o

main.o: main.c dijkstra.h
		$(CC) $(CFLAGS) -c main.c

graph.o: graph.c cost.c
		$(CC) $(CFLAGS) -c graph.c

cost.o: cost.h
		$(CC) $(CFLAGS) -c cost.c

dijkstra.o: dijkstra.c set.h graph.h cost.h
		$(CC) $(CFLAGS) -c dijkstra.c

.PHONY: clean
clean:
		rm -f all main.o graph.o cost.o dijkstra.o
