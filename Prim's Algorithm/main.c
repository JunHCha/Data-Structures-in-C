#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTEX 1001
#define MAX_EDGE 20001

//Edge, PQ, swap, push, pop, Node, addNode, 

typedef struct {
	int weight;
	int node;
}Edge;

typedef struct {
	Edge* heap[MAX_EDGE];
	int count;
}PriorityQueue;

void swap(Edge* a, Edge* b) {
	Edge temp;
	temp.weight = a->weight;
	temp.node = a->node;
	a->weight = b->weight;
	a->node = b->node;
	b->weight = temp.weight;
	b->node = temp.node;
}

void queuePush(PriorityQueue* pq, Edge* input) {
	pq->heap[pq->count] = input;
	int now = pq->count;
	int parent = (now - 1) / 2;
	while (now > 0 && pq->heap[now]->weight < pq->heap[parent]->weight) {
		swap(pq->heap[now], pq->heap[parent]);
		now = parent;
		parent = (parent - 1) / 2;
	}
	pq->count++;
}

Edge* queuePop(PriorityQueue* pq) {
	if (pq->count == 0) return NULL;
	Edge* res = pq->heap[0];
	pq->count--;
	pq->heap[0] = pq->heap[pq->count];
	int now = 0, left = 1, right = 2;
	int target = now;
	while (left < pq->count) {
		if (pq->heap[target]->weight > pq->heap[left]->weight) target = left;
		if (pq->heap[target]->weight > pq->heap[right]->weight && right < pq->count) target = right;
		if (target == now) break;
		else {
			swap(pq->heap[now], pq->heap[target]);
			now = target;
			left = now * 2 + 1;
			right = now * 2 + 2;
		}
	}
	
	return res;
}

typedef struct Node {
	Edge* edge;
	struct Node* next;
} Node;

Node** adj;
int visit[MAX_VERTEX];

void addEdge(Node** target, int index, Edge* input) {
	if (target[index] == NULL) {
		target[index] = (Node*)malloc(sizeof(Node));
		target[index]->edge = input;
		target[index]->next = NULL;
	}
	else {
		Node* node = (Node*)malloc(sizeof(Node));
		node->edge = input;
		node->next = target[index];
		target[index] = node;
	}
}

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	adj = (Node**)malloc(sizeof(Node*) * (N + 1));
	for (int i = 0; i <= N; i++)	{
		adj[i] = NULL;
	}
	for (int i = 0; i < M; i++)	{
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		Edge* edge1 = (Edge*)malloc(sizeof(Edge));
		edge1->node = b;
		edge1->weight = c;
		addEdge(adj, a, edge1);
		Edge* edge2 = (Edge*)malloc(sizeof(Edge));
		edge2->node = a;
		edge2->weight = c;
		addEdge(adj, b, edge2);
	}

	long long res = 0;
	PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	pq->count = 0;
	Edge* start = (Edge*)malloc(sizeof(Edge));
	start->node = 1; start->weight = 0;
	queuePush(pq, start);
	while (N--) { // 모든 노드 방문하는 횟수는 어차피 N번으로 고정돼있음.
		int nextNode = -1, nextWeight = INT_MAX;
		while (1) {
			Edge* cur = queuePop(pq);
			if (cur == NULL) break;
			nextNode = cur->node;
			if (!visit[nextNode]) {
				nextWeight = cur->weight;
				break;
			}
		}
		if (nextNode == INT_MAX) {
			printf("더 이상 연결된 정점이 없습니다.\n");
			break;
		}
		visit[nextNode] = 1;
		res += nextWeight;
		Node* cur = adj[nextNode];
		while (cur != NULL) {
			queuePush(pq, cur->edge);
			cur = cur->next;
		}		
	}
	printf("%lld\n", res);
	system("pause");
	return 0;
}

/*
typedef struct {
	int cost;
	int node;
} Edge;

typedef struct {
	Edge* heap[MAX_EDGE];
	int count;
} PriorityQueue;

void swap(Edge* a, Edge* b) {
	Edge temp;
	temp.cost = a->cost;
	temp.node = a->node;
	a->cost = b->cost;
	a->node = b->node;
	b->cost = temp.cost;
	b->node = temp.node;
}

void push(PriorityQueue* pq, Edge* input) {
	if (pq->count >= MAX_EDGE) return;
	pq->heap[pq->count] = input;
	int cur = pq->count, parent = (cur - 1) / 2;
	while (cur > 0 && pq->heap[parent]->cost > pq->heap[cur]->cost) {
		swap(pq->heap[parent], pq->heap[cur]);
		cur = parent;
		parent = (cur - 1) / 2;
	}
	pq->count++;
}

Edge* pop(PriorityQueue* pq) {
	if (pq->count <= 0) return NULL;
	Edge* res = pq->heap[0];
	pq->count--;
	pq->heap[0] = pq->heap[pq->count];
	int cur = 0, target = 0, left = 1, right = 2;
	while (left < pq->count) {
		if (pq->heap[cur]->cost > pq->heap[left]->cost) target = left;
		if (pq->heap[cur]->cost > pq->heap[right]->cost && right < pq->count) target = right;
		if (cur == target) break;
		else {
			swap(pq->heap[cur], pq->heap[target]);
			cur = target;
			left = cur * 2 + 1;
			right = cur * 2 + 2;
		}
	}
	return res;
}

typedef struct Node {
	Edge* edge;
	struct Node* next;
} Node;

Node** adj;
int d[MAX_VERTEX];

void add(Node** target, int index, Edge* data) {
	if (target[index] == NULL) {
		target[index] = (Node*)malloc(sizeof(Node));
		target[index]->edge = data;
		target[index]->next = NULL;
	}
	else {
		Node* node = (Node*)malloc(sizeof(Node));
		node->edge = data;
		node->next = target[index];
		target[index] = node;
	}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	adj = (Node**)malloc(sizeof(Node*) * (n + 1));
	for (int i = 1; i <= n; i++) adj[i] = NULL;
	PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	pq->count = 0;
	for (int i = 0; i < m; i++)	{
		int start, terminal, cost;
		scanf("%d %d %d", &start, &terminal, &cost);
		Edge* temp1 = (Edge*)malloc(sizeof(Edge));
		temp1->node = terminal;
		temp1->cost = cost;
		add(adj, start, temp1);
		Edge* temp2 = (Edge*)malloc(sizeof(Edge));
		temp2->node = start;
		temp2->cost = cost;
		add(adj, terminal, temp2);
	}
	long long res = 0;
	Edge* start = (Edge*)malloc(sizeof(Edge));
	start->cost = 0; start->node = 1; push(pq, start);
	for (int i = 0; i < n; i++) {
		int nextNode = -1, nextCost = INT_MAX;
		while (1) {
			Edge* now = pop(pq);
			if (now == NULL) break;
			nextNode = now->node;
			if (!d[nextNode]) {
				nextCost = now->cost;
				break;
			}
		}
		if (nextCost == INT_MAX) printf("연결그래프가 아닙니다.\n");
		res += nextCost;
		d[nextNode] = 1;
		Node* cur = adj[nextNode];
		while (cur != NULL) {
			push(pq, cur->edge);
			cur = cur->next;
		}
	}
	printf("%lld\n", res);
	system("pause");
	return 0;
}
*/