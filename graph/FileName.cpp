#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	100	
#define INF	1000000	           /* 무한대 (연결이 없는 경우) */

typedef struct GraphType
{
	int n;	                  // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES];
int P[MAX_VERTICES][MAX_VERTICES];
int S[MAX_VERTICES];

void floyd(GraphType* g)
{

	int i, j, k;
	for (i = 0; i < g->n; i++)
		for (j = 0; j < g->n; j++) {
			A[i][j] = g->weight[i][j];
			if (g->weight[i][j] != 0 && g->weight[i][j] != INF) {
				P[i][j] = j;
			}
			else {
				P[i][j] = -1;
			}
		}

	for (k = 0; k < g->n; k++)
	{
		for (i = 0; i < g->n; i++)
			for (j = 0; j < g->n; j++)
				if (A[i][k] + A[k][j] < A[i][j]) {
					A[i][j] = A[i][k] + A[k][j];
					P[i][j] = k;
				}
	}
}

void shortway(int start, int end) {
	int s = P[end][start];
	int i = 0;
	S[i] = end;
	i++;
	while (s != -1) {
		S[i] = s;
		i++;
		s = P[s][start];
	}
	for (int j = i-1; j > 0; j--) {
		printf("%d->", S[j]+1);
	}
	printf("%d\n", S[0] + 1);

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
	floyd(&g);
	
	int start, end = 0;
	printf("Floyd - Warshall Algorithm\n");
	while (1) {
		printf("Start Node: ");
		scanf_s("%d", &start);
		printf("End Node: ");
		scanf_s("%d", &end);
		printf("Shortest Distance: %d\n", A[start-1][end-1]);
		printf("최단 경로: ");
		shortway(start-1, end-1);
		printf("\n");
	}
	return 0;
}