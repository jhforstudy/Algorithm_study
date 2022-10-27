#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

enum Color {
	RED=0,
	BLACK=1
};

struct node {
	// key, left, right, parent, color
	int key;
	struct node* left;
	struct node* right;
	struct node* parent;
	enum Color color;
};

struct rbtree {
	struct node* root;
	struct node* NIL;
};

struct node create_nil = {
  .color = BLACK,
  .left = NULL,
  .right = NULL,
  .parent = NULL,
};
struct node* nil = &create_nil;

struct trunk {
	struct trunk* prev;
	char* str;
};

bool checkList(int* list, int value) {

	for (int i = 0; i < 15; i++) {
		if (list[i] == value) {
			return true;
		}
	}
	return false;
}

void del_node(struct node* n) {
	if (n != NULL) {
		del_node(n->left);
		del_node(n->right);
	}
	free(n);
}

void delete_rbtree(struct rbtree* tree) {
	del_node(tree->root);
	free(tree);
}

struct node* newNode(int k) {
	struct node* new = (struct node*)malloc(sizeof(struct node));

	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	new->key = k;
	new->color = RED;

	return new;
}

struct rbtree* newRBtree() {
	struct rbtree* tree = malloc(sizeof(struct rbtree));
	struct node* temp_nil = malloc(sizeof(struct node));

	temp_nil->left = NULL;
	temp_nil->right = NULL;
	temp_nil->parent = NULL;
	temp_nil->color = RED;

	tree->NIL = temp_nil;
	tree->root = tree->NIL;

	return tree;
}

struct node* node_nil(struct node* x) {
	if (x == NULL) {
		return nil;
	}
	else {
		return x;
	}
}

struct node* tree_successor(struct rbtree* t, struct node* n) {
	// right child가 존재할 경우, 우측 노드의 제일 왼쪽을 찾으면 됨
	if (n->right != NULL) {
		// temp가 NULL이 될때까지 왼쪽으로 이동
		struct node* temp_c = n->right;
		while (temp_c->left != NULL) {
			temp_c = temp_c->left;
		}
		return temp_c;
	}
	// right node가 없으면, n의 parent 선언 후
	struct node* temp_p = n->parent;
	// 위로 올라가면서 temp node가 left child가 될때까지 반복
	while (temp_p != NULL && n == temp_p->right) {
		n = temp_p;
		temp_p = temp_p->parent;
	}

	return temp_p;
}

struct node* tree_predeccessor(struct rbtree* t, struct node* n) {
	// left child가 존재할 경우, 좌측 노드의 제일 오른쪽을 찾으면 됨
	if (n->left != NULL) {
		// temp가 NULL이 될때까지 왼쪽으로 이동
		struct node* temp_c = n->left;
		while (temp_c->right != NULL) {
			temp_c = temp_c->right;
		}
		return temp_c;
	}
	// left node가 없으면, n의 parent 선언 후
	struct node* temp_p = n->parent;
	// 위로 올라가면서 temp node가 right child가 될때까지 반복
	while (temp_p != NULL && n == temp_p->left) {
		n = temp_p;
		temp_p = temp_p->parent;
	}

	return temp_p;
}

void left_Rotate(struct rbtree* tree, struct node* x) {
	// x의 right child
	struct node* y = x->right;

	// y의 left child를 x의 right에 붙임
	x->right = y->left;

	// x의 right child의 parent 연결
	if (x->right != NULL) {
		x->right->parent = x;
	}

	// y의 parent 연결
	y->parent = x->parent;

	// x의 부모 노드가 NULL이면, y는 root
	if (x->parent == NULL) {
		tree->root = y;
	}

	// x가 left child이면
	else if (x == x->parent->left) {
		// x의 부모노드의 left에 y를 연결
		x->parent->left = y;
	}
	else {
		// x의 부모노드의 right에 y를 연결
		x->parent->right = y;
	}

	// y의 left를 x로
	y->left = x;
	// x의 parent를 y로
	x->parent = y;
}

