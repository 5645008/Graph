#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

typedef struct ListNode {
    int vertex;
    int weight;
    struct ListNode* link;
} ListNode;

typedef struct GraphType {
    int n;
    ListNode* adj_list[MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int MST[MAX_VERTICES] = { 0 };

int get_min_vertex(int n) {
    int v, i;
    for (i = 0; i < n; i++) {
        if (!found[i]) {
            v = i;
            break;
        }
    }
    for (i = 0; i < n; i++) {
        if (!found[i] && (distance[i] < distance[v])) {
            v = i;
        }
    }
    return v;
}

void add_edge(GraphType* g, int start, int end, int weight) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->vertex = end;
    node->weight = weight;
    node->link = g->adj_list[start];
    g->adj_list[start] = node;
}

//출력 부분
void print_status(GraphType* g) {
    printf("Dijkstra Algorithm\n");
    printf("Distance:");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF) {
            printf("* ");
        }
        else {
            printf("%d ", distance[i]);
        }
    }
    printf("\n");
    printf("Found:   ");
    for (int i = 0; i < g->n; i++) {
        printf("%d ", found[i]);
    }
    printf("\n\n");
}


void dijkstra(GraphType* g, int s) {
    int i, u, v;
    ListNode* p;
    for (u = 0; u < g->n; u++) {
        distance[u] = INF;
    }
    distance[s] = 0;
    for (i = 0; i < g->n; i++) {
        print_status(g);
        u = get_min_vertex(g->n);
        found[u] = 1;
        MST[i + 1] = u;
        if (distance[u] == INF) {
            return;
        }
        p = g->adj_list[u];
        while (p != NULL) {
            v = p->vertex;
            if (!found[v] && p->weight < distance[v]) {
                distance[v] = p->weight;
            }
            p = p->link;
        }
    }
}

int main(void) {
    GraphType g = { 10, {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL} };
    add_edge(&g, 0, 1, 3);
    add_edge(&g, 0, 5, 11);
    add_edge(&g, 0, 6, 12);
    add_edge(&g, 1, 2, 5);
    add_edge(&g, 1, 3, 4);
    add_edge(&g, 1, 4, 1);
    add_edge(&g, 1, 5, 7);
    add_edge(&g, 1, 6, 8);
    add_edge(&g, 2, 3, 2);
    add_edge(&g, 2, 6, 6);
    add_edge(&g, 2, 7, 5);
    add_edge(&g, 3, 4, 13);
    add_edge(&g, 3, 7, 14);
    add_edge(&g, 3, 9, 16);
    add_edge(&g, 4, 5, 9);
    add_edge(&g, 4, 8, 18);
    add_edge(&g, 4, 9, 17);
    add_edge(&g, 6, 7, 13);
    add_edge(&g, 7, 9, 15);
    add_edge(&g, 8, 9, 10);
    dijkstra(&g, 0);

    //MST 출력부분
    for (int i = 0; i < g.n; i++) {
        printf("%d ", MST[i] + 1);
    }

    return 0;
}
