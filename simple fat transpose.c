#include <stdio.h>
#define MAX_TERMS 100

typedef struct {
    int r;
    int c;
    int v;
} term;

term s[MAX_TERMS], t[MAX_TERMS];

void sparsemat(int a[10][10], term s[], int row, int col);
void sparsetrans(int a[10][10],term t[],int row,int col);				
void fastTranspose(term s[], term t[]);

int main() {
    int a[10][10];
    int row, col;

    printf("Enter the number of rows: ");
    scanf("%d", &row);
    printf("Enter the number of columns: ");
    scanf("%d", &col);

    printf("Enter the elements\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("Sparse matrix:\n");
    sparsemat(a, s, row, col);
    
    printf("Simple Transpose:\n");
    sparsetrans(a,t,row,col);
    
    printf("Sparse transpose using fast transpose:\n");
    fastTranspose(s, t);

    return 0;
}

void sparsemat(int a[10][10], term s[], int row, int col) {
    int k = 1;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (a[i][j] != 0) {
                s[k].r = i;
                s[k].c = j;
                s[k].v = a[i][j];
                k++;
            }
        }
    }
    s[0].r = row;
    s[0].c = col;
    s[0].v = k - 1;

    for (int c = 0; c < k; c++) {
        printf("%d\t%d\t%d\n", s[c].r, s[c].c, s[c].v);
    }
}

void sparsetrans(int a[10][10], term t[], int row, int col) {
    int k=1;
    for(int i=0;i<row; i++){
        for(int j=0;j<col; j++){
            if(a[j][i]!=0){
            	t[k].r=i;
                t[k].c=j;
				t[k].v=a[j][i];
                k++;
            }
        }
    }
       t[0].r=col;
       t[0].c=row;
       t[0].v=k-1;
       
    for (int c=0;c<k;c++){
        printf("%d\t%d\t%d\n",t[c].r,t[c].c,t[c].v); 
    }
}

void fastTranspose(term s[], term t[]) {
    int rowTerms[MAX_TERMS] = {0}, startingPos[MAX_TERMS];
    int numTerms = s[0].v, numCols = s[0].c;

    // Count the number of entries in each column
    for (int i = 1; i <= numTerms; i++) {
        rowTerms[s[i].c]++;
    }

    // Starting position for each column in t
    startingPos[0] = 1;
    for (int i = 1; i < numCols; i++) {
        startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
    }

    // Perform the fast transpose
    for (int i = 1; i <= numTerms; i++) {
        int pos = startingPos[s[i].c]++;
        t[pos].r = s[i].c;
        t[pos].c = s[i].r;
        t[pos].v = s[i].v;
    }

    t[0].r = s[0].c;
    t[0].c = s[0].r;
    t[0].v = s[0].v;

    for (int i = 0; i <= numTerms; i++) {
        printf("%d\t%d\t%d\n", t[i].r, t[i].c, t[i].v);
    }
}
