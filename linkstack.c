#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *link;
} Node;

Node *first = NULL;

void insert_front(int item) {
    Node *temp = (Node *)malloc(sizeof(Node));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    temp->data = item; // Example data value
    temp->link = NULL;

    if (first == NULL) {
        first = temp;
    } 
	else {
        Node *ptr = first;
        while (ptr->link != NULL) {
            ptr = ptr->link;
        }
        ptr->link = temp; // Insert the new node at the end
    }
}

void delete_end() {
    if (first == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    if (first->link == NULL) {
        free(first);
        first = NULL;
    } 
	else {
        Node *ptr = first;
        while (ptr->link->link != NULL) {
            ptr = ptr->link;
        }
        printf("Item deleted :%d\n",ptr->link->data);
        free(ptr->link); // Delete the last node
        ptr->link = NULL; // Set the second last node's link to NULL
    }
}

void display() {
    if (first == NULL) {
        printf("List is empty.\n");
        return;
    }
    Node *ptr = first;
    printf("List elements: ");
    while (ptr != NULL) {
        printf("%d -> ", ptr->data);
        ptr = ptr->link;
    }
    printf("NULL\n");
}

int main() {
    int choice;
    int ele;
    
    while (1) {
        printf("\n1.Insert\n2.Delete\n3.Display list\n4.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
			    printf("Enter the element :");
                scanf("%d",&ele);
                insert_front(ele);
                break;
            case 2:
                delete_end();
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}
