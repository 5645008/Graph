#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	100	
#define INF	1000000	           // 무한대 (연결이 없는 경우) 

typedef struct GraphType
{
	int n;	                  // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];   // 시작정점으로부터의 최단경로 거리 
int found[MAX_VERTICES];      // 방문한 정점 표시 
int MST[MAX_VERTICES] = { 0 };

int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
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


// Dijkstra의 최단 경로 프로그램
void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	for (i = 0; i < g->n; i++)   /* 초기화 */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE;    /* 시작 정점 방문 표시 */
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++)
	{
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		MST[i+1] = u;
		for (w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
	}
}

int main(void)
{
	GraphType g = { 10,
		{{0,3,INF,INF,INF,11,12,INF,INF,INF},
		{3,0,5,4,1,7,8,INF,INF,INF},
		{INF,5,0,2,INF,INF,6,5,INF,INF},
		{INF,4,2,0,13,INF,INF,14,INF,16},
		{INF,1,INF,13,0,9,INF,INF,18,17},
		{11,7,INF,INF,9,0,INF,INF,INF,INF},
		{12,8,6,INF,INF,INF,0,INF,13,INF},
		{INF,INF,5,14,INF,INF,13,0,INF,15},
		{INF,INF,INF,INF,18,INF,INF,INF,0,10},
		{INF,INF,INF,16,17,INF,INF,15,10,0}}
	};
	shortest_path(&g, 0);

	//MST 출력부분
	for (int i = 0; i < g.n; i++) {
		printf("%d ", MST[i] + 1);
	}
	return 0;
}