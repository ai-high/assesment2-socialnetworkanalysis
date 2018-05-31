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
	NodeValues *values = malloc(sizeof(NodeValues));
	values->noNodes = numVerticies(g);
	values->values = malloc(sizeof(double)*numVerticies(g));
	int count;
	for (int i = 0; i < numVerticies(g); i++)
	{
		count = 0;
		AdjList out = inIncident(g,i);
		while(out!=NULL) {
			count++;
			out = out->next;
		}
		values->values[i] = count;
	}
	return *values;
}
NodeValues degreeCentrality(Graph g) {
	NodeValues *values = malloc(sizeof(NodeValues));
	values->noNodes = numVerticies(g);
	values->values = malloc(sizeof(double)*numVerticies(g));
	NodeValues in = inDegreeCentrality(g);
	NodeValues out = outDegreeCentrality(g);
	for (int i = 0; i < in.noNodes; i++)
	{
		values->values[i] = in.values[i] + out.values[i];
	}
	return *values;
}

NodeValues closenessCentrality(Graph g){
	NodeValues *values = malloc(sizeof(NodeValues));
	values->noNodes = numVerticies(g);
	values->values = malloc(sizeof(double)*numVerticies(g));
	double count;
	double N = numVerticies(g);
	double n;
	for (int i = 0; i < N; i++)
	{
		count = 0;
		n = 0;
		ShortestPaths paths = dijkstra(g, i);
		for (int j = 0; j < N; j++)
		{
			if (i!=j) {
				count = count + paths.dist[j];
				if (paths.pred[j]!=NULL)
					n++;
			}
		}
		if (n==0) {
			values->values[i] = 0;
		} else {
			values->values[i] = ((n)/(N-1))*((n)/count);
		}
	}
	return *values;
}

NodeValues betweennessCentrality(Graph g){
	NodeValues *values = malloc(sizeof(NodeValues));
	values->noNodes = numVerticies(g);
	values->values = malloc(sizeof(double)*numVerticies(g));

	double numerator[numVerticies(g)-1];
	for (int i = 0; i < numVerticies(g); i++) {
		numerator[i] = 0;
	}
	double count;
	for (int i = 0; i < numVerticies(g); i++) {
		ShortestPaths paths = dijkstra(g, i);
		for (int j = 0; j < numVerticies(g); j++)
		{
			if (i!=j) {
				count = 0;
				if (paths.pred[j]!=NULL) {
					PredNode *tmp = paths.pred[j];
					while(tmp!=NULL){
						count++;
						int x = tmp->v;
						while(x!=i){
							numerator[x]++;
							x = paths.pred[x]->v;
						}
						tmp = tmp->next;
						if(tmp==NULL) {
							for (int i = 0; i < numVerticies(g); i++) {
								if (numerator[i]!=0 && count!=0) {
									values->values[i] = values->values[i] + numerator[i]/count;
								}
								numerator[i] = 0;
							}
						}	
					}
				}
			}
		}

	}


	return *values;
}

NodeValues betweennessCentralityNormalised(Graph g){
	NodeValues values = betweennessCentrality( g);
	double n = numVerticies(g);
	for (int i = 0; i < numVerticies(g); i++) {

		values.values[i] = values.values[i]*(1/((n-1)*(n-2)));


	}
	return values;
}

void showNodeValues(NodeValues values){

	for (int i = 0; i < values.noNodes; i++)
	{
		printf("%d: %lf\n",i,values.values[i]);
	}

}

void freeNodeValues(NodeValues values){

}
