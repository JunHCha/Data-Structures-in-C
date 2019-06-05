#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NUMBER 7
int list[NUMBER] = { 1, 23, 13, 24, 32, 7, 15 };
int tree[4 * NUMBER];

int init(int start, int end, int node) {
	if (start == end) return tree[node] = list[start];
	int mid = (start + end) / 2;
	return tree[node] = init(start, mid, node * 2) + init(mid + 1, end, node * 2 + 1);
}

int sum(int start, int end, int node, int rangeStart, int rangeEnd) {
	if (start > rangeEnd || rangeStart > end) return 0;
	if (rangeStart <= start && end <= rangeEnd) return tree[node];
	int mid = (start + end) / 2;
	return sum(start, mid, node * 2, rangeStart, rangeEnd) + sum(mid + 1, end, node * 2 + 1, rangeStart, rangeEnd);
}

void update(int startIdx, int endIdx, int node, int index, int data) {
	if (index < startIdx || endIdx < index) return;
	tree[node] += data;
	if (startIdx == endIdx) return;
	int mid = (startIdx + endIdx) / 2;
	update(startIdx, mid, node * 2, index, data);
	update(mid + 1, endIdx, node * 2 + 1, index, data);
}

int main() {
	init(0, NUMBER - 1, 1);
	printf("0-6 sum : %d\n", sum(0, NUMBER - 1, 1, 0, 6));
	printf("index 5 data + 3\n");
	update(0, NUMBER - 1, 1, 5, 3);
	printf("3-6 sum : %d\n", sum(0, NUMBER - 1, 1, 3, 6));
	system("pause");
	return 0;
}