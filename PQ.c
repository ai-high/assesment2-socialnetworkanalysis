// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct PQNode *Node;
Node newNode(ItemPQ element);
void reorder(PQ pq,Node n);

struct PQNode {
	ItemPQ item;
	Node next;
};

struct PQRep {
	Node first;
};


PQ newPQ() {
	PQ pq = malloc(sizeof(PQ));
	pq->first = NULL;
	return pq;
}

int PQEmpty(PQ p) {
	if(p->first==NULL) {
		return 1;
	}
	return 0;
}

void addPQ(PQ pq, ItemPQ element) {

	Node tmp = pq->first;
	while(tmp!=NULL) {
		if (tmp->item.key == element.key) {
			updatePQ(pq, element);
			return;
		}
		tmp = tmp->next;
	}

	if(pq->first==NULL) {
		Node new = newNode(element);
		pq->first = new;
	} else {
		Node new = newNode(element);
		Node tmp = pq->first;
		new->next = tmp;
		pq->first = new;
	}
}

ItemPQ dequeuePQ(PQ pq) {
	if (pq->first == NULL) {
		printf("TRIED TO DEQUEUE EMPTY LIST IDIOT\n");
		exit(1);
	}
	Node tmp = pq->first;
	Node trail = NULL;
	int lowest = pq->first->item.value;
	Node save = pq->first;
	ItemPQ dequeued;
	while (tmp!=NULL) {
		if (tmp->item.value < lowest) {
			save = tmp;
			lowest = tmp->item.value;
			printf("lowest: %d\n",lowest);
		}
		trail = tmp;
		tmp = tmp->next;
	}
	dequeued = save->item;
	trail = NULL;
	tmp = pq->first;
	while (tmp!=save) {
		trail = tmp;
		tmp = tmp->next;
	}

	if (trail == NULL) {
		tmp = pq->first;
		pq->first = pq->first->next;
		free(tmp);
	} else {
		trail->next = tmp->next;
		free(tmp);
	}
	return dequeued;
}

void updatePQ(PQ pq, ItemPQ element) {

	Node tmp = pq->first;
	while (tmp!=NULL) {
		if (tmp->item.key == element.key) {
			tmp->item.value = element.value;
			return;
		}
		tmp = tmp->next;
	}

}

void  showPQ(PQ pq) {
	Node tmp = pq->first;
	printf("--------------------------\n");
	while (tmp!=NULL) {
		printf("| key: %d | value: %d |\n",tmp->item.key, tmp->item.value);
		tmp = tmp->next;
	}
	printf("--------------------------\n");
}

void  freePQ(PQ pq) {

}

Node newNode(ItemPQ element) {
	Node new = malloc (sizeof(Node));
	new->item.key = element.key;
	new->item.value = element.value;
	new->next = NULL;
	return new;
}

