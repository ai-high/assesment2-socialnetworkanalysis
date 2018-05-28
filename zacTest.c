#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){

	Graph g = newGraph(10);
  	insertEdge(g,1, 2, 1);
  	insertEdge(g,2, 1, 10);
  	insertEdge(g,4, 2, 60);
  	insertEdge(g,3, 2, 6);
  	insertEdge(g,1, 4, 2);
  
  	insertEdge(g,2, 3, 1);
  	insertEdge(g,1, 0, 1);
  	insertEdge(g,0, 4, 2);
  	insertEdge(g,3, 4, 1);
  	insertEdge(g,3, 1, 5);
  	showGraph(g);
	dijkstra(g, 0);


	return 0;
}