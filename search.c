#include "search.h"
#include "extra.h"
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
            if(p > graph->n){
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
            if(str_path + p_end == NULL){
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
    g->n = numberOfVertices(name);
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
    }
}

void AdjList_Split_Point(AdjList* graph)
{
    int i, count = graph->n;
    Arc *Arc_pointer, *newArc;
    for (i = 0; i <= count; i++) {
        if(i == 21 || i == 67){
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
