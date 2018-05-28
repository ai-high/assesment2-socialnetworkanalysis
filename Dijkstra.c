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
		if (i!=v) {
			sp.dist[i] = INFINITY;
			sp.pred[i] = NULL;
			item.key = i;
			item.value = INFINITY;
			addPQ(pq, item);
		}
	}
	sp.dist[v] = 0;
	item.key = v;
	item.value = 0;
	addPQ(pq, item);
	//showPQ(pq);
	int newDist;
	while (PQEmpty(pq)==0) {
		item = dequeuePQ(pq);
		int src = item.key;
		AdjList verts = outIncident(g, src);
		//printf("_____________________ %d ____________\n\n", src);
		while(verts!=NULL){
			int dest = verts->w;
			newDist = sp.dist[src] + verts->weight;
			if (newDist < sp.dist[dest]) {
				sp.dist[dest] = newDist;
				PredNode *new = malloc(sizeof(PredNode));
				new->v = dest;
				new->next = NULL;
				sp.pred[src] = new; 
			}
			//for (int i = 0; i < sp.noNodes; i++) {
				///printf(" [%d] ",sp.dist[i]);
			//}
			//printf("\n");
			verts = verts->next;
		}
		//showPQ(pq);
	}

	//for (int i = 0; i < sp.noNodes; i++) {
	//	printf(" [%d] ",sp.dist[i]);
	//}
	//printf("\n");

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