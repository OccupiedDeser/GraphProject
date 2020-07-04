#include "extra.h"
#include "search.h"
#include "stats.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int a = 0;
    FILE* fp = NULL;

    if (extra_strcmp(argv[1], "-h") == 0 || extra_strcmp(argv[1], "--help") == 0) {
        printf("-h/--help:\n\tdisplay command list\n");
        printf("-g/--graph _FILE:\n");
        printf("\t-s/--stats edges: display number of edges\n");
        printf("\t-s/--stats vertices: display number of vertices\n");
        printf("\t-s/--stats freeman: display freeman\n");
        printf("\t-s/--stats closeness node_x: display closeness of node_x\n");
        printf("\t-sp/--shortestpath _ALG -u _START -v _TARGET:\n");
        printf("\t\tdisplay shortest path from _START to _TARGET with algorithm _ALG\n");
        printf("-j:\n\tdisplay image of garlic monster\n\n");
    } else if (extra_strcmp(argv[1], "-g") == 0 || extra_strcmp(argv[1], "--graph") == 0) {
        fp = fopen(argv[2], "r");
        if (fp == NULL) {
            fclose(fp);
            printf("Unable to open the file!\n\n");
        } else {
            fclose(fp);
            if (extra_strcmp(argv[3], "-s") == 0 || extra_strcmp(argv[3], "--stats") == 0) {
                if (extra_strcmp(argv[4], "edges") == 0) {
                    printf("number of edges is: %d\n\n", numberOfEdges(argv[2]));
                } else if (extra_strcmp(argv[4], "vertices") == 0) {
                    printf("number of vertices is: %d\n\n", numberOfVertices(argv[2]));
                } else if (extra_strcmp(argv[4], "freeman") == 0) {
                    printf("Freeman Network Centrality: %f\n\n", freemanNetworkCentrality(argv[2]));
                }
                // else if (extra_strcmp(argv[4], "closeness") == 0) {
                //     printf("%d", closenessCentrality(argv[2]));
                // }
                else {
                    printf("Invalid command!\nTry \"-h\" or \"--help\"\n\n");
                }
            } else if (extra_strcmp(argv[3], "-sp") == 0 || extra_strcmp(argv[3], "--shortestpath") == 0) {
                int u = extra_atoi(argv[6]);
                int v = extra_atoi(argv[8]);
                if (u == -1 || v == -1) {
                    printf("Illegal input number!\n\n");
                } else {
                    printf("please wait for a while......\n\n");
                    char* ret = shortestPath(u, v, argv[4], argv[2]);
                    if (ret == NULL) {
                        printf("GG: unable to reach Suantou's castle! Cyber Security Continent is deystroyed\n");
                    } else {
                        printf("%s\n", ret);
                    }
                    free(ret);
                }
            } else {
                printf("Invalid command!\nTry \"-h\" or \"--help\"\n\n");
            }
        }
    } else if (extra_strcmp(argv[1], "-j") == 0) {
        draw_garlic();
    } else {
        printf("Invalid command!\nTry \"-h\" or \"--help\"\n\n");
    }
    return 0;
}