void right_Rotate(struct rbtree* tree, struct node* x) {

	// x의 left child
	struct node* y = x->left;

	// y의 right child를 x의 left에 붙임
	x->left = y->right;

	// x의 right이 안비었으면, right child의 parent 연결
	if (x->right != NULL) {
		x->right->parent = x;
	}

	// y의 parent 연결
	y->parent = x->parent;

	// x의 부모 노드가 NULL이면, y는 root
	if (x->parent == NULL) {
		tree->root = y;
	}

	// x가 right child이면
	else if (x == x->parent->right) {
		// x의 부모노드의 right에 y를 연결
		x->parent->right = y;
	}
	else {
		// x의 부모노드의 left에 y를 연결
		x->parent->left = y;
	}

	// y의 left를 x로
	y->right = x;
	// x의 parent를 y로
	x->parent = y;
}

struct node* RB_find(struct rbtree* tree, int key) {
	struct node* temp;
	temp = tree->root;

	while (temp != nil) {
		if (key == temp->key) {
			return temp;
		}
		else if (key > temp->key) {
			temp = temp->right;
		}

		else if (key < temp->key) {
			temp = temp->left;
		}
	}

	return NULL;
}

void RB_insert_fixup(struct rbtree* tree, struct node* new_node) {
	struct node* y;
	// new_node가 root가 아니면서 RED일 동안 반복 
	while (new_node->parent != NULL && new_node->parent->color == RED) {
		if (new_node->parent == new_node->parent->parent->left) {
			y = new_node->parent->parent->right;

			// 부모, 삼촌 RED
			if (y != NULL && y->color == RED) {
				new_node->parent->color = BLACK;
				y->color = BLACK;
				new_node->parent->parent->color = RED;
				new_node = new_node->parent->parent;
			}
			// 부모 RED, 삼촌 BLACK
			else {
				if (new_node == new_node->parent->right) {
					new_node = new_node->parent;
					left_Rotate(tree, new_node);
				}

				new_node->parent->color = BLACK;
				new_node->parent->parent->color = RED;
				right_Rotate(tree, new_node->parent->parent);
			}
		}
		else {
			y = new_node->parent->parent->left;

			// 부모, 삼촌 RED
			if (y != NULL && y->color == RED) {
				new_node->parent->color = BLACK;
				y->color = BLACK;
				new_node->parent->parent->color = RED;
				new_node = new_node->parent->parent;
			}
			// 부모 RED, 삼촌 BLACK
			else {
				if (new_node == new_node->parent->left) {
					new_node = new_node->parent;
					right_Rotate(tree, new_node);
				}

				new_node->parent->color = BLACK;
				new_node->parent->parent->color = RED;
				left_Rotate(tree, new_node->parent->parent);
			}
		}

	}
	// 완료 후, root의 색을 black으로
	tree->root->color = BLACK;
}

void RB_insert(struct rbtree* tree, int k) {
	// NIL과 root node
	struct node* y = tree->NIL;
	struct node* temp = tree->root;

	// 새로운 노드 생성
	struct node* new_node = newNode(k);

	// root가 null이면, 새로운 노드를 root로
	if (tree->root == tree->NIL) {
		new_node->color = BLACK;
		tree->root = new_node;
	}
	else {
		// BST 트리와 같은 방식으로 노드 삽입
		while (temp != NULL) {
			y = temp;
			// 만약 새로운 노드의 key가 x보다 크면
			if (k > temp->key) {
				// 오른쪽으로 이동
				temp = temp->right;
			}
			else {
				// 아니면, 왼쪽
				temp = temp->left;
			}
		}

		// 새로운 노드를 y 아래에 연결
		new_node->parent = y;

		// 새로운 노드의 키 값에 따라, 왼 or 오 선택
		if (k > y->key) {
			y->right = new_node;
		}
		else {
			y->left = new_node;
		}

		// Fixup 수행
		RB_insert_fixup(tree, new_node);

	}
}

void tree_transplant(struct rbtree* tree, struct node* n_1, struct node* n_2) {
	// tree의 특성 유지
	// n_1의 parent 없으면, n_2를 root로 설정
	if (n_1->parent == NULL) {
		tree->root = n_2;
	}
	// n_1이 left child 이면, n_1의 left child을 n_2로 설정
	else if (n_1 == n_1->parent->left) {
		n_1->parent->left = n_2;
	}
	// n_1이 right child 이면, n_1의 right child를 n_2로 설정
	else {
		n_1->parent->right = n_2;
	}

	// n_2가 있으면
	if (n_2 != NULL) {
		// n_2의 parent을 n_1의 parent로 설정
		n_2->parent = n_1->parent;
	}
}

