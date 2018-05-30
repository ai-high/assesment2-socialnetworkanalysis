// LanceWilliamsHAC ADT interface for Ass2 (COMP2521)
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "LanceWilliamsHAC.h"
#include "Dijkstra.h"
#define INFINITY 9999

typedef struct DendRep *DendrogramRep;

typedef struct GraphRep {
	int nVert;
	AdjList *adjListArray;
} GraphRep;

typedef struct DendRep {
	int size;
	Dendrogram *dendA;
} DendRep;

DendrogramRep newDendrogramRep(int nVert) {
	DendrogramRep dRep;
	if ((dRep = malloc(sizeof(DendRep))) == NULL) {
		fprintf(stderr, "ERROR!\n");
		exit(1);
	}
	dRep->dendA = malloc(sizeof(DNode)*nVert);
	dRep->size = 0;
	return dRep;
}

Dendrogram newDendrogram(int vertex, Dendrogram left, Dendrogram right) {
	Dendrogram d;
	if ((d = malloc(sizeof(DNode))) == NULL) {
		fprintf(stderr, "ERROR!\n");
		exit(1);
	}
	d->vertex = vertex;
	d->left = left;
	d->right = right;
	return d;
}

// initialse a new array to hold distances
float **initDistanceArray(int nVert) {
	assert(nVert > 0);
	float **dist;
	dist = malloc(nVert*sizeof(float *));
	assert(dist != 0);
	for (int i = 0; i < nVert; i++) {
		dist[i] = malloc(nVert*sizeof(float));
		assert(dist[i] != 0);
		for (int j = 0; j < nVert; j++) {
			dist[i][j] = 0;
		}
	}
	return dist;
}

// return edge we are looking for
AdjList findEdge(Graph g, Vertex src, Vertex dest) {
	AdjList tmp = g->adjListArray[src];
	while (tmp != NULL) {
		if (tmp->w == dest) {
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

// calculates initial distance array
void initDistance(Graph g, float **dist, int src, int dest) {
	float weight1 = 0;
	float weight2 = 0;
	float wt;
	AdjList tmp;
	if ((tmp = findEdge(g, src, dest)) != NULL) {
		weight1 = tmp->weight;
	}
	if ((tmp = findEdge(g, dest, src)) != NULL) {
		weight2 = tmp->weight;
	}
	if ((weight1 == 0) && (weight2 == 0)) {
		dist[src][dest] = dist[dest][src] = INFINITY;
	} else {
		if (weight1 > weight2) {
			wt = weight1;
		} else {
			wt = weight2;
		}
		float distance = 1/wt;
		dist[src][dest] = dist[dest][src] = distance;
	}
}

// method = 1 represents "single linkage" and method = 2 represents "complete linkage"
Dendrogram LanceWilliamsHAC(Graph g, int method) {
	/*Calculate distances between each pair of vertices
	  Create clusters for every vertex i, c[i]
	  Let Dist(c[i], c[j]) represent the distance between cluster c[i] and c[j], initially it will represent the distance between i and j
	  for k=1 to n-1:
	  	find two closest clusters, eg. c[i] and c[j]. If there are multiple alternatives, you can select any one of the pairs
	  	remove clusters c[i], c[j] from the collection and add a new cluster c[i+j] (with all vertices c[i] and c[j]) to the collection of clusters
	  	update dendrogram
	  	update distances, say Dist(c[i+j], c[k]), between the newly added cluster c[i+j] and the rest of the clusters c[k] into the collection using Lance-Williams formula
	  end for
	  return dendrogram*/

	// Calculate initial distances between each pair of vertices
	float **distanceArr = initDistanceArray(g->nVert);
	for (int i = 0; i < g->nVert; i++) {
		for (int j = 0; j < g->nVert; j++) {
			initDistance(g, distanceArr, i, j);
		}
	}

	// code to test if initDistance() works //
	for (int i = 0; i < g->nVert; i++) {
		for (int j = 0; j < g->nVert; j++) {
			printf("[%d][%d] = %.4f ", i, j, distanceArr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	// -------------it works------------- //

	// make a struct that will hold the dendrograms --- index is equal to vertex
	DendrogramRep dRep = newDendrogramRep(g->nVert);
	for (int i = 0; i < g->nVert; i++) {
		int placeholder = g->adjListArray[i]->w;
		Dendrogram d = newDendrogram(placeholder, NULL, NULL);
		dRep->dendA[placeholder] = d;
	}
	// printf("dRep->dendA[0]->vertex = %d\n", dRep->dendA[0]->vertex);

	return dRep->dendA[0];
}

void freeDendrogram(Dendrogram d) {

}