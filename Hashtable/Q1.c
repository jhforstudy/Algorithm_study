#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
	int key;
	struct node* next_node;
};

struct bucket {
	struct node* head;
	int num;	// �ش� index�� data ����
};

struct bucket* hashTable_1 = NULL;
struct bucket* hashTable_2 = NULL;
struct bucket* hashTable_3 = NULL;

int size_1 = 5;
int size_2 = 7;
int size_3 = 13;

struct node* createNode(int key) {
	// ���� ����
	struct node* new_node;
	
	// �޸� �Ҵ�
	new_node = (struct node*)malloc(sizeof(struct node));

	// key, next_node �ʱ�ȭ
	new_node->key = key;
	new_node->next_node = NULL;

	return new_node;
}

int hash_function(int key, int size) {
	return (key % size);
}

void insert(struct bucket* B, int key, int size) {
	// hash ���
	int hash_index = hash_function(key, size);

	// node ����
	struct node* new_node = createNode(key);

	// ���� �ش� index�� �ƹ��͵� ������, head�� �߰�
	if (B[hash_index].num == 0) {
		B[hash_index].num = 1;
		B[hash_index].head = new_node;
	}

	// �ƴϸ�, �ش� head�� next�� �߰�
	else {
		new_node->next_node = B[hash_index].head;	// new_node�� next�� �ش� hash index�� head�� �ΰ�
		B[hash_index].head = new_node;	// new_node�� �ش� hash index�� head��.
		B[hash_index].num++;
	}

}

void print(struct bucket* B, int size) {
	int shortest_len = 50;
	int longest_len = 0;
	float sum_len = 0;
	struct node* temp = NULL;

	for (int i = 0; i < size; i++) {
		struct node* temp = B[i].head;
		printf("Bucket[%d]: ", i);
		// next_node�� ���� ������ �ش� hash index�� �� ���� ���
		while (temp != NULL) {
			printf("%d -> ", temp->key);

			// ���� ���� �̵�
			temp = temp->next_node;
		}

		// ���� ���� �������� �˻�

		if (B[i].num <= shortest_len) {
			shortest_len = B[i].num;
		}
		else if (B[i].num >= longest_len) {
			longest_len = B[i].num;
		}
		
		sum_len += B[i].num;

		printf("\n");
	}

	printf("\n======================\n");
	printf("Shortest length : %d\n", shortest_len);
	printf("Longest length : %d\n", longest_len);
	printf("Average length : %.2f\n", sum_len/size);
	printf("======================\n\n");
}

bool checkList(int* list, int value) {
	
	for (int i = 0; i < 50; i++) {
		if (list[i] == value) {
			return true;
		}
	}
	return false;
}

int main() {
	srand(time(NULL));
	int rand_int;

	// Table 1
	// memory �Ҵ�, num ���� �ʱ�ȭ
	hashTable_1 = (struct bucket*)malloc(size_1 * sizeof(struct bucket));
	for (int i = 0; i < size_1; i++) {
		hashTable_1[i].num = 0;
	}
	// identical value ������ ���� üũ�� ����Ʈ
	int* check_list_1 = (int*)malloc(50 * sizeof(int));
	// ���� ����
	for (int i = 0; i < 50; i++) {
		do {
			rand_int = rand() % 1000;
		} while (checkList(check_list_1, rand_int));
		check_list_1[i] = rand_int;
		insert(hashTable_1, rand_int, size_1);
	}
	// print
	printf("Hash Table 1\n\n");
	print(hashTable_1, size_1);
	// memory �ݳ�
	free(hashTable_1);
	free(check_list_1);

	// Table 2
	// memory �Ҵ�, num ���� �ʱ�ȭ
	hashTable_2 = (struct bucket*)malloc(size_2 * sizeof(struct bucket));
	for (int i = 0; i < size_2; i++) {
		hashTable_2[i].num = 0;
	}
	// identical value ������ ���� üũ�� ����Ʈ
	int* check_list_2 = (int*)malloc(50 * sizeof(int));
	// ���� ����
	for (int i = 0; i < 50; i++) {
		do {
			rand_int = rand() % 1000;
		} while (checkList(check_list_2, rand_int));
		check_list_2[i] = rand_int;
		insert(hashTable_2, rand_int, size_2);
	}
	// print
	printf("Hash Table 2\n\n");
	print(hashTable_2, size_2);
	// memory �ݳ�
	free(hashTable_2);
	free(check_list_2);

	// Table 3
	// memory �Ҵ�, num ���� �ʱ�ȭ
	hashTable_3 = (struct bucket*)malloc(size_3 * sizeof(struct bucket));
	// memory �Ҵ�, num ���� �ʱ�ȭ
	for (int i = 0; i < size_3; i++) {
		hashTable_3[i].num = 0;
	}
	// identical value ������ ���� üũ�� ����Ʈ
	int* check_list_3 = (int*)malloc(50 * sizeof(int));
	// ���� ����
	for (int i = 0; i < 50; i++) {
		do {
			rand_int = rand() % 1000;
		} while (checkList(check_list_3, rand_int));
		check_list_3[i] = rand_int;
		insert(hashTable_3, rand_int, size_3);
	}
	// print
	printf("Hash Table 3\n\n");
	print(hashTable_3, size_3);
	// memory �ݳ�
	free(hashTable_3);
	free(check_list_3);

}

