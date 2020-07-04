#include "search.h"
#include "extra.h"
#include "stats.h"
#include <stdio.h>
#include <stdlib.h>

int visit[MAXV] = { 0 };
//返回的字符数组是malloc的，需要free
char* DFS(int u, int v, AdjList* graph)
{
    S_Stack* S;
    initStack(&S);
    for (int i = 0; i < MAXV; i++) {
        visit[i] = 0;
    }

    double path_Weight; //当前路径权值总和
    double min_Weight = DBL_MAX;

    //初始化，压入起点入栈
    int pos;
    pos = u;
    visit[pos] = 1;
    push(pos, S);
    Arc* Arc_pointer;
    int next = -1;
    int v_path[MAXV], num = 0;
    int p = u, count = 0, p_end = 0;
    char* str_path = (char*)malloc(sizeof(char) * 10 * MAXV);

    while (!isStackEmpty(S)) {
        //回溯
        pos = S->data[S->top];
        Arc_pointer = graph->adjlist[pos].firstarc;
        if (next != -1) { //next为-1时，为起点，不是回溯
            while (Arc_pointer->adjvex != next) {
                Arc_pointer = Arc_pointer->nextarc;
            }
            Arc_pointer = Arc_pointer->nextarc;
        }
        while (Arc_pointer != NULL) {
            if (Arc_pointer->adjvex == v) {
                path_Weight = 0;
                //计算路径权值
                num = S->top + 2;
                for (int i = 0; i < num - 1; i++) {
                    v_path[i] = S->data[i];
                }
                v_path[num - 1] = v;
                goto break_DFS_loop;
            }
            if (!visit[Arc_pointer->adjvex]) {
                pos = Arc_pointer->adjvex;
                push(pos, S);
                Arc_pointer = graph->adjlist[pos].firstarc;
                visit[pos] = 1;
            } else {
                Arc_pointer = Arc_pointer->nextarc;
            }
        }
        //恢复pop出的节点为可访问
        pos = pop(S);
        next = pos;
        visit[pos] = 0;
    }

break_DFS_loop:
    deleteStack(S);

    if (num == 0) {
        extra_strcpy(str_path, "Failed to find a path.");
    } else {
        p_end = extra_itoa(v_path[0], str_path);
        for (int i = 1; i < num; i++) {
            p_end += extra_strcpy(str_path + p_end, " -> ");
            p_end += extra_itoa(v_path[i], str_path + p_end);
        }
    }
    return str_path;
}

//返回的字符数组是malloc的，需要free
char* BFS(int u, int v, AdjList* graph)
{
    AdjList_Split_Point(graph);
    S_Queue* Q;
    initQueue(&Q);
    for (int i = 0; i < MAXV; i++) {
        visit[i] = 0;
    }
    visit[u] = 1;

    //初始化将起点压入队列
    int pos = u;
    // pos = graph->adjlist[u].firstarc->adjvex;
    enQueue(pos, Q);

    int p, count, p_end;
    char* str_path = (char*)malloc(sizeof(char) * MAXV);
    int v_path[MAXV];

    int pre[MAXV];
    Arc* Arc_pointer;
    while (!isQueueEmpty(Q)) {
        p = pos = deQueue(Q);
        visit[pos] = 1;
        Arc_pointer = graph->adjlist[pos].firstarc;
        while (Arc_pointer != NULL) {
            if (!visit[Arc_pointer->adjvex]) {
                pre[Arc_pointer->adjvex] = p;
                if (Arc_pointer->adjvex == v) {
                    goto exit_loop;
                }
                pos = Arc_pointer->adjvex;
                enQueue(pos, Q);
            }
            Arc_pointer = Arc_pointer->nextarc;
        }
    }
exit_loop:
    p = v;
    count = 0;
    p_end = 0;
    if (Arc_pointer == NULL) {
        extra_strcpy(str_path, "Failed to find a path.");
    } else {
        while (p != u) {
            if (p > graph->n) {
                p = pre[p];
                continue;
            }
            v_path[count] = p;
            p = pre[p];
            count++;
        }
        v_path[count] = u;
        p_end = extra_itoa(v_path[count], str_path);
        for (int i = count - 1; i >= 0; i--) {
            p_end += extra_strcpy(str_path + p_end, " -> ");
            if (str_path + p_end == NULL) {
                str_path += p_end;
            }
            p_end += extra_itoa(v_path[i], str_path + p_end);
        }
    }
    deleteQueue(Q);
    AdjList_Merge_Point(graph);
    return str_path;
}

