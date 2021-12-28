clean:
	rm -f *.o main

main: main.o nodes.o graph.o
	gcc -Wall -o main main.o nodes.o graph.o

main.o: main.c graph.h nodes.h
	gcc -Wall -c main.c

graph.o: graph.c graph.h
	gcc -Wall -c graph.c

nodes.o: nodes.c nodes.h graph.h
	gcc -Wall -c nodes.c