#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    PQ pq = newPQ();
    ItemPQ new;
    ItemPQ *change;
    ItemPQ what;

    what.value = 5;
    what.key = 2;
    change = &what;
    addPQ(pq, what);
    printf("ADDING: %d\n", what.value);
    showPQ(pq);

    new.value = 1;
    new.key = 5;
    addPQ(pq, new);
    printf("ADDING: %d\n", new.value);
    showPQ(pq);

    new.value = 3;
    new.key = 1;
    addPQ(pq, new);
    printf("ADDING: %d\n", new.value);
    showPQ(pq);

    new.value = 40;
    new.key = 5;
    addPQ(pq, new);
    printf("REPLACING 1 WITH: %d\n", new.value);
    showPQ(pq);

    new.value = 23;
    new.key = 10;
    addPQ(pq, new);
    printf("ADDING: %d\n", new.value);
    showPQ(pq);

    new.value = 14;
    new.key = 9;
    addPQ(pq, new);
    printf("ADDING: %d\n", new.value);
    showPQ(pq);

    new.value = 8;
    new.key = 6;
    addPQ(pq, new);
    printf("ADDING: %d\n", new.value);
    showPQ(pq);

    printf("CHANGE 5 TO 100\n");
    change->value = 100;
    updatePQ(pq, *change);
    showPQ(pq);

    ItemPQ remove;
    remove = dequeuePQ(pq);
    printf("REMOVING %d\n", remove.value);
    showPQ(pq);

    remove = dequeuePQ(pq);
    printf("REMOVING %d\n", remove.value);
    showPQ(pq);
    return 0;
}
