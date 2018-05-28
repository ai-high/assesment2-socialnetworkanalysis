#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    PQ pq = newPQ();
    ItemPQ new;
    ItemPQ *change;
    ItemPQ what;

    new.value = 1;
    new.key = 2;
    addPQ(pq, new);
    showPQ(pq);

    new.value = 2;
    new.key = 5;
    addPQ(pq, new);
    showPQ(pq);

    what.value = 3;
    what.key = 1;
    change = &what;
    addPQ(pq, what);
    showPQ(pq);

    new.value = 4;
    new.key = 9;
    addPQ(pq, new);
    showPQ(pq);

    new.value = 5;
    new.key = 10;
    addPQ(pq, new);
    showPQ(pq);

    new.value = 6;
    new.key = 4;
    addPQ(pq, new);
    showPQ(pq);

    new.value = 7;
    new.key = 3;
    addPQ(pq, new);
    showPQ(pq);
   
    printf("CHANGE ONE VALUE\n");
    change->value = 100;
    updatePQ(pq, *change);
    showPQ(pq);

    ItemPQ remove;
    remove = dequeuePQ(pq);
    printf("REMOVING %d\n", remove.value);
    showPQ(pq);
    return 0;
}
