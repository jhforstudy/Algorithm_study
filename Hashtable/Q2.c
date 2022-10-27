#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
	int key;
	int probe_count;
};

struct node* hashTable_1 = NULL;
struct node* hashTable_2 = NULL;
struct node* hashTable_3 = NULL;

int total_probe_count;

int size_1 = 37;
int size_2 = 37;
int size_3 = 37;


int linear_probing(struct node* B, int key, int size, int* ptr) {
	int temp_hash = (key + *(ptr)) % size;
	// 만약 그 자리에 무언가 있으면, 다시 해싱
	if (B[temp_hash].key >= 0) {
		// Average probe count
		total_probe_count++;
		// Open Address
		*(ptr) += 1;
		temp_hash = linear_probing(B, key, size, ptr);
	}
	return temp_hash;
}

int quadratic_probing(struct node* B, int key, int size, int* ptr) {
	int temp_hash = (key + *(ptr) * 1 + ((*(ptr)) * (*(ptr))) * 3) % size;
	// 만약 그 자리에 무언가 있으면, 다시 해싱
	if (B[temp_hash].key >= 0) {
		// Average probe count
		total_probe_count++;
		// Open Address
		*(ptr) += 1;
		temp_hash = quadratic_probing(B, key, size, ptr);
	}
	return temp_hash;
}

int double_hashing(struct node* B, int key, int size, int* ptr) {
	int h1 = key % size;
	int h2 = 1 + (key % (size - 1));
	int temp_hash = (h1 + (*(ptr)) * h2) % size;
	// 만약 그 자리에 무언가 있으면, 다시 해싱
	if (B[temp_hash].key >= 0) {
		// Average probe count
		total_probe_count++;
		// Open Address
		*(ptr) += 1;
		temp_hash = double_hashing(B, key, size, ptr);
	}
	return temp_hash;
}

void insert_1(struct node* B, int key, int size) {
	int total_probe_count = 0;
	// probe 횟수 측정
	int probe_count = 0;
	int* cnt_ptr = &(probe_count);
	// hash 계산
	int hash_index = linear_probing(B, key, size, cnt_ptr);

	// node 생성
	struct node new_node;
	new_node.key = key;
	new_node.probe_count = probe_count;

	// 해당 index에 노드를 추가
	B[hash_index] = new_node;
}

void insert_2(struct node* B, int key, int size) {
	int total_probe_count = 0;
	// probe 횟수 측정
	int probe_count = 0;
	int* cnt_ptr = &(probe_count);
	// hash 계산
	int hash_index = quadratic_probing(B, key, size, cnt_ptr);

	// node 생성
	struct node new_node;
	new_node.key = key;
	new_node.probe_count = probe_count;

	// 해당 index에 노드를 추가
	B[hash_index] = new_node;
}

void insert_3(struct node* B, int key, int size) {
	int total_probe_count = 0;
	// probe 횟수 측정
	int probe_count = 0;
	int* cnt_ptr = &(probe_count);
	// hash 계산
	int hash_index = linear_probing(B, key, size, cnt_ptr);

	// node 생성
	struct node new_node;
	new_node.key = key;
	new_node.probe_count = probe_count;

	// 해당 index에 노드를 추가
	B[hash_index] = new_node;
}

void print(struct node* B, int size) {
	int longest_len = 0;

	for (int i = 0; i < size; i++) {
		// 데이터 출력
		if (B[i].key < 0) {
			printf("Bucket[%d]: NULL", i);
		}
		else {
			printf("Bucket[%d]: %d", i, B[i].key);
		}

		// 제일 큰 probe_count 검사
		if (B[i].probe_count >= longest_len) {
			longest_len = B[i].probe_count;
		}

		printf("\n");
	}

	float average = total_probe_count / (float)size ;

	printf("\n======================\n");
	printf("Longest probe count : %d\n", longest_len);
	printf("Average probe count : %.2f\n", (average));
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
	hashTable_1 = (struct node*)malloc(size_1 * sizeof(struct node));
	// identical value 대입을 위한 체크용 리스트
	int* check_list_1 = (int*)malloc(30 * sizeof(int));
	// 숫자 삽입
	for (int i = 0; i < 30; i++) {
		do {
			rand_int = rand() % 1000;
		} while (checkList(check_list_1, rand_int));
		check_list_1[i] = rand_int;
		insert_1(hashTable_1, rand_int, size_1);
	}
	// print
	printf("Hash Table 1\n\n");
	print(hashTable_1, size_1);
	// memory 반납
	free(hashTable_1);
	free(check_list_1);

	// Table 2
	// memory 할당, num 변수 초기화
	hashTable_2 = (struct node*)malloc(size_2 * sizeof(struct node));
	// identical value 대입을 위한 체크용 리스트
	int* check_list_2 = (int*)malloc(30 * sizeof(int));
	// 숫자 삽입
	for (int i = 0; i < 30; i++) {
		do {
			rand_int = rand() % 1000;
		} while (checkList(check_list_2, rand_int));
		check_list_2[i] = rand_int;
		insert_2(hashTable_2, rand_int, size_2);
	}
	// print
	printf("Hash Table 2\n\n");
	print(hashTable_2, size_2);
	// memory 반납
	free(hashTable_2);
	free(check_list_2);

	// Table 3
	// memory 할당, num 변수 초기화
	hashTable_3 = (struct node*)malloc(size_3 * sizeof(struct node));
	// identical value 대입을 위한 체크용 리스트
	int* check_list_3 = (int*)malloc(30 * sizeof(int));
	// 숫자 삽입
	for (int i = 0; i < 30; i++) {
		do {
			rand_int = rand() % 1000;
		} while (checkList(check_list_3, rand_int));
		check_list_3[i] = rand_int;
		insert_3(hashTable_3, rand_int, size_3);
	}
	// print
	printf("Hash Table 3\n\n");
	print(hashTable_3, size_3);
	// memory 반납
	free(hashTable_3);
	free(check_list_3);

}

