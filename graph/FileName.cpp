#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000
#define MAX_EDGE 100

int parent[MAX_VERTICES];

void set_init(int n)
{
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

int set_find(int curr)
{
	if (parent[curr] == -1)
		return curr;
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

void set_union(int a, int b)
{
	int root1 = set_find(a);
	int root2 = set_find(b);
	if (root1 != root2)
		parent[root1] = root2;
}

struct Edge
{
	int start, end, weight;
};
//힙 정의
typedef struct {
	Edge heap[MAX_EDGE];
	int heap_size;
}HeapType;

//힙 생성
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}

//힙 초기화
void init(HeapType* h)
{
	h->heap_size = 0;
}
//삽입 함수
void insert_min_heap(HeapType* h, Edge item)
{
	int i;
	i = ++(h->heap_size);
	h->heap[h->heap_size] = item;

	while ((i != 1) && (item.weight < h->heap[i / 2].weight)) {
		h->heap[i] = h->heap[i / 2];
		h->heap[i / 2] = item;
		i /= 2;

	}
	h->heap[i] = item;
}
//삭제 함수
Edge delete_min_heap(HeapType* h)
{
	int parent, child;
	Edge item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size)
	{
		if ((child > h->heap_size) &&
			(h->heap[child].weight) > h->heap[child + 1].weight)
			child++;
		if (temp.weight < h->heap[child].weight) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

typedef struct GraphType
{
	int n;
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;
// 그래프 초기화 
void graph_init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++)
	{
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}
// qsort()에 사용되는 함수
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}
// kruskal의 최소 비용 신장 트리 프로그램(qsort사용)
void kruskal(GraphType* g)
{
	printf("qsort사용\n");
	int edge_accepted = 0;	                // 현재까지 선택된 간선의 수	
	int uset, vset;			                // 정점 u와 정점 v의 집합 번호
	struct Edge e;

	set_init(g->n);			                // 집합 초기화
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("Kruskal MST Algorithm \n");
	int i = 0;
	while (edge_accepted < (g->n - 1))	    // 간선의 수 < (n-1)
	{
		e = g->edges[i];
		uset = set_find(e.start);	        // 정점 u의 집합 번호 
		vset = set_find(e.end);		        // 정점 v의 집합 번호
		if (uset != vset)                   // 서로 속한 집합이 다르면
		{
			printf("Edge (%d, %d) Select %d \n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	        // 두개의 집합을 합친다.
		}
		i++;
	}
}

//kruskal의 최소 비용 신장 트리 프로그램(min_heap사용)
void kruskal2(GraphType* g, HeapType* h)
{
	printf("min_heap사용\n");
	int edge_accepted = 0;	                // 현재까지 선택된 간선의 수	
	int uset, vset;			                // 정점 u와 정점 v의 집합 번호
	struct Edge e;

	set_init(g->n);			                // 집합 초기화


	printf("Kruskal MST Algorithm \n");
	int i = 0;
	while (edge_accepted < (g->n - 1))	    // 간선의 수 < (n-1)
	{
		e = delete_min_heap(h);
		uset = set_find(e.start);	        // 정점 u의 집합 번호 
		vset = set_find(e.end);		        // 정점 v의 집합 번호
		if (uset != vset)                   // 서로 속한 집합이 다르면
		{
			printf("Edge (%d, %d) Select %d \n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	        // 두개의 집합을 합친다.
		}
		i++;
	}
}


int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	insert_edge(g, 1, 2, 3);
	insert_edge(g, 1, 6, 11);
	insert_edge(g, 1, 7, 12);
	insert_edge(g, 2, 3, 5);
	insert_edge(g, 2, 4, 4);
	insert_edge(g, 2, 5, 1);
	insert_edge(g, 2, 6, 7);
	insert_edge(g, 2, 7, 8);
	insert_edge(g, 3, 4, 2);
	insert_edge(g, 3, 7, 6);
	insert_edge(g, 3, 8, 5);
	insert_edge(g, 4, 5, 13);
	insert_edge(g, 4, 8, 14);
	insert_edge(g, 4, 10, 16);
	insert_edge(g, 5, 6, 9);
	insert_edge(g, 5, 9, 18);
	insert_edge(g, 5, 10, 17);
	insert_edge(g, 7, 8, 13);
	insert_edge(g, 8, 10, 15);
	insert_edge(g, 9, 10, 10);

	kruskal(g);

	HeapType* h = create();
	init(h);
	for (int i = 0; i <= g->n; i++) {
		insert_min_heap(h, g->edges[i]);
	}

	set_init;
	kruskal2(g, h);
	free(g);
	return 0;
}