// Graph ADT interface for Ass2 (COMP2521)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Graph.h"

typedef struct GraphRep {

	int nVert;
	AdjList * adjListArray;

	// AdjList = adjListNode*

} GraphRep;


Graph newGraph(int noNodes) {


	Graph g;
	if((g= malloc(sizeof(GraphRep))) == NULL){
		fprintf(stderr, "Error!!  .... \n");
	}
	g->nVert = noNodes;

	//malloc and init adjList
	if((g->adjListArray = malloc(sizeof(AdjList)*noNodes)) == NULL){
		fprintf(stderr, "Error!!  .... \n");
	}
	int i = 0;
	while(i<noNodes){
		g->adjListArray[i] = NULL;
		i++;
	}

	return g;
}

int numVerticies(Graph g) {
	return g->nVert;
}

void  insertEdge(Graph g, Vertex src, Vertex dest, int weight) {

	assert(src<=g->nVert);
	assert(dest<=g->nVert);
	// check if dest is in g->adjListArray[src]
	AdjList tmp;
	tmp = g->adjListArray[src];
	while(tmp!=NULL){
		printf("1");
		if (tmp->w==dest) {
			return;
		}
		tmp = tmp->next;
	}


	// add dest to src
	AdjList new = malloc(sizeof(AdjList));
	new->weight = weight;
	new->w = dest;
	new->next = g->adjListArray[src];
	g->adjListArray[src] = new;

	//add scr to dest
	AdjList new2 = malloc(sizeof(AdjList));
	new2->weight = weight;
	new2->w = src;
	new2->next = g->adjListArray[dest];
	g->adjListArray[dest] = new2;

	g->nVert++;

	
}

void  removeEdge(Graph g, Vertex src, Vertex dest) {

	assert(src<=g->nVert);
	assert(dest<=g->nVert);
	// check if dest is in g->adjListArray[src]
	AdjList tmp;
	tmp = g->adjListArray[src];
	while(tmp!=NULL){
		if (tmp->w==dest) {
			//found connecton from v to w
			if(tmp->next==NULL){
				AdjList tmp2 = g->adjListArray[src];
				while (tmp2->next!=tmp){
					tmp2 = tmp2->next;
				}
				//tmp2 pointing before tmp in adjlist
				tmp2->next = NULL;
				free(tmp);
			} else if (tmp==g->adjListArray[src]) {
				g->adjListArray[src] = NULL;
				free(tmp);
			} else {
				AdjList tmp2 = g->adjListArray[src];
				while (tmp2->next!=tmp){
					tmp2 = tmp2->next;
				}
				//tmp2 pointing before tmp in adjlist
				tmp2->next = tmp->next;
				free(tmp);
			}
			g->nVert--;
		}
		tmp = tmp->next;
	}

}

bool adjacent(Graph g, Vertex src, Vertex dest) {
	return false;
}

AdjList outIncident(Graph g, Vertex v) {
	return NULL;
}

AdjList inIncident(Graph g, Vertex v) {
	return NULL;
}

void  showGraph(Graph g) {

}

void  freeGraph(Graph g) {

}