#include "LanceWilliamsHAC.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	Graph g = readGraph("graphs/2.in");
	Dendrogram d = LanceWilliamsHAC(g, 1);

	return 0;
}