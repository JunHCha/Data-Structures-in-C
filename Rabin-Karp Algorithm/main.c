#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* parent = "abcdefgalsdkfjalskdjf";
char* pattern = "defgal";

void check(char* parent, char* pattern, int index) {
	int found = 1;
	int parentSize = strlen(pattern);
	for (int i = 0; i < parentSize; i++) {
		if (pattern[i] != parent[index + i]) {
			found = 0;
			break;
		}
	}
	if (found) {
		printf("Pattern found in index %d\n", index + 1);
	}
}

void rabinKarp(char* parent, char* pattern) {
	int parentSize = strlen(parent);
	int patternSize = strlen(pattern);
	int parentHash = 0, patternHash = 0, power = 1;
	for (int i = 0; i <= parentSize - patternSize; i++) {
		if (i == 0) {
			for (int j = 0; j < patternSize; j++) {
				parentHash += parent[patternSize - j - 1] * power;
				patternHash += pattern[patternSize - j - 1] * power;
				if (j < patternSize - 1) power *= 2;
			}
		}
		else {
			parentHash = 2 * (parentHash - power * parent[i - 1]) + parent[patternSize + i - 1];
		}
		if (parentHash == patternHash) {
			check(parent, pattern, i);
		}
	}
}

int main() {
	rabinKarp(parent, pattern);
	system("pause");
	return 0;
}

