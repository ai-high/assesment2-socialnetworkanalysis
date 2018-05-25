// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


struct PQRep {
	int size;
	ItemPQ *item;  // current item
};

PQ newPQ() {
	PQ *pq;
	if ((pq = malloc(sizeof(PQ))) == NULL) {
		fprintf(stderr, "Error!\n");
	}
	int initial_size = 16;
	pq->item = malloc(sizeof(ItemPQ))*(initial_size + 1);
	pq->size = 0;
	return pq;
}

int PQEmpty(PQ pq) {
	return (pq->size == 0);
}

void addPQ(PQ pq, ItemPQ element) {
	int i = pq->size + 1;
	ItemPQ *item = pq->item;
	item[i] = element;
	while ((item[i]->value > item[i/2]) && (i > 1)) {
		ItemPQ *tmp;
		tmp = item[i/2];
		item[i/2] = item[i];
		item[i] = tmp;
		i = i/2;
	}
	pq->size++;
}

ItemPQ dequeuePQ(PQ pq) {
	ItemPQ *item = pq->item;
	ItemPQ *tmp = item[1];
	item[1] = item[pq->size];
	pq->size--;
	updatePQ(pq, item);
	return tmp;
}

void updatePQ(PQ pq, ItemPQ element) {
	int index = 1;  // (2*1)
	int current;
	ItemPQ *tmp;
	while (current < pq->size) {
		current = 2*index;
		if (item[current] < item[current + 1]) {
			current++;
		}
		if (item[current]->value < item[index]->value) {
			tmp = item[current];
			item[current] = item[index];
			item[index] = tmp;
			index = current;
		} else {
			break;
		}
	}
}

void  showPQ(PQ pq) {
	printf("Value in priority queue:");
	for (int i = 1; i <= pq->size; i++) {
		printf("%d ", pq->item[i]->value);
	}
	printf("\n");
	printf("Key in priority queue:");
	for (int i = 1; i <= pq->size; i++) {
		printf("%d ", pq->item[i]->key);
	}
	printf("\n");
}

void  freePQ(PQ pq) {
	free(pq->item);
	free(pq);
}
