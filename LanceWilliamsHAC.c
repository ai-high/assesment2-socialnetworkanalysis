// LanceWilliamsHAC ADT interface for Ass2 (COMP2521)
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "LanceWilliamsHAC.h"
#include "Dijkstra.h"
#define INFINITY 9999

typedef struct CNode *ClusterNode;
typedef struct CLink *ClusterLink;
typedef struct CRep *ClusterRep;

typedef struct GraphRep {
	int nVert;
	AdjList *adjListArray;
} GraphRep;

// struct that links clusters
typedef struct CLink {
	int *clusters;		// array of index of clusters in link
	ClusterNode *head;	// source cluster when merging
	ClusterNode *tail;	// dest cluster when merging
} CLink;

// struct for cluster
typedef struct CNode {
	int index;		
	int *vertices;	// array of all vertices it is holding
	ClusterLink *link;
} CNode;

// struct that holds all clusters
typedef struct CRep {
	int size; 	// # of clusters
	int *ClusterArray;	// array that holds all clusters
} CRep;

// creation of CRep
ClusterRep initClusterRep(int nV) {
	ClusterRep clusterRep;
	if ((clusterRep = malloc(sizeof(CRep))) == NULL) {
		fprintf(stderr, "Error!!  .... \n");
		exit(1);
	}
	clusterRep->ClusterArray = malloc(sizeof(int)*(nV));
	clusterRep->size = 0;
	return clusterRep;
}

// creation of cluster node
ClusterNode initClusterNode(int vertex, int *vertArr) {
	ClusterNode node;
	if ((node = malloc(sizeof(CNode))) == NULL) {
		fprintf(stderr, "Error!!  .... \n");
		exit(1);
	}
	// copies vertices from vertArr into it's own array
	node->vertices = malloc(sizeof(vertArr));
	for (int i = 0; i < sizeof(vertArr); i++){
		node->vertices[i] = vertArr[i];
	}
	// initially, index is the vertex
	node->index = vertex;
	node->link = NULL;
	return node;
}

ClusterNode mergeClusterNodes(int src, int dest) {

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

// calculates initial distance
void initDistance(Graph g, float **dist, int src, int dest) {
	float weight1 = 0;
	float weight2 = 0;
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
		float wt = weight1 + weight2;
		float distance = 1/wt;
		if (weight1 == 0) {
			dist[dest][src] = distance;
			dist[src][dest] = INFINITY;
		} else if (weight2 == 0) {
			dist[src][dest] = distance;
			dist[dest][src] = INFINITY;
		} else {
			dist[src][dest] = dist[dest][src] = distance;
		}
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

	// Calculate distances between each pair of vertices
	float **distanceArr = initDistanceArray(g->nVert);
	for (int i = 0; i < g->nVert; i++) {
		for (int j = 0; j < g->nVert; j++) {
			initDistance(g, distanceArr, i, j);
		}
	}
	// code to test if initDistance() works // it does
	for (int i = 0; i < g->nVert; i++) {
		for (int j = 0; j < g->nVert; j++) {
			printf("[%d][%d] = %.4f\n", i, j, distanceArr[i][j]);
		}
	}
	printf("\n");
												// printf("nVert = %d\n", g->nVert);
	// Create ClusterRep
	ClusterRep clusterRep = initClusterRep(g->nVert);
	int *vertArr = malloc(sizeof(int));
	int vertex;
	// Create individual cluster (every vertex)
	for (int i = 0; i < g->nVert; i++) {
		vertex = vertArr[0] = g->adjListArray[i]->w;
												// printf("%d\n", g->adjListArray[i]->w);
		ClusterNode c = initClusterNode(vertex, vertArr);
		clusterRep->ClusterArray[i] = i;
		clusterRep->size++;
	}
												// printf("clusterrep size = %d\n", clusterRep->size);

	/*
					I DONT KNOW WHAT TO DO ABOUT DISTANCES AHHHH
	*/

	mergeClusterNodes(src, dest);

	// INITIALISE DENDROGRAM
	Dendrogram d = {0};
	return d;
}

void freeDendrogram(Dendrogram d) {
	free(d);
}