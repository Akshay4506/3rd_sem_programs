#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr;
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    arr = (int *)calloc(n,sizeof(int));     //for both malloc or calloc

    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // Print the allocated values
    printf("Allocated values:\n");
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    int *brr;
    int m=n-2;
    brr = (int *)realloc(arr,m);
    
    if (brr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    
    // Print the allocated values
    printf("Allocated values:\n");
    for (int i = 0; i < m; i++) {
        printf("brr[%d] = %d\n", i, brr[i]);
    }
    
    free(brr);

    return 0;
}
