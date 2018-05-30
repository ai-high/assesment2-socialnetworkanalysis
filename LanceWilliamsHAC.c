// LanceWilliamsHAC ADT interface for Ass2 (COMP2521)
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "LanceWilliamsHAC.h"
#include "Dijkstra.h"
#define INFINITY 9999

typedef struct DendRep *DendrogramRep;
typedef struct Coords *Coordinates;

typedef struct Coords {
	int x, y;
} Coords;

typedef struct GraphRep {
	int nVert;
	AdjList *adjListArray;
} GraphRep;

typedef struct DendRep {
	int size;
	Dendrogram *dendA;
} DendRep;

Coordinates newCoordinates() {
	Coordinates coord;
	if ((coord = malloc(sizeof(Coords))) == NULL) {
		fprintf(stderr, "ERROR!\n");
		exit(1);
	}
	coord->x = coord->y = -1;
	return coord;
}

DendrogramRep newDendrogramRep(int nVert) {
	DendrogramRep dRep;
	if ((dRep = malloc(sizeof(DendRep))) == NULL) {
		fprintf(stderr, "ERROR!\n");
		exit(1);
	}
	dRep->dendA = malloc(sizeof(DNode)*nVert);
	dRep->size = nVert;
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

Coordinates findClosestClusters(Coordinates coord, float **distanceArr, int size) {
	float smallest = INFINITY;
	int arr_size = size;
	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
			if ((i == j) || (distanceArr[i][j] == -1)) {
				continue;
			}
			if (distanceArr[i][j] < smallest) {
				smallest = distanceArr[i][j];
				coord->x = i;
				coord->y = j;
			}
		}
	}
	return coord;
}

void removeClusters(int x, int y, DendrogramRep dRep) {
	int keep, remove;
	if (x < y) {
		keep = x;
		remove = y;
	} else {
		keep = y;
		remove = x;
	}
	// printf("keep = %d\n", keep);
	
	Dendrogram new = newDendrogram(keep, dRep->dendA[keep], dRep->dendA[remove]);
	dRep->dendA[keep] = new;

	Dendrogram removed = newDendrogram(-1, NULL, NULL);
	dRep->dendA[remove] = removed;
}

void restructureDistanceArr(float **distanceArr, int change, int size) {
	// for row
	for (int i = 0; i < size; i++) {
		if (i == change) {
			continue;
		}
		distanceArr[i][change] = -1;
	}

	// for column
	for (int i = 0; i < size; i++) {
		distanceArr[change][i] = -1;
	}
}

void singleLinkage(float **distanceArr, int x, int y, int size) {
	float smallest;
	// for rows
	for (int i = 0; i < size; i++) {
		float x_value = distanceArr[i][x];
		float y_value = distanceArr[i][y];
		if (x_value == -1) {
			distanceArr[i][x] = distanceArr[i][y];
		} else if (y_value == -1) {
			distanceArr[i][y] = distanceArr[i][x];
		} else if (x_value < y_value) {
			smallest = x_value;
			distanceArr[i][y] = smallest;
		} else {
			smallest = y_value;
			distanceArr[i][x] = smallest;
		}
	}

	// for columns
	for (int i = 0; i < size; i++) {
		float x_value = distanceArr[x][i];
		float y_value = distanceArr[y][i];
		if ((i == x) || (i == y)) {
			continue;
		} else if (x_value == -1) {
			distanceArr[x][i] = distanceArr[y][i];
		} else if (y_value == -1) {
			distanceArr[y][i] = distanceArr[x][i];
		} else if (x_value < y_value) {
			smallest = x_value;
			distanceArr[y][i] = smallest;
		} else {
			smallest = y_value;
			distanceArr[x][i] = smallest;
		}
	}
	int change;
	if (x < y) {
		change = y;
	} else {
		change = x;
	}
	restructureDistanceArr(distanceArr, change, size);
}

