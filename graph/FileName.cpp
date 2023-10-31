#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 10

//�湮�� ���
int node=0;


// �����Լ�
void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}


/////////////////////////////////////////////////////////�׷���
//�׷��� ��� ����
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

// ���� ���� ����
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}
/////////////////////////////////////////////////////////�׷���


/////////////////////////////////////////////////////////����
//���� ��� ����
typedef struct {
	int data[MAX_STACK_SIZE];
	int top;
}StackType;

//���� �ʱ�ȭ
void init_stack(StackType* s) {
	s->top = -1;
}

//���� ���� ���� ���� �Լ�
int is_empty(StackType* s) {
	return(s->top == -1);
}

//���� ��ȭ ���� ���� �Լ�
int is_full(StackType* s) {

	return (s->top == (MAX_STACK_SIZE - 1));

}


//���� ���� �Լ�
void push(StackType* s, int item) {

	if (is_full(s)) {

		error("������ ��ȭ�����Դϴ�.");

		return;

	}

	else s->data[++(s->top)] = item;

}

//���� ���� �Լ�
int pop(StackType* s) {

	if (is_empty(s)) {

		error("������ ��������Դϴ�.");

		exit(1);

	}

	else return s->data[(s->top)--];

}
/////////////////////////////////////////////////////////����

/////////////////////////////////////////////////////////ť
typedef struct {
	int queue[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;



// ť �ʱ�ȭ
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
	return (q->front == (q->rear + 1) % MAX_QUEUE_SIZE);
}

// ���� �Լ�
void enqueue(QueueType* q, int item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

// ���� �Լ�
int dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

/////////////////////////////////////////////////////////ť

// ���� ��ķ� ǥ���� �׷����� ���� ���� �켱 Ž��
void dfs_mat(GraphType* g, int start, int target)
{
	int a;
	StackType *s= (StackType*)malloc(sizeof(StackType*)); // ���û���
	init_stack(s);
	push(s,start);
	visited[start] = 1;
	node++;
	
	while (!is_empty(s)) {//������ ������� �ʴٸ�
		int count = 0;
		a = pop(s);
		printf("%d ", a);
		s->top++;

		if (a == target) {//���ϴ� �� Ž�� ����
			printf("\nž�� ����: %d\n", a);
			for (int i = 0; i < MAX_VERTICES + 1; i++) {
				visited[i] = 0;
			}
			return;
		}

		for (int w = 0; w < g->n; w++){//���� ���� Ž��
			if (g->adj_mat[a][w] && !visited[w]){
				push(s, w);
				visited[w] = 1;
				node++;
				count++;
				break;
			}
		}
		if (count == 0) {//���� ���� �߿� �湮���� ���� ���� ���ٸ�
			a = pop(s);
			node++;
		}
	}
	printf("Ž�� ����\n");
	for (int i = 0; i < MAX_VERTICES + 1; i++) {
		visited[i] = 0;
	}
}

//���� ��ķ� ǥ���� �׷����� ���� �ʺ� �켱 Ž��
void bfs_mat(GraphType* g, int start, int target)
{
	int w;
	QueueType q;//ť ����
	init_queue(&q);
	visited[start] = TRUE;
	printf("%d ", start);
	enqueue(&q, start);
	node++;
	while (!is_empty(&q)) {//ť�� ������� �ʴٸ�
		int a = dequeue(&q);
		if (a == target) {//Ž�� �Ϸ�
			printf("\nŽ�� �Ϸ�: %d\n", a);
			return;
		}
		for (w = 0; w < g->n; w++)//���� ���� Ž��
			if (g->adj_mat[a][w] && !visited[w]) {
				visited[w] = TRUE;
				printf("%d ", w);
				enqueue(&q, w);
				node++;
			}
	}
}


//�Է½� ����� ���� �޾��ֱ�
void Clear(void) {
	while (getchar() != '\n');
}

int main(void)
{
	//�׷��� ����
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


	//�޴�
	printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
	printf("| 1    : ���� �켱 Ž��    |\n");
	printf("| 2    : �ʺ� �켱 Ž��    |\n");
	printf("| 3    : ����              |\n");
	printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
	printf("\n\n");

	int number1, number2=0;
	int command;
	do {
		printf("�޴� �Է�: ");
		command = getchar();

		switch (command) {
			//���� �켱 Ž��(1)�Է�
		case '1':
		{
			printf("���� ��ȣ�� Ž���� �� �Է�: ");
			scanf_s("%d %d", &number1, &number2);
			Clear();
			dfs_mat(g, number1, number2);
			printf("��尡 �̵��� Ƚ��: %d\n\n", node);
			node = 0;
			break;
		}
		//�ʺ� �켱 Ž��(2)�Է�
		case '2':
		{
			printf("���� ��ȣ�� Ž���� �� �Է�: ");
			scanf_s("%d %d", &number1, &number2);
			Clear();
			bfs_mat(g, number1, number2);
			
			printf("��尡 �̵��� Ƚ��: %d\n\n", node);
			node = 0;
			break;
		}
		}
		//3�� �ԷµǸ� do-while�� ����
	} while (command != '3');

	free(g);
	return 0;
}