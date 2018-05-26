// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

typedef struct PQRep {
	int size;
	ItemPQ *item;
} PQRep;

// yeah nah

PQ newPQ() {
	PQ pq;
	if ((pq = malloc(sizeof(PQ))) == NULL) {
		fprintf(stderr, "Error!\n");
	}
	int initial_size = 16;
	pq->item = malloc(sizeof(ItemPQ)*(initial_size + 1));
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
	while ((item[i].value < item[i/2].value) && (i > 1)) {
		ItemPQ tmp;
		tmp = item[i/2];
		item[i/2] = item[i];
		item[i] = tmp;
		i = i/2;
	}
	pq->size++;
}

ItemPQ dequeuePQ(PQ pq) {
	ItemPQ returned = pq->item[1];
	pq->item[1] = pq->item[pq->size];
	pq->size--;
	ItemPQ tmp;
	updatePQ(pq, tmp);
	return returned;
}

void updatePQ(PQ pq, ItemPQ element) {
	int index = 1;
	int current = 0;
	ItemPQ tmp;
	// ItemPQ *item = element;
	while (current < pq->size) {
		current = 2*index;
		if (pq->item[current].value > pq->item[current + 1].value) {
			current++;
		}
		if (pq->item[current].value < pq->item[index].value) {
			tmp = pq->item[current];
			pq->item[current] = pq->item[index];
			pq->item[index] = tmp;
			index = current;
		} else {
			break;
		}
	}
}

void  showPQ(PQ pq) {
	/*printf("Value in priority queue: ");
	for (int i = 1; i <= pq->size; i++) {
		printf("%d ", pq->item[i].value);
	}
	printf("\n");
	// printf("Key in priority queue: ");
	// for (int i = 1; i <= pq->size; i++) {
	// 	printf("%d ", pq->item[i].key);
	// }
	printf("\n");*/
    for (int i = 1; i <= pq->size; i++) {
        printf("| key: %d | value: %d |\n",pq->item[i].key, pq->item[i].value);
    }
    printf("\n");

}

void  freePQ(PQ pq) {
	free(pq->item);
	free(pq);
}

/*int main(void) {
    int i;
    PQ pq = newPQ();
    ItemPQ new;
    srand(time(NULL));
    for (i = 1; i < 9; i++) {
        new.value = rand()%10000;
        printf("add node with value: %d\n", new.value);
        addPQ(pq, new);
    }
    showPQ(pq);
    printf("\ndequeue all values:\n");
    for (i = 1; i < 9; i++) {
        new = dequeuePQ(pq);
        printf("remove node with value: %d, queue size after removal: %d\n", new.value, pq->size);
        showPQ(pq);
    }
    freePQ(pq);

    // PQ pq = newPQ();
    // ItemPQ new;
    // srand(time(NULL));
    // new.value = rand()%100;
    // printf("adding %d\n", new.value);
    // addPQ(pq, new);

    // showPQ(pq);
    // new.value = rand()%100;
    // printf("adding %d\n", new.value);
    // addPQ(pq, new);

    // showPQ(pq);
    // // printf("second: %d\n\n", pq->item[pq->size/2].value);
    // new.value = rand()%100;
    // printf("adding %d\n", new.value);
    // addPQ(pq, new);

    // showPQ(pq);
    // // printf("second: %d\n\n", pq->item[pq->size/2].value);
    // new.value = rand()%100;
    // printf("adding %d\n", new.value);
    // addPQ(pq, new);

    // showPQ(pq);
    // // printf("second: %d\n\n", pq->item[pq->size/2].value);
    // new.value = rand()%100;
    // printf("adding %d\n", new.value);
    // addPQ(pq, new);

    // showPQ(pq);
    // // printf("second: %d\n\n", pq->item[pq->size/2].value);
    // new.value = rand()%100;
    // printf("adding %d\n", new.value);
    // addPQ(pq, new);

    // showPQ(pq);
    // // printf("second: %d\n\n", pq->item[pq->size/2].value);
    // new.value = rand()%100;
    // printf("adding %d\n", new.value);
    // addPQ(pq, new);

    // showPQ(pq);

    // ItemPQ remove = dequeuePQ(pq);
    // printf("removed %d\n", remove.value);
    // showPQ(pq);

    // remove = dequeuePQ(pq);
    // printf("removed %d\n", remove.value);
    // showPQ(pq);

    // remove = dequeuePQ(pq);
    // printf("removed %d\n", remove.value);
    // showPQ(pq);

    // freePQ(pq);
    return 0;
}*/