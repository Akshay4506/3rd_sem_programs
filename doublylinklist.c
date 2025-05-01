#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node* prev;
    int data;
    struct node* next;
};
typedef struct node* Node;

Node addToEmpty(Node head, int data) {
    Node temp = (Node)malloc(sizeof(Node));
    temp->prev = NULL;
    temp->data = data;
    temp->next = NULL;
    head = temp;
    return head;
}

Node insert(Node head, int data) {
    if (head == NULL) {
        head = addToEmpty(head, data);
    } 
	else {
        Node temp = (Node)malloc(sizeof(Node));
        temp->prev = NULL;
        temp->data = data;
        temp->next = head;

        head->prev = temp;
        head = temp;
    }
    return head;
}

Node delete(Node head) {
    Node temp = NULL;
    temp = head;
    if (temp == NULL) {
        printf("List is empty\n");
    } 
	else {
        int val = temp->data;
        printf("Element deleted: %d\n", val);
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        free(temp);
    }
    return head;
}

void display(Node head) {
    Node ptr = NULL;
    ptr = head;

    if (ptr == NULL) {
        printf("List is empty\n");
    } 
	else {
        while (ptr != NULL) {
            printf("%d <-> ", ptr->data);
            ptr = ptr->next;
        }
        printf("NULL\n");
    }
}

int main() {
    Node head = NULL;
    int choice, data;
    
    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data: ");
                scanf("%d", &data);
                head = insert(head, data);
                break;
            case 2:
                head = delete(head);
                break;
            case 3:
                display(head);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid Choice\n");
        }
    }
}
