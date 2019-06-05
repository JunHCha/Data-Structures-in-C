#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1001

typedef struct Node {
	int index;
	struct Node* next;
} Node;

Node** adj;
int n, m, c[MAX_SIZE];

void addFront(Node* root, int index) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->next = root->next;
	node->index = index;
	root->next = node;
}

void dfs(int index) {
	if (c[index]) return;
	c[index] = 1;
	Node* cur = adj[index]->next;
	printf("%d ", index);
	while (cur) {
		int next_i = cur->index;
		dfs(next_i);
		cur = cur->next;
	}
}

int main () {
	scanf("%d %d", &n, &m);
	adj = (Node**)malloc(sizeof(Node*) * (n + 1));
	for (int i = 1; i <= n; i++) {
		adj[i] = (Node*)malloc(sizeof(Node));
		adj[i]->next = NULL;
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		addFront(adj[a], b);
		addFront(adj[b], a);
	}
	dfs(1);
	system("pause");
	return 0;
}