void RB_delete_fixup(struct rbtree* tree, struct node* delete_node) {
	struct node* s;
	if (delete_node->parent->left == delete_node) {
		s = delete_node->parent->right;
	}
	else {
		s = delete_node->parent->left;
	}
	struct node* s_left = s->left;
	struct node* s_right = s->right;
	while (delete_node != tree->root && delete_node->color == BLACK) {
		if (delete_node == delete_node->parent->left) {
			s = delete_node->parent->right;
			if (s->color == RED) {
				s->color = BLACK;
				delete_node->parent->color = RED;
				left_Rotate(tree, delete_node->parent);
				s = delete_node->parent->right;
			}
			s_left = node_nil(s_left);
			s_right = node_nil(s_right);
			if ((s_left->color == BLACK) && (s_right->color == BLACK)) {
				s->color = RED;
				delete_node = delete_node->parent;
			}
			else {
				if (s_right->color == BLACK) {
					s_left->color = BLACK;
					s->color = RED;
					right_Rotate(tree, s);
					s = delete_node->parent->right;
				}
				s->color = delete_node->parent->color;
				delete_node->parent->color = BLACK;
				s->right->color = BLACK;
				left_Rotate(tree, delete_node->parent);
				delete_node = tree->root;
			}
		}
		else {
			s = delete_node->parent->left;
			if (s->color == RED) {
				s->color = BLACK;
				delete_node->parent->color = RED;
				right_Rotate(tree, delete_node->parent);
				s = delete_node->parent->left;
			}
			s_left = node_nil(s_left);
			s_right = node_nil(s_right);
			if ((s_right->color == BLACK) && (s_left->color == BLACK)) {
				s->color = RED;
				delete_node = delete_node->parent;
			}
			else {
				if (s_left->color == BLACK) {
					s_right->color = BLACK;
					s->color = RED;
					left_Rotate(tree, s);
					s = delete_node->parent->left;
				}
				s->color = delete_node->parent->color;
				delete_node->parent->color = BLACK;
				s->left->color = BLACK;
				right_Rotate(tree, delete_node->parent);
				delete_node = tree->root;
			}
		}
	}
	delete_node->color = BLACK;
}

void RB_delete(struct rbtree* tree, int k) {
	// 삭제될 노드
	struct node* delete_node = RB_find(tree, k);
	// 그 노드를 가리키는 임시 노드
	struct node* y = delete_node;
	// 그 노드의 원래 위치 및 색 기억
	struct node* temp;
	enum Color temp_col = delete_node->color;

	// 삭제할 노드의 왼쪽이 없다면,
	if (delete_node->left == NULL) {
		temp = node_nil(delete_node->right);
		tree_transplant(tree, delete_node, temp);
		free(delete_node);
	}
	// 삭제할 노드의 오른쪽이 없다면,
	else if (delete_node->right == NULL) {
		temp = node_nil(delete_node->left);
		tree_transplant(tree, delete_node, temp);
		free(delete_node);
	}

	// 삭제할 노드의 양쪽 child가 다 존재할 경우
	else {
		y = tree_successor(tree, delete_node);
		temp_col = y->color;
		temp = node_nil(y->right);


		if (y->parent == delete_node) {
			temp->parent = y;
		}
		else {
			tree_transplant(tree, y, temp);
			y->right = delete_node->right;
			y->right->parent = y;
		}
		tree_transplant(tree, delete_node, y);
		y->left = delete_node->left;
		y->left->parent = y;
		y->color = delete_node->color;
		free(delete_node);
	}

	if (temp_col == BLACK) {
		RB_delete_fixup(tree, temp);
	}

	if (tree->root == nil) {
		tree->root = NULL;
	}
	else if (nil->parent != NULL) {
		if (nil->parent->left == nil) {
			nil->parent->left = NULL;
		}
		else {
			nil->parent->right = NULL;
		}
	}
	nil->parent = NULL;

}

struct node* get_closest(struct node* n1, struct node* n2, int k) {
	if (abs(k - n1->key) < abs(k - n2->key)) {
		return n1;
	}
	else {
		return n2;
	}
}

struct node* find_closest(struct node* n, int k) {
	if (k < n->key && n->left != NULL) {
		struct node* temp = find_closest(n->left, k);
		return get_closest(n, temp, k);
	}
	else if (k > n->key && n->right != NULL) {
		struct node* temp = find_closest(n->right, k);
		return get_closest(n, temp, k);
	}
	else {
		return n;
	}
}

