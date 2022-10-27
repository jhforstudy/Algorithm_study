#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
	int key;
	struct node* next_node;
};

struct bucket {
	struct node* head;
	int num;	// 해당 index의 data 개수
};

struct bucket* hashTable_1 = NULL;
struct bucket* hashTable_2 = NULL;
struct bucket* hashTable_3 = NULL;

int size_1 = 5;
int size_2 = 7;
int size_3 = 13;

struct node* createNode(int key) {
	// 변수 선언
	struct node* new_node;
	
	// 메모리 할당
	new_node = (struct node*)malloc(sizeof(struct node));

	// key, next_node 초기화
	new_node->key = key;
	new_node->next_node = NULL;

	return new_node;
}

int hash_function(int key, int size) {
	return (key % size);
}

void insert(struct bucket* B, int key, int size) {
	// hash 계산
	int hash_index = hash_function(key, size);

	// node 생성
	struct node* new_node = createNode(key);

	// 만약 해당 index에 아무것도 없으면, head에 추가
	if (B[hash_index].num == 0) {
		B[hash_index].num = 1;
		B[hash_index].head = new_node;
	}

	// 아니면, 해당 head의 next에 추가
	else {
		new_node->next_node = B[hash_index].head;	// new_node의 next를 해당 hash index의 head로 두고
		B[hash_index].head = new_node;	// new_node를 해당 hash index의 head로.
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
		// next_node가 없을 때까지 해당 hash index의 각 원소 출력
		while (temp != NULL) {
			printf("%d -> ", temp->key);

			// 다음 노드로 이동
			temp = temp->next_node;
		}

		// 제일 작은 길이인지 검사

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
	// memory 할당, num 변수 초기화
	hashTable_1 = (struct bucket*)malloc(size_1 * sizeof(struct bucket));
	for (int i = 0; i < size_1; i++) {
		hashTable_1[i].num = 0;
	}
	// identical value 대입을 위한 체크용 리스트
	int* check_list_1 = (int*)malloc(50 * sizeof(int));
	// 숫자 삽입
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
	// memory 반납
	free(hashTable_1);
	free(check_list_1);

	// Table 2
	// memory 할당, num 변수 초기화
	hashTable_2 = (struct bucket*)malloc(size_2 * sizeof(struct bucket));
	for (int i = 0; i < size_2; i++) {
		hashTable_2[i].num = 0;
	}
	// identical value 대입을 위한 체크용 리스트
	int* check_list_2 = (int*)malloc(50 * sizeof(int));
	// 숫자 삽입
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
	// memory 반납
	free(hashTable_2);
	free(check_list_2);

	// Table 3
	// memory 할당, num 변수 초기화
	hashTable_3 = (struct bucket*)malloc(size_3 * sizeof(struct bucket));
	// memory 할당, num 변수 초기화
	for (int i = 0; i < size_3; i++) {
		hashTable_3[i].num = 0;
	}
	// identical value 대입을 위한 체크용 리스트
	int* check_list_3 = (int*)malloc(50 * sizeof(int));
	// 숫자 삽입
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
	// memory 반납
	free(hashTable_3);
	free(check_list_3);

}

