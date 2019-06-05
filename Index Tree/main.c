#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define NUMBER 7

int tree[7];

int sum(int i) {
	int res = 0;
	while (i > 0) {
		res += tree[i];
		i -= (i & -i);
	}
	return res;
}

int update(int i, int diff) {
	while (i <= NUMBER) {
		tree[i] += diff;
		i += (i & -i);
	}
}

int getSectionSum(int start, int end) {
	return sum(end) - sum(start - 1);
}

int main() {
	update(1, 7);
	update(2, 2);
	update(3, 4);
	update(4, 5);
	update(5, 12);
	update(6, 32);
	update(7, 3);
	printf("1 ~ 7 sum : %d\n", getSectionSum(1, 7));
	system("pause");
	return 0;
}