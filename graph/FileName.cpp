#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 10

//방문한 노드
int node=0;


// 오류함수
void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}


/////////////////////////////////////////////////////////그래프
//그래프 요소 정의
typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];



void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++) {
		for (int c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
	}
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}
/////////////////////////////////////////////////////////그래프


/////////////////////////////////////////////////////////스택
//스택 요소 정의
typedef struct {
	int data[MAX_STACK_SIZE];
	int top;
}StackType;

//스택 초기화
void init_stack(StackType* s) {
	s->top = -1;
}

//스택 공백 상태 검출 함수
int is_empty(StackType* s) {
	return(s->top == -1);
}

//스택 포화 상태 검출 함수
int is_full(StackType* s) {

	return (s->top == (MAX_STACK_SIZE - 1));

}


//스택 삽입 함수
void push(StackType* s, int item) {

	if (is_full(s)) {

		error("스택이 포화상태입니다.");

		return;

	}

	else s->data[++(s->top)] = item;

}

//스택 삭제 함수
int pop(StackType* s) {

	if (is_empty(s)) {

		error("스택이 공백상태입니다.");

		exit(1);

	}

	else return s->data[(s->top)--];

}
/////////////////////////////////////////////////////////스택

/////////////////////////////////////////////////////////큐
typedef struct {
	int queue[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;



// 큐 초기화
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q)
{
	return (q->front == (q->rear + 1) % MAX_QUEUE_SIZE);
}

// 삽입 함수
void enqueue(QueueType* q, int item)
{
	if (is_full(q))
		error("큐가 포화상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

// 삭제 함수
int dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

/////////////////////////////////////////////////////////큐

// 인접 행렬로 표현된 그래프에 대한 깊이 우선 탐색
void dfs_mat(GraphType* g, int start, int target)
{
	int a;
	StackType *s= (StackType*)malloc(sizeof(StackType*)); // 스택생성
	init_stack(s);
	push(s,start);
	visited[start] = 1;
	node++;
	
	while (!is_empty(s)) {//스택이 비어있지 않다면
		int count = 0;
		a = pop(s);
		printf("%d ", a);
		s->top++;

		if (a == target) {//원하는 값 탐색 성공
			printf("\n탑색 성공: %d\n", a);
			for (int i = 0; i < MAX_VERTICES + 1; i++) {
				visited[i] = 0;
			}
			return;
		}

		for (int w = 0; w < g->n; w++){//인접 정점 탐색
			if (g->adj_mat[a][w] && !visited[w]){
				push(s, w);
				visited[w] = 1;
				node++;
				count++;
				break;
			}
		}
		if (count == 0) {//인접 정점 중에 방문하지 않은 곳이 없다면
			a = pop(s);
			node++;
		}
	}
	printf("탐색 실패\n");
	for (int i = 0; i < MAX_VERTICES + 1; i++) {
		visited[i] = 0;
	}
}

//인접 행렬로 표현된 그래프에 대한 너비 우선 탐색
void bfs_mat(GraphType* g, int start, int target)
{
	int w;
	QueueType q;//큐 생성
	init_queue(&q);
	visited[start] = TRUE;
	printf("%d ", start);
	enqueue(&q, start);
	node++;
	while (!is_empty(&q)) {//큐가 비어있지 않다면
		int a = dequeue(&q);
		if (a == target) {//탐색 완료
			printf("\n탐색 완료: %d\n", a);
			return;
		}
		for (w = 0; w < g->n; w++)//인접 정점 탐색
			if (g->adj_mat[a][w] && !visited[w]) {
				visited[w] = TRUE;
				printf("%d ", w);
				enqueue(&q, w);
				node++;
			}
	}
}


//입력시 생기는 엔터 받아주기
void Clear(void) {
	while (getchar() != '\n');
}

int main(void)
{
	//그래프 생성
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 11; i++)
		insert_vertex(g, i);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 4);
	insert_edge(g, 0, 5);
	insert_edge(g, 0, 6);
	insert_edge(g, 0, 9);
	insert_edge(g, 1, 4);
	insert_edge(g, 1, 5);
	insert_edge(g, 1, 7);
	insert_edge(g, 1, 10);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 3, 4);
	insert_edge(g, 3, 5);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 6);
	insert_edge(g, 4, 7);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 8);
	insert_edge(g, 7, 10);
	insert_edge(g, 8, 9);
	insert_edge(g, 8, 10);


	//메뉴
	printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
	printf("| 1    : 깊이 우선 탐색    |\n");
	printf("| 2    : 너비 우선 탐색    |\n");
	printf("| 3    : 종료              |\n");
	printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
	printf("\n\n");

	int number1, number2=0;
	int command;
	do {
		printf("메뉴 입력: ");
		command = getchar();

		switch (command) {
			//깊이 우선 탐색(1)입력
		case '1':
		{
			printf("시작 번호와 탐색할 값 입력: ");
			scanf_s("%d %d", &number1, &number2);
			Clear();
			dfs_mat(g, number1, number2);
			printf("노드가 이동된 횟수: %d\n\n", node);
			node = 0;
			break;
		}
		//너비 우선 탐색(2)입력
		case '2':
		{
			printf("시작 번호와 탐색할 값 입력: ");
			scanf_s("%d %d", &number1, &number2);
			Clear();
			bfs_mat(g, number1, number2);
			
			printf("노드가 이동된 횟수: %d\n\n", node);
			node = 0;
			break;
		}
		}
		//3가 입력되면 do-while문 종료
	} while (command != '3');

	free(g);
	return 0;
}