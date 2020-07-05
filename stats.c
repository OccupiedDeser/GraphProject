#include "stats.h"
#include "extra.h"
#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#define MAXA 2000000

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

float closenessCentrality(char name[], int node)
{
    float ret;
    long long int sum = 0, count = 0;
    AdjList* g = create_AL(name);
    int* dist = (int*)malloc(g->n * sizeof(int));
    int* path = (int*)malloc(g->n * sizeof(int));
    Dijkstra(node, node, g, dist, path);
    //把node作为v传入，使得Dijkstra不至于中途退出，能找到所有node可到达的点
    for (int i = 0; i <= g->n; i++) {
        if (dist[i] < INF) {
            sum += dist[i];
            count++;
        }
    }
    ret = (float)(count - 1) / sum;     //sum中包含了dist值为0的点，即node本身
    delete_AL(g);
    free(dist);
    free(path);
    return ret;
}