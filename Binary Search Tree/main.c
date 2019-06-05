#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* leftChild;
	struct Node* rightChild;
} Node;

Node* insertNode(Node* root, int data) {
	if (root == NULL) {
		root = (Node*)malloc(sizeof(Node));
		root->data = data;
		root->leftChild = root->rightChild = NULL;
		return root;
	}
	else {
		if (root->data > data) root->leftChild = insertNode(root->leftChild, data);
		else root->rightChild = insertNode(root->rightChild, data);
	}
	return root;
}

Node* searchNode(Node* root, int data) {
	if (root == NULL) return NULL;
	if (root->data == data) return root;
	else if (root->data > data) return searchNode(root->leftChild, data);
	else return searchNode(root->rightChild, data);
}

Node* findMinNode(Node* root) {
	Node* left = root->leftChild;
	if (root->leftChild == NULL) return root;
	else return findMinNode(left);
}

Node* deleteNode(Node* root, int data) {
	Node* node = NULL;
	if (root == NULL) return NULL;
	if (root->data > data) root->leftChild = deleteNode(root->leftChild, data);
	if (root->data < data) root->rightChild = deleteNode(root->rightChild, data);
	else {
		if (root->leftChild != NULL && root->rightChild != NULL) {
			node = findMinNode(root->rightChild);
			root->data = node->data;
			root->rightChild = deleteNode(root->rightChild, node->data);
		}
		else {
			node = (root->leftChild == NULL) ? root->rightChild : root->leftChild;
			free(root);
			return node;
		}
	}
	return root;
}

void preorder(Node* root) {
	if (root == NULL) return;
	printf("%d ", root->data);
	preorder(root->leftChild);
	preorder(root->rightChild);
}

int main() {
	Node* tree = NULL;
	int n, x;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)	{
		scanf("%d", &x);
		tree = insertNode(tree, x);
	}
	preorder(tree);
	printf("\n searching data :	");
	scanf("%d", &n);
	tree = searchNode(tree, n);
	preorder(tree);
	system("pause");
	return 0;
}