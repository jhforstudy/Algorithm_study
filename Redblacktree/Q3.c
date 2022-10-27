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
	// right child�� ������ ���, ���� ����� ���� ������ ã���� ��
	if (n->right != NULL) {
		// temp�� NULL�� �ɶ����� �������� �̵�
		struct node* temp_c = n->right;
		while (temp_c->left != NULL) {
			temp_c = temp_c->left;
		}
		return temp_c;
	}
	// right node�� ������, n�� parent ���� ��
	struct node* temp_p = n->parent;
	// ���� �ö󰡸鼭 temp node�� left child�� �ɶ����� �ݺ�
	while (temp_p != NULL && n == temp_p->right) {
		n = temp_p;
		temp_p = temp_p->parent;
	}

	return temp_p;
}

struct node* tree_predeccessor(struct rbtree* t, struct node* n) {
	// left child�� ������ ���, ���� ����� ���� �������� ã���� ��
	if (n->left != NULL) {
		// temp�� NULL�� �ɶ����� �������� �̵�
		struct node* temp_c = n->left;
		while (temp_c->right != NULL) {
			temp_c = temp_c->right;
		}
		return temp_c;
	}
	// left node�� ������, n�� parent ���� ��
	struct node* temp_p = n->parent;
	// ���� �ö󰡸鼭 temp node�� right child�� �ɶ����� �ݺ�
	while (temp_p != NULL && n == temp_p->left) {
		n = temp_p;
		temp_p = temp_p->parent;
	}

	return temp_p;
}

void left_Rotate(struct rbtree* tree, struct node* x) {
	// x�� right child
	struct node* y = x->right;

	// y�� left child�� x�� right�� ����
	x->right = y->left;

	// x�� right child�� parent ����
	if (x->right != NULL) {
		x->right->parent = x;
	}

	// y�� parent ����
	y->parent = x->parent;

	// x�� �θ� ��尡 NULL�̸�, y�� root
	if (x->parent == NULL) {
		tree->root = y;
	}

	// x�� left child�̸�
	else if (x == x->parent->left) {
		// x�� �θ����� left�� y�� ����
		x->parent->left = y;
	}
	else {
		// x�� �θ����� right�� y�� ����
		x->parent->right = y;
	}

	// y�� left�� x��
	y->left = x;
	// x�� parent�� y��
	x->parent = y;
}

