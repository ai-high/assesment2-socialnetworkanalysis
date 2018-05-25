#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    int i;
    PQ pq = newPQ();
    ItemPQ *new = malloc(sizeof(struct ItemPQ));
    new->value = 100;
    srand(time(NULL));
    printf("%d\n", new->value);
    return 0;
}
