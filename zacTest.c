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

	printf("%d\n",numVerticies(g));
	insertEdge(g, 0, 1, 1);
	insertEdge(g, 0, 1, 1);






}

