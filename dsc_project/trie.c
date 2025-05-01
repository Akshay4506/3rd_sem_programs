#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 27 // Includes 'a-z' and '/'

// Convert character to index (supports lowercase letters and '/')
int charToIndex(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c == '/') return 26; // Map '/' to the last index
    return -1; // Invalid character
}

// Reverse mapping for display
char indexToChar(int index) {
    if (index >= 0 && index < 26) return 'a' + index;
    if (index == 26) return '/'; // Map last index back to '/'
    return '?'; // Invalid index
}

// Trie node structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
};

// Function to create a new trie node
struct TrieNode *createNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    node->isEndOfWord = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

int isValidPath(const char *key) {
    if (key == NULL || key[0] == '\0') {
        return 0; // Empty or NULL string is invalid
    }

    if (key[0] == '/') {
        key++; // Skip leading '/'
    } else if ((key[0] >= 'a' && key[0] <= 'z')) {
        if (key[1] == ':' && (key[2] == '\\' || key[2] == '/')) {
            key += 3; // Skip "C:\" or "C:/"
        } else {
            return 0; // Invalid drive path
        }
    } else {
        return 0; // Neither Unix nor Windows-style path
    }

    while (*key) {
        if (!((*key >= 'a' && *key <= 'z') || *key == '/')) {
            return 0; // Invalid character found
        }
        key++;
    }

    return 1; // Valid path format
}

// Function to insert a key into the trie
void insert(struct TrieNode *root, const char *key) {
    if (!isValidPath(key)) {
        printf("Error!\nInvalid path format. Insertion failed.\n");
        return;
    }

    // Check if the key already exists
    if (search(root, key)) {
        printf("%s is already entered.\n", key);
        return;
    }

    struct TrieNode *pCrawl = root;
    while (*key) {
        int index = charToIndex(*key);
        if (index == -1) {
            printf("Error!\nInvalid character '%c' in path '%s'.\n", *key, key);
            return;
        }
        if (!pCrawl->children[index]) {
            pCrawl->children[index] = createNode();
        }
        pCrawl = pCrawl->children[index];
        key++;
    }
    pCrawl->isEndOfWord = 1;
}

// Function to search for a key in the trie
int search(struct TrieNode *root, const char *key) {
    struct TrieNode *pCrawl = root;
    while (*key) {
        int index = charToIndex(*key);
        if (index == -1 || !pCrawl->children[index]) {
            return 0;
        }
        pCrawl = pCrawl->children[index];
        key++;
    }
    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

// Function to delete a key from the trie
int isEmpty(struct TrieNode *root) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            return 0;
        }
    }
    return 1;
}

struct TrieNode *deleteKey(struct TrieNode *root, const char *key, int depth) {
    if (!root) {
        return NULL;
    }

    if (*key) {
        int index = charToIndex(*key);
        root->children[index] = deleteKey(root->children[index], key + 1, depth + 1);

        if (isEmpty(root) && root->isEndOfWord == 0) {
            free(root);
            root = NULL;
        }
        return root;
    }
    if (root->isEndOfWord) {
        root->isEndOfWord = 0;
    }
    if (isEmpty(root)) {
        free(root);
        root = NULL;
    }
    return root;
}

void deleteWithFeedback(struct TrieNode *root, const char *key) {
    if (!search(root, key)) {
        printf("Error!\n'%s' is not present in the trie. Cannot delete.\n", key);
        return;
    }
    root = deleteKey(root, key, 0);
    printf("Deleted '%s'\n", key);
}

// Helper function to recursively display words in the trie
void displayTrieHelper(struct TrieNode *root, char *word, int level) {
    if (root->isEndOfWord) {
        word[level] = '\0';
        printf("%s\n", word);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            word[level] = indexToChar(i);
            displayTrieHelper(root->children[i], word, level + 1);
        }
    }
}

// Function to display all words in the trie
void displayTrie(struct TrieNode *root) {
    char word[100]; // Buffer to store words
    printf("Contents in the trie:\n");
    displayTrieHelper(root, word, 0);
}

// Main function to demonstrate trie operations with user input
int main() {
    struct TrieNode *root = createNode();
    char key[100];
    int choice;

    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Search\n4. Display Trie\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%s", key);
                insert(root, key);
                break;

            case 2:
                printf("Enter key to delete: ");
                scanf("%s", key);
                deleteWithFeedback(root, key);
                break;

            case 3:
                printf("Enter key to search: ");
                scanf("%s", key);
                printf("Search for '%s': %s\n", key, search(root, key) ? "Found" : "Not Found");
                break;

            case 4:
                displayTrie(root);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}
