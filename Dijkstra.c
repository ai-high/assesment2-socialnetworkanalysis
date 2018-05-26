// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#define INFINITY 9999

ShortestPaths init(Graph g, Vertex v);

ShortestPaths dijkstra(Graph g, Vertex v) {

	ShortestPaths sp = init(g,v);
	
	PQ pq = newPQ();
	ItemPQ item;
	for (int i = 0; i < sp.noNodes; i++) {
		sp.dist[i] = INFINITY;
		sp.pred[i] = NULL;
		item.key = i;
		item.value = INFINITY;
		addPQ(pq, item);
	}
	sp.dist[v] = 0;
	item.key = v;
	item.value = 0;
	updatePQ(pq, item);
	showPQ(pq);
	for (int i = 0; i < sp.noNodes; ++i)
	{
		printf("[%d]",sp.dist[i]);
	}

	return sp;
}

void showShortestPaths(ShortestPaths paths) {

}


void  freeShortestPaths(ShortestPaths paths) {

}

ShortestPaths init(Graph g, Vertex v) {
	ShortestPaths *sp = malloc(sizeof(ShortestPaths));
	sp->src = v;
	sp->noNodes = numVerticies(g);
	sp->dist = malloc(sizeof(int)*numVerticies(g));
	sp->pred = malloc(sizeof(PredNode)*numVerticies(g));
	return *sp;
}