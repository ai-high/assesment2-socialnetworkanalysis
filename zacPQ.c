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

	if(pq->first==NULL) {
		Node new = newNode(element);
		pq->first = new;
	} else {
		Node tmp = pq->first;
		Node trail = NULL;
		while(tmp!=NULL && tmp->item.value <= element.value) {
			if (tmp->item.key == element.key) {
				tmp->item.value = element.value;
				return;
			}
			trail = tmp;
			tmp = tmp->next;
		}
		Node new = newNode(element);
		if(tmp==NULL) {
			trail->next = new;
			new->next = NULL;
			return;
		}
		if (tmp == pq->first) {
			pq->first = new;
			new->next = tmp;
			return;
		}
		trail->next = new;
		new->next = tmp;
	}
}

ItemPQ dequeuePQ(PQ pq) {
	Node tmp = pq->first;
	pq->first = pq->first->next;
	return tmp->item;
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

void reorder(PQ pq,Node n) {
	ItemPQ item;
	item.key = n->item.key;
	item.value = n->item.value;
	Node tmp = pq->first;
	if(tmp==n){
		Node new = newNode(item);
		tmp = n->next;
		pq->first = new;
		new->next = tmp;
	}
	while(tmp->next!=n && tmp!=NULL) {
		tmp = tmp->next;
	}
	

}