#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Graph.h"

/*typedef struct node {

	int x;
	struct node* next;

} Node;*/




int main(void){


	Graph g = newGraph(5);

	printf("Inserting 0 to 1\n");
	insertEdge(g, 0, 1, 1);

	printf("Inserting 0 to 2\n");
	insertEdge(g, 0, 2, 1);

	printf("Inserting 0 to 3\n");
	insertEdge(g, 0, 3, 1);

	printf("Inserting 0 to 4\n");
	insertEdge(g, 0, 4, 1);

	printf("Inserting 4 to 0\n");
	insertEdge(g, 4, 0, 1);
	insertEdge(g, 4, 2, 1);
	insertEdge(g, 4, 3, 1);
	insertEdge(g, 4, 1, 1);
	insertEdge(g, 4, 333, 1);
	insertEdge(g, 0, 0, 1);

	showGraph(g);

	removeEdge(g,4,0);

	showGraph(g);
	removeEdge(g,3,0);
	removeEdge(g,2,0);
	removeEdge(g,1,0);
	removeEdge(g,4,1);
	showGraph(g);
	removeEdge(g,1,4);
	removeEdge(g,4,1);
	removeEdge(g,4,3);
	removeEdge(g,4,2);

	showGraph(g);









}

