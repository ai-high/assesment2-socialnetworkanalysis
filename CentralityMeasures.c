// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

NodeValues outDegreeCentrality(Graph g){

	NodeValues *values = malloc(sizeof(NodeValues));
	values->noNodes = numVerticies(g);
	values->values = malloc(sizeof(double)*numVerticies(g));
	int count;
	for (int i = 0; i < numVerticies(g); i++)
	{
		count = 0;
		AdjList out = outIncident(g,i);
		while(out!=NULL) {
			count++;
			out = out->next;
		}
		values->values[i] = count;
	}
	return *values;
}
NodeValues inDegreeCentrality(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}
NodeValues degreeCentrality(Graph g) {
	NodeValues throwAway = {0};
	return throwAway;
}

NodeValues closenessCentrality(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

NodeValues betweennessCentrality(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

NodeValues betweennessCentralityNormalised(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

void showNodeValues(NodeValues values){

	for (int i = 0; i < values.noNodes; i++)
	{
		printf("%d: %f\n",i,values.values[i]);
	}

}

void freeNodeValues(NodeValues values){

}