void right_Rotate(struct rbtree* tree, struct node* x) {

	// x�� left child
	struct node* y = x->left;

	// y�� right child�� x�� left�� ����
	x->left = y->right;

	// x�� right�� �Ⱥ������, right child�� parent ����
	if (x->right != NULL) {
		x->right->parent = x;
	}

	// y�� parent ����
	y->parent = x->parent;

	// x�� �θ� ��尡 NULL�̸�, y�� root
	if (x->parent == NULL) {
		tree->root = y;
	}

	// x�� right child�̸�
	else if (x == x->parent->right) {
		// x�� �θ����� right�� y�� ����
		x->parent->right = y;
	}
	else {
		// x�� �θ����� left�� y�� ����
		x->parent->left = y;
	}

	// y�� left�� x��
	y->right = x;
	// x�� parent�� y��
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
	// new_node�� root�� �ƴϸ鼭 RED�� ���� �ݺ� 
	while (new_node->parent != NULL && new_node->parent->color == RED) {
		if (new_node->parent == new_node->parent->parent->left) {
			y = new_node->parent->parent->right;

			// �θ�, ���� RED
			if (y != NULL && y->color == RED) {
				new_node->parent->color = BLACK;
				y->color = BLACK;
				new_node->parent->parent->color = RED;
				new_node = new_node->parent->parent;
			}
			// �θ� RED, ���� BLACK
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

			// �θ�, ���� RED
			if (y != NULL && y->color == RED) {
				new_node->parent->color = BLACK;
				y->color = BLACK;
				new_node->parent->parent->color = RED;
				new_node = new_node->parent->parent;
			}
			// �θ� RED, ���� BLACK
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
	// �Ϸ� ��, root�� ���� black����
	tree->root->color = BLACK;
}

void RB_insert(struct rbtree* tree, int k) {
	// NIL�� root node
	struct node* y = tree->NIL;
	struct node* temp = tree->root;

	// ���ο� ��� ����
	struct node* new_node = newNode(k);

	// root�� null�̸�, ���ο� ��带 root��
	if (tree->root == tree->NIL) {
		new_node->color = BLACK;
		tree->root = new_node;
	}
	else {
		// BST Ʈ���� ���� ������� ��� ����
		while (temp != NULL) {
			y = temp;
			// ���� ���ο� ����� key�� x���� ũ��
			if (k > temp->key) {
				// ���������� �̵�
				temp = temp->right;
			}
			else {
				// �ƴϸ�, ����
				temp = temp->left;
			}
		}

		// ���ο� ��带 y �Ʒ��� ����
		new_node->parent = y;

		// ���ο� ����� Ű ���� ����, �� or �� ����
		if (k > y->key) {
			y->right = new_node;
		}
		else {
			y->left = new_node;
		}

		// Fixup ����
		RB_insert_fixup(tree, new_node);

	}
}

void tree_transplant(struct rbtree* tree, struct node* n_1, struct node* n_2) {
	// tree�� Ư�� ����
	// n_1�� parent ������, n_2�� root�� ����
	if (n_1->parent == NULL) {
		tree->root = n_2;
	}
	// n_1�� left child �̸�, n_1�� left child�� n_2�� ����
	else if (n_1 == n_1->parent->left) {
		n_1->parent->left = n_2;
	}
	// n_1�� right child �̸�, n_1�� right child�� n_2�� ����
	else {
		n_1->parent->right = n_2;
	}

	// n_2�� ������
	if (n_2 != NULL) {
		// n_2�� parent�� n_1�� parent�� ����
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
	// ������ ���
	struct node* delete_node = RB_find(tree, k);
	// �� ��带 ����Ű�� �ӽ� ���
	struct node* y = delete_node;
	// �� ����� ���� ��ġ �� �� ���
	struct node* temp;
	enum Color temp_col = delete_node->color;

	// ������ ����� ������ ���ٸ�,
	if (delete_node->left == NULL) {
		temp = node_nil(delete_node->right);
		tree_transplant(tree, delete_node, temp);
		free(delete_node);
	}
	// ������ ����� �������� ���ٸ�,
	else if (delete_node->right == NULL) {
		temp = node_nil(delete_node->left);
		tree_transplant(tree, delete_node, temp);
		free(delete_node);
	}

	// ������ ����� ���� child�� �� ������ ���
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
		printf("%s\n", "��");
	}
	else {
		printf("%s\n", "��");
	}

	if (prev) {
		prev->str = prev_str;
	}
	trunk_temp->str = "   |";
	Print_BST(n->left, trunk_temp, false);
}

int main() {
	// RB tree ����
	struct rbtree* tree = newRBtree();

	srand(time(NULL));
	int rand_int;
	// identical value ������ ���� üũ�� ����Ʈ
	int* A = (int*)malloc(15 * sizeof(int));

	// Q1. 15���� ���� ���ڿ� ��� ����
	printf("Q1. Add 15 random values to red-black tree\n=================================\n");
	for (int i = 0; i < 15; i++) {
		do {
			rand_int = rand() % 50;
			//rand_int = i;
		} while (checkList(A, rand_int));
		A[i] = rand_int;
		// A[i]�� ���� ����
		// key�� RB tree�� ����
		RB_insert(tree, rand_int);
	}
	// RB tree ���
	Print_BST(tree->root, NULL, false);

	// Q2. 5���� ���� ����
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

	// Q3. ����� �̿� ã��
	printf("\n\nQ3. Find nearest neighbor\n=================================\n");
	Print_BST(tree->root, NULL, false);
	printf("%d�� ���� ����� �̿�: %d\n", 5, nearest_neighbor(tree, 5));
	printf("%d�� ���� ����� �̿�: %d\n", 23, nearest_neighbor(tree, 23));
	printf("%d�� ���� ����� �̿�: %d\n", 38, nearest_neighbor(tree, 38));

	// Q4. 5���� ���� ����
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

	// �޸� �ݳ�
	delete_rbtree(tree);
}