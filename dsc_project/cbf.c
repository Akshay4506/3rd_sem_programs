#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BLOOM_SIZE 1000
#define HASH_COUNT 3

struct BloomFilter {
    int bitArray[BLOOM_SIZE];
};

// Hash functions
int hash1(const char *str) {
    int hash = 0;
    while (*str) {
        hash = (hash * 31 + *str) % BLOOM_SIZE;
        str++;
    }
    return hash;
}

int hash2(const char *str) {
    int hash = 0;
    while (*str) {
        hash = (hash * 17 + *str) % BLOOM_SIZE;
        str++;
    }
    return hash;
}

int hash3(const char *str) {
    int hash = 0;
    while (*str) {
        hash = (hash * 13 + *str) % BLOOM_SIZE;
        str++;
    }
    return hash;
}

// Function to initialize the Bloom filter
void initBloomFilter(struct BloomFilter *bf) {
    memset(bf->bitArray, 0, sizeof(bf->bitArray));
}

// Function to add an element to the Bloom filter
void add(struct BloomFilter *bf, const char *str) {
	if (check(bf, str)) { // Check if the string is already present
        printf("'%s' is already entered.\n", str);
        return;
    }
    int hashValues[HASH_COUNT] = {hash1(str), hash2(str), hash3(str)};
    
    // Print the hash values for the string
    printf("Hash values for '%s': hash1 = %d, hash2 = %d, hash3 = %d\n", str, hashValues[0], hashValues[1], hashValues[2]);
    
    for (int i = 0; i < HASH_COUNT; i++) {
        bf->bitArray[hashValues[i]] = 1;
    }
    printf("'%s' has been added to the Bloom filter.\n", str);
}

void removebf(struct BloomFilter *bf, const char *str) {
	if (!check(bf, str)) {
        printf("ERROR!\n'%s' is not present in the Bloom filter. Cannot delete.\n", str);
        return;
    }
    
    int hashValues[HASH_COUNT] = {hash1(str), hash2(str), hash3(str)};
    for (int i = 0; i < HASH_COUNT; i++) {
        if (bf->bitArray[hashValues[i]] > 0) {
            bf->bitArray[hashValues[i]]--;
        }
    }
    printf("Item deleted: %s\n", str);
}

// Function to check if an element is in the Bloom filter
int check(struct BloomFilter *bf, const char *str) {
    int hashValues[HASH_COUNT] = {hash1(str), hash2(str), hash3(str)};
    
    // Print the hash values for the string
    
    
    for (int i = 0; i < HASH_COUNT; i++) {
        if (bf->bitArray[hashValues[i]] == 0) {
            return 0;
        }
    }
    return 1;
}

// Function to display the Bloom filter
void displayBloomFilter(struct BloomFilter *bf) {
    printf("\nBloom Filter Bit Array:\n");
    for (int i = 0; i < BLOOM_SIZE; i++) {
        printf("%d", bf->bitArray[i]);
        if ((i + 1) % 50 == 0) { // Newline every 50 bits for readability
            printf("\n");
        }
    }
    printf("\n");
}

// Main function to demonstrate Bloom filter operations with user input
int main() {
    struct BloomFilter bf;
    initBloomFilter(&bf);
    char str[100];
    int choice;
    
    while (1) {
        printf("\n1. Add\n2. Remove\n3. Check\n4. Display Bloom Filter\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter string to add: ");
                scanf("%s", str);
                add(&bf, str);
                break;
                
            case 2:
                printf("Enter the string to delete: ");
                scanf("%s", str);
                removebf(&bf, str);
                break;
                
            case 3:
                printf("Enter string to check: ");
                scanf("%s", str);
                printf("Check '%s': %s\n", str, check(&bf, str) ? "Present" : "Not Present");
                break;
                
            case 4:
                displayBloomFilter(&bf);
                break;
                
            case 5:
                exit(0);
                
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
