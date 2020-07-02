#include "stats.h"
#include <stdio.h>
#include <stdlib.h>

int numberOfVertices(char name[])
{
    int i, j, max = 0, max_;
    int p1, p2, wei;
    FILE* g = fopen(name, "r");
    while (fscanf(g, "%d%d%d", &p1, &p2, &wei) != EOF) {
        max_ = p1 > p2 ? p1 : p2;
        max = max_ > max ? max_ : max;
    }
    return max + 1;
}