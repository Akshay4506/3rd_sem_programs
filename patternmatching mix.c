#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int fail[50] = {-1};

void endindices(char str[100], char pat[100]) {
    int start = 0;
    int i = 0, j = 0;
    int lasts = strlen(str) - 1;
    int lastp = strlen(pat) - 1;
    int endmatch = lastp;
    for (i = 0; endmatch <= lasts; endmatch++, start++) {
        if (str[endmatch] == pat[lastp]) {
            for (j = 0, i = start; j <= lastp && str[i] == pat[j]; i++, j++) {
                if (j == lastp) {
                    printf("Pattern found at index: %d\n", start);
                }
            }
        }
    }
}

void pitable(char pat[50]) {
    int i = 0;
    int n = strlen(pat);
    for (int j = 1; j < n; j++) {
        i = fail[j - 1];
        while (pat[i] != pat[j + 1] && i >= 0) {
            i = fail[i];
        }
        if (pat[i] == pat[j + 1]) {
            fail[j] = i + 1;
        } else {
            fail[j] = -1;
        }
    }
}

void kmp(char str[100], char pat[50]) {
    int i = 0, j = 0;
    int lasts = strlen(str);
    int lastp = strlen(pat);
    pitable(pat);
    int found = 0;
    while (i < lasts && j < lastp) {
        if (str[i] == pat[j]) {
            i++; j++;
            if (j == lastp) {
                found = 1;
                printf("Pattern found at %d\n", i - j);
                j = 0;
            }
        } else if (j == 0) {
            i++;
        } else {
            j = fail[j - 1] + 1;
        }
    }
    if (!found) {
        printf("Pattern not found!\n");
    }
}

int main() {
    char str[100], pat[100];
    int choice;

    printf("Enter the main string: ");
    scanf("%s", str);
    printf("Enter the pattern: ");
    scanf("%s", pat);

    while(1){
    	printf("Choose the algorithm:\n");
        printf("1. Simple pattern matching\n");
        printf("2. KMP algorithm\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                endindices(str, pat);
                break;
            case 2:
                kmp(str, pat);
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
	}
    return 0;
}
