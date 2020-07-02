#include "stats.h"
#include <stdio.h>

int numberOfEdges(char name[])
{
    FILE* fp = fopen(name, "r");
    int u, v, w;
    int edge_count = 0;
    while (fscanf(fp, "%d %d %d", &u, &v, &w) != EOF) {
        edge_count++;
    }
    fclose(fp);
    return edge_count;
}

float freemanNetworkCentrality(char name[], int node)
{
    FILE* fp = fopen(name, "r");
    int u, v, w;
    float degree_Centrality = 0;
    while (fscanf(fp, "%d %d %d", &u, &v, &w) != EOF) {
        if (u == node || v == node) {
            degree_Centrality += 1;
        }
    }
    fclose(fp);
    return degree_Centrality;
}
