#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    PQ pq = newPQ();
    ItemPQ new;
    // ItemPQ *change;
    // ItemPQ what;

    new.value = 5;
    new.key = 2;
    addPQ(pq, new);
    showPQ(pq);

    new.value = 1;
    new.key = 5;
    addPQ(pq, new);
    showPQ(pq);

    new.value = 3;
    new.key = 1;
    addPQ(pq, new);
    showPQ(pq);

    new.value = 2;
    new.key = 5;
    addPQ(pq, new);
    showPQ(pq);

    freePQ(pq);
    return 0;
    // printf("CHANGE ONE VALUE\n");
    // change->value = 100;
    // updatePQ(pq, *change);
    // showPQ(pq);

    // ItemPQ remove;
    // remove = dequeuePQ(pq);
    // printf("REMOVING %d\n", remove.value);
    // showPQ(pq);

    // remove = dequeuePQ(pq);
    // printf("REMOVING %d\n", remove.value);
    // showPQ(pq);
}
