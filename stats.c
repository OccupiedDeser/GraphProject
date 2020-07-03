#include "stats.h"
#include "search.h"
#include <stdio.h>
#include <stdlib.h>

int numberOfVertices(char name[])
{
    int i, p1, p2, wei, count = 0, _max;
    int* list = (int*)malloc(MAXV * sizeof(int));
    for (i = 0; i < MAXV; i++) {
        list[i] = 0;
    }
    FILE* g = fopen(name, "r");
    while (fscanf(g, "%d%d%d", &p1, &p2, &wei) != EOF) {
        list[p1] = 1;
        list[p2] = 1;
        if (p1 > _max) {
            _max = p1;
        }
        if (p2 > _max) {
            _max = p2;
        }
    }
    for (i = 0; i <= _max; i++) {
        if (list[i] == 1) {
            count++;
        }
    }
    free(list);
    return count;
}

int max_Vertice(char name[])
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