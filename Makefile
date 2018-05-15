# Makefile for Ass2

CC = gcc
CFLAGS =  -Wall -std=c11 -Werror -g
AR = ar
objs = Graph.o GraphVis.o CentralityMeasures.o PQ.o Dijkstra.o

all : testGraph testPQ testDijkstra testCentralityMeasures

$(objs) : %.o : %.c

GraphLib.a : $(objs)
	$(AR) rcs $@ $^

testGraph : testGraph.c GraphLib.a
	$(CC) -o testGraph testGraph.c GraphLib.a

testPQ : testPQ.c PQ.o
	$(CC) -o testPQ  testPQ.c PQ.o

testDijkstra : testDijkstra.c GraphLib.a
	$(CC) -o  testDijkstra testDijkstra.c GraphLib.a

testCentralityMeasures : testCentralityMeasures.c GraphLib.a
	$(CC) -o testCentralityMeasures testCentralityMeasures.c GraphLib.a

clean :
	rm -f *.o testCentralityMeasures testDijkstra testGraph testPQ GraphLib.a
