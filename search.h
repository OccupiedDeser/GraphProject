#ifndef _SEARCH_H_
#define _SEARCH_H_

#define MAXV 1000000
#define DBL_MAX 1.7976931348623157e+308

typedef struct Anode {      //边
    int adjvex;             //该边终点编号
    struct ANode* nextarc;  //下一条边
    int wei;                //该边的权值
} Arc;

typedef struct Vnode {      //顶点
    Arc* firstarc;          //第一条边
} Vertex;

typedef struct {            //邻接表
    Vertex adjlist[MAXV];   //邻接表
    int n;                  //顶点数
    int e;                  //边数
} AdjList;

char* shortestPath(int u, int v, char algorithm[], char name[]);
char* Dijkstra(int u, int v, char algorithm[], char name[]);
AdjList* create_AL(char name[]);
void delete_AL(AdjList* g);

char* DFS(int u, int v, AdjList* graph);
char* BFS(int u, int v, AdjList* graph);

#endif