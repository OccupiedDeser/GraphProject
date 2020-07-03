#include "stats.h"
#include "extra.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXA 2000000

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

float freemanNetworkCentrality(char name[])
{
    FILE* fp = fopen(name, "r");
    int u, v, w, num = 0, node_num;
    // int graph[MAXA * 2][2];
    int* graph = (int*)malloc(2 * MAXA * sizeof(int));
    while (fscanf(fp, "%d %d %d", &u, &v, &w) != EOF) {
        graph[num * 2] = u;
        graph[num * 2 + 1] = v;
        graph[(num + 1) * 2] = v;
        graph[(num + 1) * 2 + 1] = u;
        num += 2;
        if (num >= MAXA) {
            printf("超出最大处理范围");
            return -1;
        }
    }
    fclose(fp);

    node_num = 0;
    qsort(graph, num, 2 * sizeof(int), cmp);
    for (int i = 0; i < num; i++) {
        if (i != 0 && graph[i * 2] != graph[(i - 1) * 2]) {
            node_num++;
        }
    }
    int maxCD = 0, CDi = 0;
    float sumCD = 0;
    for (int i = 0; i < num; i++) {
        if (i == 0 || graph[i * 2] != graph[(i - 1) * 2]) {
            sumCD += CDi; //i为0时，CDi == 0, sumCD的值没有改变
            if (CDi > maxCD) {
                maxCD = CDi;
            }
            CDi = 1;
        } else {
            if (graph[i * 2 + 1] != graph[(i - 1) * 2 + 1]) {
                CDi++;
            }
        }
    }
    free(graph);
    float degree_Centrality = (1.0 * node_num * maxCD - sumCD) / (1.0 * (node_num - 1) * (node_num - 2));
    return degree_Centrality;
}

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