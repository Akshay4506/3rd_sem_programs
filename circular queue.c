#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int n;
}element;

int front=0, rear=0, capacity;
element *queue;
void copy(element* start, element* end, element* newQueue){
    element* i;
    element* j;
    i=newQueue;
    for(j=start; j<end; j++, i++){
        *i=*j;
    }
}
void queueFull(){
    element* newQueue;
    newQueue=(element*)malloc(2*capacity*sizeof(element));
    int start=(front+1)%capacity;
    if(start < 2){
        copy(queue+start, queue+start+capacity-1, newQueue);
    } 
    else{
        copy(queue+start, queue+capacity , newQueue);
        copy(queue, queue+rear+1, newQueue+capacity-start);
    }
    front=2*capacity-1;
    rear=capacity-1;
    capacity*=2;
    free(queue);
    queue=newQueue;
}
void addq(element item){
    rear=(rear+1)%capacity;
    if(front==rear){
        queueFull();
    }
    queue[rear]=item;
}
element deleteq(){
    element item;
    if(front==rear){
        item.n=-1;
        return item;
    }
    front=(front+1)%capacity;
    return queue[front];
}
void displayq(){
    int i;
    if(front==rear){
        printf("Queue Empty\n");
        return;
    }
    for(i=(front+1)%capacity; i!=rear; i=(i+1)%capacity){
        printf("%d\t",queue[i].n);
    }
    printf("%d", queue[i].n);
    printf("\n");
}
int main(){
    int choice;
    element item;
    printf("Enter intial size: ");
    scanf("%d",&capacity);
    queue=(element*)malloc(capacity*sizeof(element));
    if(capacity<=0){
        printf("Invalid Size");
        exit(0);
    }
    while(1){
        printf("\n1. Add\n2. Delete\n3. Display\n4.Exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter item to add: ");
                scanf("%d",&item.n);
                addq(item);
                break;
            case 2:
                if(item.n==-1){
                    printf("queue is empty\n");
                }
                else{
                    printf("Item deleted :%d\n",deleteq());
                }
                break;
            case 3:
                displayq();
                break;
            case 4:
            	exit(0);
        }
    }
}

