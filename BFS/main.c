#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define INF 999999
#define MAX_SIZE 1001

typedef struct Node {
	int index;
	struct Node* next;
} Node;

typedef struct {
	Node* front;
	Node* rear;
	int count;
} Queue;

Node** adj;
int n, m, c[MAX_SIZE];

void addFront(Node* root, int index) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->index = index;
	node->next = root->next;
	root->next = node;
}

void queuePush(Queue* queue, int index) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->index = index;
	node->next = NULL;
	if (queue->count == 0) {
		queue->front = node;
	}
	else {
		queue->rear->next = node;
	}
	queue->rear = node;
	queue->count++;
}

int queuePop(Queue* queue) {
	if (queue->count <= 0) return -INF;
	int res = queue->front->index;
	Node* temp = (Node*)malloc(sizeof(Node));
	temp = queue->front;
	queue->front = temp->next;
	free(temp);
	queue->count--;
	return res;
}

void bfs(int start) {
	Queue q;
	q.count = 0;
	q.front = NULL;
	q.rear = NULL;
	queuePush(&q, start);
	c[start] = 1;
	while (q.count != 0) {
		int x = queuePop(&q);
		printf("%d ", x);
		Node* cur = adj[x]->next;
		while (cur) {
			int next = cur->index;
			if (!c[next]) {
				queuePush(&q, next);
				c[next] = 1;
			}
			cur = cur->next;
		}
	}
}

int main() {
	scanf("%d %d", &n, &m); 
	adj = (Node**)malloc(sizeof(Node*) * (n + 1));
	for (int i = 1; i <= n; i++)	{
		adj[i] = (Node*)malloc(sizeof(Node));
		adj[i]->next = NULL;
	}
	for (int i = 0; i < m; i++)	{
		int a, b;
		scanf("%d %d", &a, &b);
		addFront(adj[a], b);
		addFront(adj[b], a);
	}
	bfs(1);
	system("pause");
	return 0;
}