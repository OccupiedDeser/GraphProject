#include "search.h"
#include "extra.h"
#include <stdio.h>
#include <stdlib.h>

AdjList* create_AL(char name[])
{
    int i, j, edges = 0;
    int p1, p2, wei;
    int repeated_arc;
    Arc* new = NULL, *p;
    AdjList* g = NULL;
    g = (AdjList*)malloc(sizeof(AdjList));
    g->n = numberOfVertices(name);
    for (i = 0; i <= g->n; i++) {
        g->adjlist[i].firstarc = NULL;
    }

    FILE* fp = fopen(name, "r");
    while (fscanf("%d%d%d", &p1, &p2, &wei) != EOF) {
        new = (Arc*)malloc(sizeof(Arc));
        new->adjvex = p2;
        new->wei = wei;
        new->nextarc = NULL;
        if (g->adjlist[p1].firstarc == NULL) {
            g->adjlist[p1].firstarc = new;
        } else {
            p = g->adjlist[p1].firstarc;
            for (; p->nextarc != NULL; p = p->nextarc) {
                if (p->adjvex == p2) {
                    repeated_arc = 1;
                    free(new);
                    break;
                }
            }
            if (p->adjvex == p2) {
                repeated_arc = 1;
                free(new);
            }
            if (repeated_arc == 1) {
                continue;
            }
            p->nextarc = new;
        }
        edges++;
    }
    g->e = edges;
    return g;
}

void delete_AL(AdjList* g)
{
    Arc *pre, *p;
    int i;
    for (i = 0; i < g->n; i++) {
        pre = g->adjlist[i].firstarc;
        while (pre != NULL) {
            p = pre->nextarc;
            free(pre);
            pre = p;
        }
    }
    free(g);
    return;
}

char* shortestPath(int u, int v, char algorithm[], char name[])
{
    if (strcmp(algorithm, "DFS") == 0) {
        AdjList* g = create_AL(name);
        DFS();
        delete_AL(g);
    } else if (strcmp(algorithm, "BFS") == 0) {
        AdjList* g = create_AL(name);
        BFS();
        delete_AL(g);
    } else if (strcmp(algorithm, "Dijkstra") == 0) {
        AdjList* g = create_AL(name);
        int* dist = (int*)malloc((g->n + 1) * sizeof(int));
        int* path = (int*)malloc((g->n + 1) * sizeof(int));
        Dijkstra(u, g, dist, path);
        delete_AL(g);
        int min_dis = dist[v];
        free(dist);
        int* _stack = (int*)malloc((g->n + 1) * sizeof(int));
        int stack_top = -1;
        for (int i = v; i != u; i = path[i]) {
            if (path[i] == -1) {
                free(path);
                free(_stack);
                return "GG: unable to reach Suantou's castle! Cyber Security Continent is deystroyed\n";
            }
            stack_top++;
            _stack[stack_top] = i;
        }
        char* ret = (char*)malloc((11 * (stack_top + 3)) * sizeof(char));
        int i = itoa(u, ret);
        while (stack_top > -1) {
            i += strcpy(ret + i, " -> ");
            i += itoa(_stack[stack_top], ret + i);
            stack_top--;
        }
        i += strcpy(ret + i, "\ncost: ");
        i += itoa(min_dis, ret + i);
        ret[i] = '\0';
        free(path);
        free(_stack);
        return ret;
    } else {
        return "ERROR: Invalid Algorithm\n";
    }
}

void* Dijkstra(int u, AdjList* g, int* dist, int* path)
{
    int min_dis, i, j, to_add, new_dis;
    int dist[g->n + 1], path[g->n + 1];
    int* s = (int*)malloc((g->n + 1) * sizeof(int));
    for (i = 0; i <= g->n; i++) {
        dist[i] = get_weight(g, u, i); //距离初始化
        s[i] = 0; //状态均置为"未加入s"
        if (dist[i] < INF) {
            path[i] = u;
        } else {
            path[i] = -1;
        }
    }

    s[u] = 1; //源点u加入s中
    for (i = 0; i <= g->n; i++) {
        min_dis = INF;
        for (j = 0; j <= g->n; j++) {
            if (s[j] == 0 && dist[j] < min_dis) {
                to_add = j;
                min_dis = dist[j];
            }
        }
        s[u] = 1; //顶点to_add加入S中
        for (j = 0; j <= g->n; j++) { //调整剩余顶点信息
            if (s[j] == 0) {
                new_dis = get_weight(g, u, j);
                if (new_dis < INF && dist[u] + new_dis < dist[j]) {
                    dist[j] = dist[u] + new_dis;
                    path[j] = u;
                }
            }
        }
    }
    return;
}

int get_weight(AdjList* g, int u, int v)
{
    Arc* p;
    p = g->adjlist[u].firstarc;
    for (; p != NULL; p = p->nextarc) {
        if (p->adjvex == v) {
            return p->adjvex;
        }
    }
    return INF;
}