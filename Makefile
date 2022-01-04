clean:
	rm -f *.o main

all: graph

graph: main.o nodes.o graph.o
	gcc -Wall -g -o graph main.o nodes.o graph.o

main.o: main.c graph.h nodes.h
	gcc -Wall -g -c main.c

graph.o: graph.c graph.h
	gcc -Wall -g -c graph.c

nodes.o: nodes.c nodes.h graph.h
	gcc -Wall -g -c nodes.c