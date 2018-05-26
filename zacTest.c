#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){

	Graph g = newGraph(5);
  	insertEdge(g,1,2,1);
  	insertEdge(g,2,1,10);
  	insertEdge(g,4,2,60);
  	insertEdge(g,3,2,6);
  	insertEdge(g,0,4,69);
	showGraph(g);
	PQ p = newPQ();
	ItemPQ new;
	new.key = 0;
	new.value = 10;
	addPQ(p,new);
	showPQ(p);
	new.key = 1;
	new.value = 2;
	addPQ(p,new);
	showPQ(p);
	new.key = 2;
	new.value = 16;
	addPQ(p,new);
	showPQ(p);
	new.key = 3;
	new.value = 4;
	addPQ(p,new);
	showPQ(p);
	dijkstra(g, 2);


	return 0;
}