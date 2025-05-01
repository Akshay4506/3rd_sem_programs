#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 100

struct HashNode {
    char *key;
    int value;
    struct HashNode *next;
};

struct HashTable {
    struct HashNode *table[TABLE_SIZE];
};

// Hash function
int hash(const char *key) {
    unsigned long hash = 0;
    while (*key) {
        hash = (hash * 31 + *key) % TABLE_SIZE;
        key++;
    }
    return hash % TABLE_SIZE;
}

// Function to create a new hash node
struct HashNode *createHashNode(const char *key, int value) {
    struct HashNode *node = (struct HashNode *)malloc(sizeof(struct HashNode));
    node->key = strdup(key);
    node->value = value;
    node->next = NULL;
    return node;
}

// Function to initialize the hash table
void initHashTable(struct HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

// Function to validate an IP address
int isValidIPAddress(const char *ip) {
    int num, dots = 0;
    const char *ptr = ip;

    if (!ip || *ip == '\0') return 0;

    while (*ptr) {
        char temp[4] = {0};
        int i = 0;
        while (*ptr && *ptr != '.' && i < 3) {
            if (!isdigit(*ptr)) return 0;
            temp[i++] = *ptr++;
        }

        if (i == 0 || i > 3) return 0; // Empty segment or too long
        num = atoi(temp);
        if (num < 0 || num > 255) return 0;

        dots++;
        if (*ptr) ptr++; // Skip the dot
    }
    return dots == 4;
}

// Function to insert a key-value pair into the hash table
void insertHashTable(struct HashTable *ht, const char *key, int value) {
    if (!isValidIPAddress(key)) {
        printf("Error: Invalid IP address format. Insertion failed.\n");
        return;
    }

    if (searchHashTable(ht, key) != -1) { // Check if the key already exists
        printf("'%s' is already entered.\n", key);
        return;
    }

    int index = hash(key);
    struct HashNode *newNode = createHashNode(key, value);
    newNode->next = ht->table[index];
    ht->table[index] = newNode;

    printf("'%s' inserted successfully with value %d.\n", key, value);
}

// Function to search for a key in the hash table
int searchHashTable(struct HashTable *ht, const char *key) {
    int index = hash(key);
    struct HashNode *temp = ht->table[index];
    while (temp) {
        if (strcmp(temp->key, key) == 0) {
            return temp->value;
        }
        temp = temp->next;
    }
    return -1; // Key not found
}

// Function to delete a key from the hash table
void deleteHashTable(struct HashTable *ht, const char *key) {
    int index = hash(key);
    struct HashNode *temp = ht->table[index];
    struct HashNode *prev = NULL;

    while (temp) {
        if (strcmp(temp->key, key) == 0) {
            if (prev == NULL) {
                ht->table[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp->key);
            free(temp);
            printf("Deleted key '%s'\n", key);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Error: Key '%s' not found. Deletion failed.\n", key);
}

// Function to display the hash table
void displayHashTable(struct HashTable *ht) {
    printf("\nHash Table Contents:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct HashNode *temp = ht->table[i];
        if (temp) {
            printf("Index %d: ", i);
            while (temp) {
                printf("(%s, %d) -> ", temp->key, temp->value);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
    printf("\n");
}

// Function to cleanup the hash table
void cleanupHashTable(struct HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct HashNode *temp = ht->table[i];
        while (temp) {
            struct HashNode *toFree = temp;
            temp = temp->next;
            free(toFree->key);
            free(toFree);
        }
        ht->table[i] = NULL;
    }
}

// Main function to demonstrate hash table operations with user input
int main() {
    struct HashTable ht;
    initHashTable(&ht);
    char key[100];
    int value, choice;

    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Search\n4. Display\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%s", key);
                printf("Enter value: ");
                scanf("%d", &value);
                insertHashTable(&ht, key, value);
                break;
            case 2:
                printf("Enter key to delete: ");
                scanf("%s", key);
                deleteHashTable(&ht, key);
                break;
            case 3:
                printf("Enter key to search: ");
                scanf("%s", key);
                value = searchHashTable(&ht, key);
                if (value != -1) {
                    printf("Key '%s' found with value %d\n", key, value);
                } else {
                    printf("Key '%s' not found\n", key);
                }
                break;
            case 4:
                displayHashTable(&ht);
                break;
            case 5:
                cleanupHashTable(&ht);
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

