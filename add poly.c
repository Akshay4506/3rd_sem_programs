#include <stdio.h>

typedef struct {
    int coeff;
    int exp;
} term;

term t1[100];
int avail = 0;

int compare(int x, int y) {
    if (x > y)
        return 1;
    else if (x < y)
        return -1;
    return 0;
}

void attach(int c, int e) {
    t1[avail].coeff = c;
    t1[avail].exp = e;
    avail++;
}

void add(int startA, int finishA, int startB, int finishB) {
    while (startA <= finishA && startB <= finishB) {
        switch (compare(t1[startA].exp, t1[startB].exp)) {
            case -1:
                attach(t1[startB].coeff, t1[startB].exp);
                startB++;
                break;
            case 1:
                attach(t1[startA].coeff, t1[startA].exp);
                startA++;
                break;
            case 0:
                attach(t1[startA].coeff + t1[startB].coeff, t1[startA].exp);
                startA++;
                startB++;
                break;
        }
    }
    while (startA <= finishA) {
        attach(t1[startA].coeff, t1[startA].exp);
        startA++;
    }
    while (startB <= finishB) {
        attach(t1[startB].coeff, t1[startB].exp);
        startB++;
    }
}

void display(int start, int end) {
    for (int i = start; i <= end; i++) {
        printf("%dx^%d", t1[i].coeff, t1[i].exp);
        if (i != end)
            printf(" + ");
    }
    printf("\n");
}

int main() {
    int m, n, c, e;
    int startA, startB, finishA, finishB, startC, finishC;

    printf("Enter the number of terms for the first polynomial: ");
    scanf("%d", &m);
    startA = 0;

    printf("Enter coefficient & exponent for the first polynomial:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &c, &e);
        attach(c, e);
    }
    finishA = avail - 1;

    printf("Enter the number of terms for the second polynomial: ");
    scanf("%d", &n);
    startB = avail;

    printf("Enter coefficient & exponent for the second polynomial:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &c, &e);
        attach(c, e);
    }
    finishB = avail - 1;

    startC = avail;
    add(startA, finishA, startB, finishB);
    finishC = avail - 1;

    printf("First polynomial:\n");
    display(startA, finishA);
    printf("Second polynomial:\n");
    display(startB, finishB);
    printf("Polynomial after addition:\n");
    display(startC, finishC);

    return 0;
}
