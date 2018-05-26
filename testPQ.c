#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	PQ p = newPQ();
	ItemPQ item = {1,12};
	addPQ(p,item);
	showPQ(p);
	ItemPQ item2 = {2,6};
	addPQ(p,item2);
	showPQ(p);
	ItemPQ item3 = {3,11};
	addPQ(p,item3);
	showPQ(p);
	ItemPQ item4 = {3,69};
	updatePQ(p,item4);
	showPQ(p);
	ItemPQ item5 = {12,69};
	updatePQ(p,item5);
	showPQ(p);
	//int i = PQEmpty(p);
	//printf("\n%d\n",i);
	ItemPQ i = dequeuePQ(p);
	printf("@@@@@@| key: %d | value: %d |\n",i.key, i.value);
	i = dequeuePQ(p);
	printf("@@@@@@| key: %d | value: %d |\n",i.key, i.value);
	i = dequeuePQ(p);
	printf("@@@@@@| key: %d | value: %d |\n",i.key, i.value);

	ItemPQ item6 = {10,20};
	addPQ(p,item6);
	showPQ(p);

  return EXIT_SUCCESS;
}
