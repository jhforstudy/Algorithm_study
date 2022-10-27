#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct __list {
    struct __node* head;
    struct __node* tail;
} linkedList;

typedef struct __node {
    int data;
    struct __node* prev;
    struct __node* next;
} node;

void printNodes(linkedList* lst) {
    node* p = lst->head;
    //putchar('[');
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    // putchar(']');
    printf("NULL\n\n");

}

// Check if number is repeated
bool checkElements(linkedList* lst, int input) {
    node* p = lst->head;
    while (p != NULL) {
        if (p->data == input) {
            return true;
        }
        p = p->next;
    }
    p = lst->head;
    return false;
}

// Add new node to tail of linked list
void insert(linkedList* lst, int x) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = x;
    newNode->prev = NULL;
    newNode->next = NULL;
    if (lst->head == NULL && lst->tail == NULL)
        lst->head = lst->tail = newNode;
    else {
        newNode->prev = lst->tail;
        lst->tail->next = newNode;
        lst->tail = newNode;
    }
}

void delete(linkedList* lst) {
    node* temp = lst->head;

    int first, second, third;
    first = second = third = INT_MIN;

    node* first_node = lst->head;
    node* second_node = lst->head;
    node* third_node = lst->head;

    while (temp != NULL) {
        if (temp->data > first) {
            first = temp->data;
            first_node = temp;
        }
        else if (temp->data > second && temp->data != first) {
            second = temp->data;
            second_node = temp;
        }
        else if (temp->data > third && temp->data != second) {
            third = temp->data;
            third_node = temp;
        }

        // move to next node
        temp = temp->next;
    }
    // Delete third_node
    // Change Ptr pointing third_node to Ptr pointing third_node->next
    printf("Delete the third largest number %d from linked list.\n\n", third);
    third_node->prev->next = third_node->next;
}

void print(linkedList* lst) {
    int first, second, third;
    node* temp = lst->head;
    
    first = second = third = INT_MIN;

    while (temp != NULL) {
        if (temp->data > first) {
            first = temp->data;
        }
        else if (temp->data > second && temp->data != first) {
            second = temp->data;
        }
        else if (temp->data > third && temp->data != second) {
            third = temp->data;
        }

        // move to next node
        temp = temp->next;
    }

    printf("first : %d\n", first);
    printf("second : %d\n", second);
    printf("third : %d\n\n", third);
}

int main() {
    //linkedList pointer define start
    linkedList* L = (linkedList*)malloc(sizeof(linkedList));
    L->head = NULL;
    L->tail = NULL;

    int rand_int;
    srand(time(NULL));

    for (int i = 0; i < 60; i++) {
        do {
            rand_int = rand() % 1000;
        } while (checkElements(L, rand_int));

        insert(L, rand_int);
    }
    printNodes(L);
    // 1st
    delete(L);

    //printNodes(L);
    print(L);

    //2nd
    delete(L);

    //printNodes(L);
    print(L);

    //3rd
    delete(L);

    //printNodes(L);
    print(L);

}