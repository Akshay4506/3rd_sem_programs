#include <stdio.h>
#include <stdlib.h>

struct tree {
    int data;
    struct tree* rlink;
    struct tree* llink;
};
typedef struct tree* treeptr;

void insert(treeptr *root, int item) {
    if (*root == NULL) {
        *root = (treeptr)malloc(sizeof(struct tree));
        (*root)->data = item;
        (*root)->rlink = NULL;
        (*root)->llink = NULL;
    } 
	else if ((*root)->data > item) {
        insert(&((*root)->llink), item);
    } 
	else if ((*root)->data < item) {
        insert(&((*root)->rlink), item);
    }
}

void inorder(treeptr root) {
    if (root) {
        inorder(root->llink);
        printf("%d\t", root->data);
        inorder(root->rlink);
    }
}

void preorder(treeptr root) {
    if (root) {
        printf("%d\t", root->data);
        preorder(root->llink);
        preorder(root->rlink);
    }
}

void postorder(treeptr root) {
    if (root) {
        postorder(root->llink);
        postorder(root->rlink);
        printf("%d\t", root->data);
    }
}

void search(treeptr root, int item) {
    if (root == NULL) {
        printf("Not found\n");
        return;
    } 
	else if (root->data == item) {
        printf("Found\n");
        return;
    } 
	else if (root->data > item) {
        search(root->llink, item);
    } 
	else {
        search(root->rlink, item);
    }
}

int main() {
    treeptr root = NULL;
    int choice, ele;
    while (1) {
        printf("\n1. Insert\n2. Inorder\n3. Preorder\n4. Postorder\n5. Search\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the element: ");
                scanf("%d", &ele);
                insert(&root, ele);  // Corrected to pass the address of root
                break;
            case 2:
                printf("Inorder traversal\n");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Preorder traversal\n");  // Corrected message
                preorder(root);
                printf("\n");
                break;
            case 4:
                printf("Postorder traversal\n");  // Corrected message
                postorder(root);
                printf("\n");
                break;
            case 5:
                printf("Enter the element: ");
                scanf("%d", &ele);
                search(root, ele);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice, try again.\n");
        }
    }
}
