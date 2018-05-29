#ifndef GRAPH
	#define GRAPH
	#include "Graph.h"
#endif
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



int main(){
	// some very simple code to show you
	// how to use graph vis

  /*Graph g = newGraph(10);
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
  showGraph(g);*/

  Graph g = readGraph("graphs/6.in");

	// draws the graph
  graphVis(g, DEFAULT);
	return EXIT_SUCCESS;
}
