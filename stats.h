#ifndef _STATS_H_
#define _STATS_H_

int numberOfEdges(char name[]);
int numberOfVertices(char name[]);
int max_Vertice(char name[]);       //最多可能存在的顶点数量，即最大顶点编号加一
float freemanNetworkCentrality(char name[]);
float closenessCentrality(char name[]);

#endif