void completeLinkage(float **distanceArr, int x, int y, int size) {
	float largest;
	// for rows
	for (int i = 0; i < size; i++) {
		float x_value = distanceArr[i][x];
		float y_value = distanceArr[i][y];
		if (x_value == INFINITY) {
			distanceArr[i][x] = distanceArr[i][y];
		} else if (y_value == INFINITY) {
			distanceArr[i][y] = distanceArr[i][x];
		} else if (x_value > y_value) {
			largest = x_value;
			distanceArr[i][y] = largest;
		} else {
			largest = y_value;
			distanceArr[i][x] = largest;
		}
	}

	// for columns
	for (int i = 0; i < size; i++) {
		float x_value = distanceArr[x][i];
		float y_value = distanceArr[y][i];
		if ((i == x) || (i == y)) {
			continue;
		} else if (x_value == INFINITY) {
			distanceArr[x][i] = distanceArr[y][i];
		} else if (y_value == INFINITY) {
			distanceArr[y][i] = distanceArr[x][i];
		} else if (x_value > y_value) {
			largest = x_value;
			distanceArr[y][i] = largest;
		} else {
			largest = y_value;
			distanceArr[x][i] = largest;
		}
	}
	int change;
	if (x < y) {
		change = y;
	} else {
		change = x;
	}
	restructureDistanceArr(distanceArr, change, size);
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

	// // code to test if initDistance() works //
	// for (int i = 0; i < g->nVert; i++) {
	// 	for (int j = 0; j < g->nVert; j++) {
	// 		printf("[%d][%d] = %.4f ", i, j, distanceArr[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");
	// // -------------it works------------- //

	// make a struct that will hold the dendrograms --- index is equal to vertex
	DendrogramRep dRep = newDendrogramRep(g->nVert);
	for (int i = 0; i < g->nVert; i++) {
		int placeholder = g->adjListArray[i]->w;
		Dendrogram d = newDendrogram(placeholder, NULL, NULL);
		dRep->dendA[placeholder] = d;
	}
	// printf("dRep->dendA[0]->vertex = %d\n", dRep->dendA[0]->vertex);
	// if (dRep->dendA[0]->left == NULL) {
	// 	printf("kekekeke\n");
	// }
	// printf("for dendA[0], left value is %d and right value is %d\n", dRep->dendA[0]->left, dRep->dendA[0]->right);
	// printf("dRep->dendA[1]->vertex = %d\n", dRep->dendA[1]->vertex);
	// printf("for dendA[1], left value is %d and right value is %d\n", dRep->dendA[1]->left->vertex, dRep->dendA[1]->right->vertex);
	// printf("dRep->dendA[2]->vertex = %d\n", dRep->dendA[2]->vertex);
	// printf("for dendA[2], left value is %d and right value is %d\n", dRep->dendA[2]->left->vertex, dRep->dendA[2]->right->vertex);
	// printf("dRep->dendA[3]->vertex = %d\n", dRep->dendA[3]->vertex);
	// printf("for dendA[3], left value is %d and right value is %d\n", dRep->dendA[3]->left->vertex, dRep->dendA[3]->right->vertex);
	// printf("dRep->dendA[4]->vertex = %d\n", dRep->dendA[4]->vertex);
	// printf("for dendA[4], left value is %d and right value is %d\n", dRep->dendA[4]->left->vertex, dRep->dendA[4]->right->vertex);

	// FOR LOOP TO FIND CLOSET CLUSTER AND UPDATE DENDROGRAM
	printf("nVert = %d\n", g->nVert);
	for (int k = 1; k < g->nVert; k++) {
	// for (int k = 1; k < 2; k++) {
		printf("k = %d\n", k);
		Coordinates coord = newCoordinates();
		// do a check if coord doesn't find anything!!!!!!

		// find both clusters
		coord = findClosestClusters(coord, distanceArr, g->nVert);
		printf("i = %d, j = %d\n", coord->x, coord->y);
		if ((coord->x == -1) && (coord->y == -1)) {
			exit(1);
		}
		// remove both clusters and merge them, then add it to the index of whichever was smaller
		removeClusters(coord->x, coord->y, dRep);
		// resize array to n-1
		// dRep->size--;
		// update distanceArr using Lance-Williams method
		if (method == 1) {
			singleLinkage(distanceArr, coord->x, coord->y, g->nVert);
		} else {
			completeLinkage(distanceArr, coord->x, coord->y, g->nVert);
		}

		// for (int i = 0; i < g->nVert; i++) {
		// 	for (int j = 0; j < g->nVert; j++) {
		// 		printf("[%d][%d] = %.4f ", i, j, distanceArr[i][j]);
		// 	}
		// 	printf("\n");
		// }
		// printf("\n");
	}
	return dRep->dendA[0];
}

void freeDendrogram(Dendrogram d) {
	free(d);
}