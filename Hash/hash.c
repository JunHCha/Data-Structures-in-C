#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 10007
#define INPUT_SIZE 5000

typedef struct {
	int id;
	char name[20];
} Student;

void initHash(Student** hash) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		hash[i] = (Student*)malloc(sizeof(Student));
		hash[i] = NULL;
	}
}


void destructor(Student** hash) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hash[i] != NULL) free(hash[i]);
	}
}

int findKey(Student** hash, int id) {
	int i = id % TABLE_SIZE;
	int count = 0;
	while (1) {
		if (hash[i % TABLE_SIZE] == NULL) { //i가 해시테이블 크기를 초과할 경우를 대비해서 한번 더 mod 연산을 수행
			return i % TABLE_SIZE;
		}
		count++;
		i = id % TABLE_SIZE + count * count;
	}
}

int search(Student** hash, int id) {
	int i = id % TABLE_SIZE;
	int count = 0;
	while (1) {
		if (hash[i % TABLE_SIZE] == NULL) return -1;
		else if (hash[i % TABLE_SIZE]->id == id) return i;
		count++;
		i = id % TABLE_SIZE + count * count;
	}
}

void add(Student** hash, Student* input, int key) {
	hash[key] = input;
}

Student* getValue(Student** hash, int key) {
	return hash[key];
}

void show(Student** hash) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hash[i] != NULL) 
			printf("key : %d, name : %s\n", i, hash[i]->name);
	}
}

int main() {
	Student** hashTable;
	hashTable = (Student**)malloc(sizeof(Student*) * TABLE_SIZE);
	initHash(hashTable);
	for (int i = 0; i < INPUT_SIZE; i++) {
		Student* student = (Student*)malloc(sizeof(Student));
		student->id = rand() % 100000;
		sprintf(student->name,"man(%d)",student->id);
		if (search(hashTable, student->id) == -1)
			add(hashTable, student, findKey(hashTable, student->id));
	}
	show(hashTable);
	destructor(hashTable);

	system("pause");
	return 0;
}