AdjList* create_AL(char name[])
{
    int i, j, edges = 0;
    int p1, p2, wei;
    int repeated_arc;
    Arc* new = NULL, *p;
    AdjList* g = NULL;
    g = (AdjList*)malloc(sizeof(AdjList));
    g->n = max_Vertice(name);

    for (i = 0; i <= g->n; i++) {
        g->adjlist[i].firstarc = NULL;
    }

    FILE* fp = fopen(name, "r");
    while (fscanf(fp, "%d %d %d", &p1, &p2, &wei) != EOF) {
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
    fclose(fp);
    g->e = edges;
    return g;
}

void delete_AL(AdjList* g)
{
    Arc *pre, *p;
    int i;
    for (i = 0; i <= g->n; i++) {
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
    if (extra_strcmp(algorithm, "DFS") == 0) {
        AdjList* g = create_AL(name);
        char* path = DFS(u, v, g);
        delete_AL(g);
        return path;
    } else if (extra_strcmp(algorithm, "BFS") == 0) {
        AdjList* g = create_AL(name);
        char* path = BFS(u, v, g);
        delete_AL(g);
        return path;
    } else if (extra_strcmp(algorithm, "Dijkstra") == 0) {
        AdjList* g = create_AL(name);
        if (u > g->n || v > g->n) {
            delete_AL(g);
            return NULL;
        }
        int* dist = (int*)malloc(g->n * sizeof(int));
        int* path = (int*)malloc(g->n * sizeof(int));
        Dijkstra(u, v, g, dist, path);
        int g_n = g->n;
        delete_AL(g);
        int min_dis = dist[v];
        free(dist);
        int* _stack = (int*)malloc(g_n * sizeof(int));
        int stack_top = -1;
        for (int i = v; i != u; i = path[i]) {
            if (path[i] == -1) {
                free(path);
                free(_stack);
                return NULL;
            }
            stack_top++;
            _stack[stack_top] = i;
        }
        char* ret = (char*)malloc((11 * (stack_top + 3)) * sizeof(char));
        int i = extra_itoa(u, ret);
        while (stack_top > -1) {
            i += extra_strcpy(ret + i, " -> ");
            i += extra_itoa(_stack[stack_top], ret + i);
            stack_top--;
        }
        i += extra_strcpy(ret + i, "\ncost: ");
        i += extra_itoa(min_dis, ret + i);
        ret[i++] = '\n';
        ret[i++] = '\0';
        free(path);
        free(_stack);
        return ret;
    } else {
        return "ERROR: Invalid Algorithm\n";
    }
}

void Dijkstra(int u, int v, AdjList* g, int* dist, int* path)
{
    int min_dis, i, j, to_add, new_dis;
    int stop_flag = 0; //没有必要做完完整的Dijkstra，找到v点就可以退出
    int* s = (int*)malloc(g->n * sizeof(int));
    Arc* p = NULL;
    for (i = 0; i <= g->n; i++) {
        dist[i] = get_weight(g, u, i); //距离初始化
        s[i] = 0; //状态均置为"未加入s"
        if (dist[i] < INF) {
            path[i] = u;
        } else {
            path[i] = -1;
        }
    }
    dist[u] = 0;

    s[u] = 1; //源点u加入s中
    for (i = 0; i <= g->n; i++) {
        min_dis = INF;
        for (j = 0; j <= g->n; j++) {
            if (s[j] == 0 && dist[j] < min_dis) {
                to_add = j;
                min_dis = dist[j];
            }
        }
        if (min_dis == INF) { //剩下的点均不可以到达
            break;
        }
        s[to_add] = 1; //顶点to_add加入S中
        //printf("add point %d, i = %d\n", to_add, i);
        if (to_add == v) { //已经找到了到v的最短路径，可以退出Dijkstra
            break;
        }
        p = g->adjlist[to_add].firstarc; //调整剩余顶点信息。只需要考察新加入点的相邻点
        while (p != NULL) {
            if (s[p->adjvex] == 0) {
                new_dis = p->wei;
                if (dist[to_add] + new_dis < dist[p->adjvex]) {
                    dist[p->adjvex] = dist[to_add] + new_dis;
                    path[p->adjvex] = to_add;
                }
            }
            p = p->nextarc;
        }
    }
    //printf("%d is the %dst point added\n", v, i);
    // for (i = 0; i <= g->n; i++) {
    //     printf("u->%d: %d\n", i, dist[i]);
    // }
    free(s);
    return;
}

int get_weight(AdjList* g, int u, int v)
{
    Arc* p;
    p = g->adjlist[u].firstarc;
    for (; p != NULL; p = p->nextarc) {
        if (p->adjvex == v) {
            return p->wei;
        }
    }
    return INF;
}

void AdjList_Split_Point(AdjList* graph)
{
    int i, count = graph->n;
    Arc *Arc_pointer, *newArc;
    for (i = 0; i <= count; i++) {
        if (i == 21 || i == 67) {
            i++;
            i--;
        }
        Arc_pointer = graph->adjlist[i].firstarc;
        //在邻接表的第count+1的位置上建立新的节点，建立原Arc_pointer的路径，权值为w-1，Arc_pointer与其建立权值为1的路径，
        while (Arc_pointer != NULL) {
            if (Arc_pointer->wei > 1) {
                newArc = (Arc*)malloc(sizeof(Arc));
                newArc->nextarc = NULL;
                newArc->wei = Arc_pointer->wei - 1;
                newArc->adjvex = Arc_pointer->adjvex;
                graph->adjlist[count + 1].firstarc = newArc;
                count++;
                Arc_pointer->adjvex = count;
                Arc_pointer->wei = 1;
            }
            Arc_pointer = Arc_pointer->nextarc;
        }
    }
    count++;
}

void AdjList_Merge_Point(AdjList* graph)
{
    Arc* Arc_pointer;
    int tem;
    for (int i = 0; i <= graph->n; i++) {
        Arc_pointer = graph->adjlist[i].firstarc;
        while (Arc_pointer != NULL && Arc_pointer->adjvex > graph->n) {
            tem = Arc_pointer->adjvex;
            Arc_pointer->adjvex = graph->adjlist[tem].firstarc->adjvex;
            Arc_pointer->wei++;
            free(graph->adjlist[tem].firstarc);
        }
    }
}