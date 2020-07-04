#ifndef _SEARCH_H_
#define _SEARCH_H_

#define MAXV 100000000      //最大顶点数
#define INF 1073741824      //2的30次方
#define DBL_MAX 1.7976931348623157e+308

typedef struct Anode{      //边
    int adjvex;             //该边终点编号
    struct ANode* nextarc;  //下一条边
    int wei;                //该边的权值
}Arc;

typedef struct Vnode {      //顶点
    Arc* firstarc;          //第一条边
} Vertex;

typedef struct AL{          //邻接表
    Vertex adjlist[MAXV];   //邻接表
    int n;                  //顶点数
    int e;                  //边数
} AdjList;

char* shortestPath(int u, int v, char algorithm[], char name[]);    //找出从点u到点v的最短路径
char* call_Dijk(int u, int v, AdjList* g);
void Dijkstra(int u, int v, AdjList* g, int* dist, int* path); //找出从点u到各个顶点的最短路径
AdjList* create_AL(char name[]);            //建立邻接表
void delete_AL(AdjList* g);                 //删除邻接表
int get_weight(AdjList* g, int u, int v);   //求出两个顶点间边的权值
char* DFS(int u, int v, AdjList* graph);
char* BFS(int u, int v, AdjList* graph);
void AdjList_Split_Point(AdjList* graph); //拆点，将所有节点拆为权值为1的点
void AdjList_Merge_Point(AdjList* graph);

#endif
