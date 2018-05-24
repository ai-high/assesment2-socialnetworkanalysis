// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#define INFINITY 9999
#define WTF 25

ShortestPaths init(Graph g, Vertex v);

ShortestPaths dijkstra(Graph g, Vertex v) {

	ShortestPaths sp = init(g,v);
	//PQ pq = newPQ();
	for (int i = 0; i < WTF; i++) {
		sp.dist[i] = INFINITY;
		//Add to PQ
		//addPQ(pq, ItemPQ);
		sp.pred[i] = NULL;
	}
	sp.dist[v] = 0;
	//update PQ now with v
	int newDistance;
	//main loop
	while(PQEmpty(pq)==0){
		//get node from PQ
		curr = dequeuePQ(PQ); //or something to get node
		//go through neighbours of item
		for (int i = 0; i < WTF; i++) {
			if(g->adjListArray[i]!=NULL) {
				newDistance = sp.dist[curr] + /* distance from curr to i */
				if (newDistance < sp.dist[i]) {
					sp.dist[i] = newDistance;
					sp.pred[i] = /* current node */
				}
			}

		}

	}



	return sp;
}

void showShortestPaths(ShortestPaths paths) {

}


void  freeShortestPaths(ShortestPaths paths) {

}

ShortestPaths init(Graph g, Vertex v) {
	ShortestPaths sp;
	if((g= malloc(sizeof(ShortestPaths))) == NULL){
		fprintf(stderr, "Error!!  .... \n");
	}
	sp.src = v;
	sp.noNodes = 0;  //increment as we go
	//sp.dist = malloc(sizeof(int)*g->nVert);
	//sp.pred = malloc(sizeof(PredNode)*g->nVert);
	sp.dist = malloc(sizeof(int)*WTF);
	sp.pred = malloc(sizeof(PredNode)*WTF);
	return sp;

}