int nearest_neighbor(struct rbtree* tree, int k) {
	struct node* n;
	n = find_closest(tree->root, k);

	return n->key;
}

void show_trunks(struct trunk* p) {
	if (p == NULL) {
		return;
	}
	show_trunks(p->prev);
	printf("%s", p->str);
}

void Print_BST(struct node* n, struct trunk* prev, bool is_left) {
	if (n == NULL) {
		return;
	}
	char* prev_str = "    ";

	struct trunk* trunk_temp= (struct trunk*)malloc(sizeof(struct trunk));
	trunk_temp->prev = prev;
	trunk_temp->str = prev_str;

	Print_BST(n->right, trunk_temp, true);

	if (!prev) {
		trunk_temp->str = "---";
	}
	else if (is_left) {
		trunk_temp->str = ",---";
		prev_str = "   |";
	}
	else {
		trunk_temp->str = "`---";
		prev->str = prev_str;
	}
	show_trunks(trunk_temp);
	printf(" %d", n->key);
	if (n->color == RED) {
		printf("%s\n", "○");
	}
	else {
		printf("%s\n", "●");
	}

	if (prev) {
		prev->str = prev_str;
	}
	trunk_temp->str = "   |";
	Print_BST(n->left, trunk_temp, false);
}

int main() {
	// RB tree 생성
	struct rbtree* tree = newRBtree();

	srand(time(NULL));
	int rand_int;
	// identical value 대입을 위한 체크용 리스트
	int* A = (int*)malloc(15 * sizeof(int));

	// Q1. 15개의 랜덤 숫자와 노드 생성
	printf("Q1. Add 15 random values to red-black tree\n=================================\n");
	for (int i = 0; i < 15; i++) {
		do {
			rand_int = rand() % 50;
			//rand_int = i;
		} while (checkList(A, rand_int));
		A[i] = rand_int;
		// A[i]에 숫자 대입
		// key를 RB tree에 삽입
		RB_insert(tree, rand_int);
	}
	// RB tree 출력
	Print_BST(tree->root, NULL, false);

	// Q2. 5개의 숫자 대입
	printf("\n\nQ2. Add 5 values to red-black tree and print\n=================================\n");
	printf("Add %d\n", 13);
	RB_insert(tree, 13);
	Print_BST(tree->root, NULL, false);
	printf("\nAdd %d\n", 22);
	RB_insert(tree, 22);
	Print_BST(tree->root, NULL, false);
	printf("\nAdd %d\n", 21);
	RB_insert(tree, 21);
	Print_BST(tree->root, NULL, false);
	printf("\nAdd %d\n", 11);
	RB_insert(tree, 11);
	Print_BST(tree->root, NULL, false);
	printf("\nAdd %d\n", 45);
	RB_insert(tree, 45);
	Print_BST(tree->root, NULL, false);

	// Q3. 가까운 이웃 찾기
	printf("\n\nQ3. Find nearest neighbor\n=================================\n");
	Print_BST(tree->root, NULL, false);
	printf("%d의 제일 가까운 이웃: %d\n", 5, nearest_neighbor(tree, 5));
	printf("%d의 제일 가까운 이웃: %d\n", 23, nearest_neighbor(tree, 23));
	printf("%d의 제일 가까운 이웃: %d\n", 38, nearest_neighbor(tree, 38));

	// Q4. 5개의 숫자 삭제
	printf("\n\nQ4. Delete 5 values in red-black tree and print\n=================================\n");
	printf("Delete %d\n", 13);
	RB_delete(tree, 13);
	Print_BST(tree->root, NULL, false);
	printf("\nDelete %d\n", 22);
	RB_delete(tree, 22);
	Print_BST(tree->root, NULL, false);
	printf("\nDelete %d\n", 45);
	RB_delete(tree, 45);
	Print_BST(tree->root, NULL, false);
	printf("\nDelete %d\n", 11);
	RB_delete(tree, 11);
	Print_BST(tree->root, NULL, false);
	printf("\nDelete root(%d)\n", tree->root->key);
	RB_delete(tree, tree->root->key);
	Print_BST(tree->root, NULL, false);

	// 메모리 반납
	delete_rbtree(tree);
}