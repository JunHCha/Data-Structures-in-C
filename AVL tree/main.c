#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int getMax(int a, int b) {
	if (a > b) return a;
	else return b;
}

typedef struct Node {
	int data;
	int height;
	struct Node* leftChild;
	struct Node* rightChild;
} Node;

int getHeight(Node* node) {
	if (!node) return 0;
	return node->height;
}

void setHeight(Node* node) {
	if (!node) node->height = 0;
	node->height = getMax(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
}

Node* rotateLL(Node* node) {
	Node* left = node->leftChild;
	node->leftChild = left->rightChild;
	left->rightChild = node;
	setHeight(node);
	return left;
}

Node* rotateRR(Node* node) {
	Node* right = node->rightChild;
	node->rightChild = right->leftChild;
	right->leftChild = node;
	setHeight(node);
	return right;
}

Node* rotateLR(Node* node) {
	Node* left = node->leftChild;
	node->leftChild = rotateRR(left);
	return rotateLL(node);
}

Node* rotateRL(Node* node) {
	Node* right = node->rightChild;
	node->rightChild = rotateLL(right);
	return rotateRR(node);
}

int getBF(Node* node) {
	if (!node) return 0;
	return getHeight(node->leftChild) - getHeight(node->rightChild);
}

Node* balance(Node* node) {
	int bF = getBF(node);
	if (bF >= 2) {
		if (getBF(node->leftChild) >= 1) node = rotateLL(node);
		else node = rotateLR(node);
	}
	else if (bF <= -2) {
		if (getBF(node->rightChild) <= -1) node = rotateRR(node);
		else node = rotateRL(node);
	}
	setHeight(node);
	return node;
}

Node* insertNode(Node* node, int data) {
	if (!node) {
		node = (Node*)malloc(sizeof(Node));
		node->leftChild = node->rightChild = NULL;
		node->data = data;
		node->height = 1;
	}
	else if (node->data > data) {
		node->leftChild = insertNode(node->leftChild, data);
		node = balance(node);
	}
	else if (node->data < data) {
		node->rightChild = insertNode(node->rightChild, data);
		node = balance(node);
	}
	else {
		printf("! : Duplicated data\n");
	}
	return node;
}

Node* avl = NULL;

void display(Node* node, int level) {
	if (node) {
		display(node->rightChild, level + 1);
		printf("\n");
		if (node == avl) {
			printf("(root)");
		}
		for (int i = 0; i < level && node != avl ; i++) {
			printf("    ");
		}
		printf("%d(%d)", node->data, getHeight(node));
		display(node->leftChild, level + 1);
	}
}

int main() {
	avl = insertNode(avl, 21);
	avl = insertNode(avl, 12);
	avl = insertNode(avl, 7);
	avl = insertNode(avl, 4);
	avl = insertNode(avl, 2);
	avl = insertNode(avl, 1);
	avl = insertNode(avl, 15);
	avl = insertNode(avl, 16);
	avl = insertNode(avl, 234);
	avl = insertNode(avl, 162);
	avl = insertNode(avl, -12);
	avl = insertNode(avl, -3);
	avl = insertNode(avl, 126);
	avl = insertNode(avl, 26);

	display(avl, 2);
	printf("\n");
	system("pause");
	return 0;
}