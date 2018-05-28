#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    PQ pq = newPQ();
    ItemPQ new;
    new.value = 100;
    new.key = 1;
    addPQ(pq, new);
    showPQ(pq);
    new.value = 1;
    new.key = 2;
    addPQ(pq, new);
    showPQ(pq);
    new.value = 4;
    new.key = 3;
    addPQ(pq, new);
    showPQ(pq);
    new.value = 69;
    new.key = 1;
    addPQ(pq, new);
    showPQ(pq);
    return 0;
}
