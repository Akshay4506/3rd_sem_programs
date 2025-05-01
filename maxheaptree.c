#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void insert (int a[],int n){
    int temp;
    int i=n;
    temp=a[n];
    while(i>1 && temp>a[i/2]){
        a[i]=a[i/2];
        i=i/2;
    }   
    a[i]=temp;
}

void delete(int a[],int *n){
    if(*n==0){
        printf("Heap is empty\n");
        return;
    }
    printf("Item deleted :%d\n",a[1]);
    a[1]=a[*n];
    (*n)--;
    int i=1;
    int j=2*i;
    while(j<=*n){
        if(j+1<=*n && a[j]<a[j+1]){
            j=j+1;
        }
        if(a[i]<a[j]){
            int temp=a[i];
            a[i]=a[j];
            a[j]=temp;
            i=j;
            j=2*i;
        }
        else{
            break;
        }
    }
}

int main(){
    int choice;
    int n,*a=NULL;
    while(1){
        printf("\n1.Insert\n2.Delete\n3.Display\n4.Exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter the no.of elements :");
                scanf("%d",&n);
                a=(int *)realloc(a,(n+1)*sizeof(int));
                if(a==NULL){
                    printf("Memory allocation failed\n");
                }
                printf("Enter the elements :");
                for(int i=1;i<=n;i++){
                    scanf("%d",&a[i]);
                }       
                for(int i=2;i<=n;i++){
                    insert(a,i);
                }
                break;
            case 2:
                if(n>0){
                    delete(a,&n);
                }
                else{
                    printf("Heap is empty\n");
                }
                break;
            case 3: 
                if(n==0){
                    printf("Heap is empty\n");
                }
                else{
                    printf("Heap elements :");
                    for(int i=1;i<=n;i++){
                        printf("%d\t",a[i]);
                    }
                    printf("\n");
                }
                break;
            case 4: 
                exit(0);
        }
    }
}
