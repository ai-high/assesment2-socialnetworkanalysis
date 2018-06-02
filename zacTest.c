#include "Dijkstra.h"
#include "PQ.h"
#include "GraphVis.h"
#include <stdlib.h>
#include <stdio.h>

Graph readGraph(char* file) {
	// ugly count
	FILE * f = fopen(file , "r");
	if(!f){
		fprintf(stderr, "ERROR READING FILE %s\n", file);
		return NULL;
	}
	int lines = 0;
	char ch = 0;
	while(!feof(f)){ch = fgetc(f); if(ch == '\n')lines++;}
	fclose(f);

	//ugly parse
	f = fopen(file , "r");
	if(!f){
		fprintf(stderr, "ERROR READING FILE %s\n", file);
		return NULL;
	}
	int a=0;
	int b=0;
	int c=0;
	int i = 0;
	int maxVert = -1;
	int **nums = malloc(sizeof(int*)*lines);
	for(i=0;i<lines;i++) nums[i] = malloc(sizeof(int)*3);
	i=0;
	while(i < lines) {
		fscanf(f, "%d,", &a);
		fscanf(f, "%d,", &b);
		fscanf(f, "%d", &c);
		if (a > maxVert) maxVert = a;
		if (b > maxVert) maxVert = b;
		nums[i][0] = a;
		nums[i][1] = b;
		nums[i][2] = c;
		i++;
	}
	fclose(f);

	Graph g = newGraph(maxVert+1);
	i = 0;
	while(i < lines) {
		insertEdge(g,nums[i][0],nums[i][1],nums[i][2]);
		i++;
	}
	for(i=0;i<lines;i++) free(nums[i]);
	free(nums);
	return g;
}

int getNumPaths(ShortestPaths paths, int ***passes, int start, int cur, int end){

	if (cur == end) return 1;
	int numPaths = 0;
	PredNode *curNode = paths.pred[cur];
	while (curNode) {
		numPaths += getNumPaths(paths,passes,start,curNode->v,end);
		curNode = curNode->next;
	}
	if (cur!=start){
		passes[start][end][cur] += numPaths;
	}

}


int main(void){

	Graph g = readGraph("graphs/2.in");

	int ***passes = malloc(sizeof(**int)*numVerticies(g));
	int **numPaths = malloc(sizeof(*int)*numVerticies(g));
	for (int i = 0; i < count; ++i)
	{
		passes[i] = malloc(sizeof(*int)*numVerticies(g));
		numPaths[i] =  malloc(sizeof(int)*numVerticies(g));
		for (int j = 0; j < count; ++j)
		{
			numPaths[i][j] = 0;
			passes[i][j] = malloc(sizeof(int)*numVerticies(g));
			for (int k = 0; k < count; ++k)
			{
				passes[i][j][k] = 0;
			}
		}
	}

	for (int s = 0; s < numVerticies(g); ++s) {
		printf("node: %d\n",s);
		ShortestPaths paths = dijkstra(g, s);
		for (int t = 0; t < numVerticies(g); ++t)
		{
			numPaths[s][t] = getNumPaths(paths, passes, s, s, t);
		}
	}

	for (int i = 0; i < count; ++i)
	{
		for (int j = 0; j < count; ++j)
		{
			for (int k = 0; k < count; ++k)
			{
				if (numPaths[i][j]!=0)
				{
					values[k] += passes[i][j][k]/numPaths[i][j];
				}
			}
		}
	}


	return 0;
}






	/*double numerator[numVerticies(g)-1];
	double values[numVerticies(g)-1];
	for (int i = 0; i < numVerticies(g); i++) {
		numerator[i] = 0;
		values[i] = 0;
	}
	double count;
	for (int i = 0; i < numVerticies(g); i++) {
		ShortestPaths paths = dijkstra(g, i);
		for (int j = 0; j < numVerticies(g); j++)
		{
			if (i!=j) {
				printf("%d - %d     ",i,j);
				count = 0;
				if (paths.pred[j]!=NULL) {
					PredNode *tmp = paths.pred[j];
					while(tmp!=NULL){
						count++;
							printf(" [");
							int x = tmp->v;
							while(x!=i){
								printf(" %d ",x);
								numerator[x]++;
								x = paths.pred[x]->v;
							}
							printf("]   ");
							tmp = tmp->next;
							if(tmp==NULL) {
								printf("  %0.1f  ",count);
								for (int i = 0; i < numVerticies(g); i++) {
									if (numerator[i]!=0) {
										printf("\n[%d]:  %lf / %lf\n",i,numerator[i],count);
										values[i] = values[i] + numerator[i]/count;
									}
									//values[i] = values[i] + numerator[i]/count;
									numerator[i] = 0;
								}
							}
					}
				}
				printf("\n");
			}
		}

	}

	for (int i = 0; i < numVerticies(g); i++) {
		printf(" [%lf] ",values[i]);
	}
	printf("\n");*/




	

// gcc zacTest.c Graph.c Graph.h Dijkstra.c Dijkstra.h PQ.h PQ.c
