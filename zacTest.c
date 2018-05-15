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
	//insertEdge(g, 0, 3, 1);

	printf("Inserting 0 to 4\n");

	printf("Inserting 4 to 0\n");

	insertEdge(g, 2, 4, 1);
	insertEdge(g, 4, 3, 1);
	insertEdge(g, 1, 4, 1);
	insertEdge(g, 4, 333, 1);
	insertEdge(g, 0, 0, 1);

	showGraph(g);

	printf("%d\n",adjacent(g,4,0));
	printf("%d\n",adjacent(g,3,2));

	inIncident(g,0);

	freeGraph(g);











}

