#include<stdio.h>
#include<stdlib.h>
#define size 10
#define COMPARE(x,y)(((x)==(y))?0:((x)>(y))?1:2)

typedef struct{
   int n;
}element;

struct node{
    int coeff;
    int exp;
    struct node *link;
};
typedef struct node* NODE;

NODE create(NODE first,int c,int e)
{
    NODE temp;
    temp=(NODE)malloc(sizeof(struct node));
    NODE p;
    temp->coeff=c;
    temp->exp=e;
    temp->link=NULL;
    if(first==NULL)
    {
        return temp;
    }
    p=first;
    while(p->link!=NULL)
    {
        p=p->link;//not first->link
    }
    p->link=temp;
    return first;
}
void display(NODE first)
{
    if (first == NULL) {
        printf("\nNOTE: The linked list is empty.\n");
        return;
    }
    NODE temp = first;
    printf("The sum of the two polynomials is:\n");
    printf("The coeffient for:");
    while (temp != NULL) {
        printf("\nExponential power %d: %d ",temp->exp,temp->coeff);
        temp = temp->link;
    }
}
NODE attach(NODE C,int e,int c)
{
    NODE temp;
    temp=(NODE)malloc(sizeof(struct node));
    temp->exp=e;
    temp->coeff=c;
    temp->link=NULL;
    if(C==NULL)
    {
        return temp;
    }
    NODE p=C;
    while(p->link!=NULL)
    {
        p=p->link;//not first->link
    }
    p->link=temp;
    return C;
}
NODE add(NODE A,NODE B,NODE C)
{
        NODE p=A;
        NODE q=B;
        int sumOfCoeff;
        while(p!=NULL||q!=NULL)
        {
            switch(COMPARE(p->exp,q->exp))
            {
                case 0: //A==B
                    sumOfCoeff=(p->coeff)+(q->coeff);
                    C=attach(C,p->exp,sumOfCoeff);
                    if((p->link==NULL)&&(q->link==NULL))
                    {
                        return C;
                    }
                    else
                    { 
                        if(p->link!=NULL)
                            p=p->link;
                        if(q->link!=NULL)
                            q=q->link;
                    }
                    break;
                case 1: //A>B
                    C=attach(C,p->exp,p->coeff);
                    p=p->link;
                    if(p==NULL)
                        return C;
                    break;
                case 2://A<B
                    C=attach(C,q->exp,q->coeff);
                    q=q->link;
                    if(q==NULL)
                        return C;
                    break;
            }
        }
    return C;
}
int main()
{
    int item;
    int ch;
    int max=0;
    NODE A=NULL;
    NODE B=NULL;
    NODE C=NULL;//holds sum of the added polynomial
    while(1)
    {
    printf("\n\nSelect any one option:\n");
    printf("1.Enter polynomial-1.\n");
    printf("2.Enter polynomial-2.\n");
    printf("3.Add polynomials.\n");
    printf("4.Display the result.\n");
    printf("5.Exit the program.\n");
    printf("Enter choice: ");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:
        printf("Enter the details of polynomial-1: ");
        printf("\nEnter the highest exponential power of the equation: ");
        scanf("%d",&max);
        printf("Enter the coefficient for:\n");
        for(int i=0;i<=max;i++)
        {
           printf("Exponential power %d: ",i);
           scanf("%d",&item);
           A=create(A,item,i);
        }
        break;
        case 2:
       printf("Enter the details of polynomial-2: ");
        printf("\nEnter the highest exponential power of the equation: ");
        scanf("%d",&max);
        printf("Enter the coefficient for:\n");
        for(int i=0;i<=max;i++)
        {
           printf("Exponential power %d: ",i);
           scanf("%d",&item);
           B=create(B,item,i);
        }
        break;
        case 3:
        C=add(A,B,C);
        break;
        case 4:
        display(C);
        break;
        case 5:
        exit(0);
    }
    }
    return 0;
}
