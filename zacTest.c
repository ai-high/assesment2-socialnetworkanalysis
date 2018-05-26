#include "Dijkstra.h"
#include "Graph.h"
#include "PQ.h"
#include "GraphVis.h"
#include <stdlib.h>
#include <stdio.h>
int main (void) {

	Graph g = newGraph(5);
  insertEdge(g,1,2,1);
  insertEdge(g,2,1,10);
  insertEdge(g,4,2,60);
  insertEdge(g,4,3,6);
  insertEdge(g,0,4,69);
  showGraph(g);
  dijkstra(g, 2);

	return 0;
}