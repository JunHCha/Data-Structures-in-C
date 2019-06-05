#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NODE_MAX 20001
#define EDGE_MAX 600001
// Edge, swap, priorityQueue, push, pop, Node, addNode, res

typedef struct {
	int node;
	int weight;
} Edge;

void swap(Edge* a, Edge* b) {
	Edge temp;
	temp.node = a->node;
	temp.weight = a->weight;
	a->node = b->node;
	a->weight = b->weight;
	b->node = temp.node;
	b->weight = temp.weight;
}

typedef struct {
	Edge* heap[EDGE_MAX];
	int count;
} PriorityQueue;

void queuePush(PriorityQueue* pq, Edge* input) {
	if (pq->count >= EDGE_MAX) return;
	pq->heap[pq->count] = input;
	int now = pq->count, parent = (now - 1) / 2;
	while (now > 0 && pq->heap[now]->weight < pq->heap[parent]->weight)	{
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
	int cur = 0, left = 1, right = 2;
	int target = cur;
	while (left < pq->count) {
		if (pq->heap[left]->weight < pq->heap[target]->weight) target = left;
		if (pq->heap[right]->weight < pq->heap[target]->weight) target = right;
		if (target == cur) break;
		else {
			swap(pq->heap[target], pq->heap[cur]);
			cur = target;
			left = cur * 2 + 1;
			right = cur * 2 + 2;
		}
	}
	return res;
}

typedef struct Node {
	Edge* data;
	struct Node* next;
} Node;

Node** graph;
PriorityQueue* pq;
int res[NODE_MAX];

void addEdge(Node** target, int index, Edge* input) {
	if (target[index] == NULL) {
		target[index] = (Node*)malloc(sizeof(Node));
		target[index]->data = input;
		target[index]->next = NULL;
	}
	else {
		Node* node = (Node*)malloc(sizeof(Node));
		node->data = input;
		node->next = target[index];
		target[index] = node;
	}
}

int main() {
	int V, E, S;
	scanf("%d %d %d", &V, &E, &S);
	graph = (Node**)malloc(sizeof(Node*) * (V + 1));
	for (int i = 1; i <= V; i++) {
		graph[i] = NULL;
		res[i] = INT_MAX;
	}
	for (int i = 0; i < E; i++) {
		int start, end, cost;
		scanf("%d %d %d", &start, &end, &cost);
		Edge* edge1 = (Edge*)malloc(sizeof(Edge));
		edge1->node = end;
		edge1->weight = cost;
		addEdge(graph, start, edge1);
		Edge* edge2 = (Edge*)malloc(sizeof(Edge));
		edge2->node = start;
		edge2->weight = cost;
		addEdge(graph, end, edge2);
	}

	pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	pq->count = 0;
	Edge* start = (Edge*)malloc(sizeof(Edge));
	start->node = S; start->weight = 0;
	res[S] = 0;
	queuePush(pq, start);
	while (1) {
		Edge* cur = queuePop(pq);
		if (cur == NULL) break;
		int curNode = cur->node;
		int curWeight = cur->weight;
		if (res[curNode] < curWeight) continue;
		Node* node = graph[curNode];
		while (node != NULL) {
			Edge* temp = node->data;
			temp->weight += curWeight;
			if (temp->weight < res[temp->node]) {
				res[temp->node] = temp->weight;
				queuePush(pq, temp);
			}
			node = node->next;
		}
	}

	for (int i = 1; i <= V; i++)	{
		if (res[i] == INT_MAX) printf("INF  ");
		else  printf("%d ", res[i]);
	}
	system("pause");
	return 0;
}