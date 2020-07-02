#include "search.h"
#include "extra.h"
#include <stdlib.h>

//返回的字符数组是malloc的，需要free
char* DFS(int u, int v, AdjList* graph)
{
    S_Stack* S;
    initStack(&S);
    int visit[MAXV] = { 0 };
    visit[v] = 1;

    double path_Weight; //当前路径权值总和
    double min_Weight = DBL_MAX;

    //初始化，压入起点入栈
    Pnode pos;
    pos.v = v;
    visit[pos.v] = 1;
    push(pos, S);
    Arc* Arc_pointer;
    int next = -1;
    int v_path[MAXV], num;
    while (!isStackEmpty(S)) {
        //回溯
        pos = S->data[S->top];
        Arc_pointer = graph->adjlist[pos.v].firstarc;
        if (next != -1) {//next为-1时，为起点，不是回溯
            while (Arc_pointer->adjvex != next) {
                Arc_pointer = Arc_pointer->nextarc;
            }
            Arc_pointer = Arc_pointer->nextarc;
        }
        while (Arc_pointer != NULL) {
            if (Arc_pointer->adjvex == u) {
                path_Weight = 0;
                //计算路径权值
                for (int i = 0; i < S->top; i++) {
                    Arc_pointer = graph->adjlist[S->data[i].v].firstarc;
                    while (Arc_pointer->adjvex != S->data[i + 1].v) {
                        Arc_pointer = Arc_pointer->nextarc;
                    }
                    path_Weight += Arc_pointer->wei;
                }
                if(min_Weight > path_Weight ){
                    num = S->top+1;
                    for(int i = 0; i < num; i++){
                        v_path[i] = S->data[i].v;
                    }
                }
                break;
            }
            if (!visit[Arc_pointer->adjvex]) {
                pos.v = Arc_pointer->adjvex;
                push(pos, S);
                Arc_pointer = graph->adjlist[pos.v].firstarc;
                visit[pos.v] = 1;
            }
        }
        //恢复pop出的节点为可访问
        pos = pop(S);
        next = pos.v;
        visit[pos.v] = 0;
    }

    int p = u, count = 0, p_end = 0;
    char str_path= (char*)malloc(sizeof(char)*10 * MAXV);

    if (min_Weight == DBL_MAX) {
        strcpy(str_path, "Failed to find a path.");
    } else {
        p_end = itoa(v_path[0], str_path);
        for (int i = 1; i < num; i++) {
            p_end += strcpy(str_path + p_end, "->");
            p_end += itoa(v_path[i], str_path + p_end);
        }
    }
    
}

//返回的字符数组是malloc的，需要free
char* BFS(int u, int v, AdjList* graph)
{
    S_Queue* Q;
    initQueue(&Q);
    int visit[MAXV] = { 0 };
    visit[v] = 1;

    //初始化将起点压入队列
    Pnode pos;
    pos.v = graph->adjlist[u].firstarc->adjvex;
    enQueue(pos, Q);

    int pre[MAXV];
    Arc* Arc_pointer;
    while (!isQueueEmpty(Q)) {
        pos = deQueue(Q);
        Arc_pointer = graph->adjlist[pos.v].firstarc;
        while (Arc_pointer != NULL) {
            if (!visit[Arc_pointer->adjvex]) {
                pre[Arc_pointer->adjvex] = pos.v;
                if (Arc_pointer->adjvex == u) {
                    goto exit_loop;
                }
                visit[Arc_pointer->adjvex] = 1;
                pos.v = Arc_pointer->adjvex;
                enQueue(pos, Q);
            }
            Arc_pointer = Arc_pointer->nextarc;
        }
    }
exit_loop:
    int p = u, count = 0, p_end = 0;
    char str_path= (char*)malloc(sizeof(char)*10 * MAXV);
    char v_path[MAXV];

    if (Arc_pointer == NULL) {
        strcpy(str_path, "Failed to find a path.");
    } else {
        while (p != v) {
            v_path[count] = p;
            p = pre[p];
            count++;
        }
        p_end = itoa(v_path[count - 1], str_path);
        for (int i = count - 2; i >= 0; i--) {
            p_end += strcpy(str_path + p_end, "->");
            p_end += itoa(v_path[i], str_path + p_end);
        }
    }
    deleteQueue(Q);
    return str_path;
}
