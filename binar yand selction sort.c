#include<stdio.h>
void Binarysearch(int a[1000],int low,int high,int key);
void Selectionsort(int a[1000],int n);
int main()
{
	int n;
	int a[1000];
	printf("Enter the number of elments:");
	scanf("%d",&n);
	int i;
	printf("Enter the elements :");
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	int low=0;
	int high=n-1;
	int key,mid;
	
    printf("Enter the key :");
	scanf("%d",&key);
	Selectionsort(a,n);
    Binarysearch(a,low,high,key);
	return 0;
}
void Selectionsort(int a[1000],int n){
	int i,j,min,temp;
	for(i=0;i<n;i++){
		min=i;
		for(j=i+1;j<n;j++){
			if(a[j]<a[min]){
				min=j;
			}
		}
			temp=a[min];
			a[min]=a[i];
			a[i]=temp;
	}
	for(i=0;i<n;i++){
		printf("%d\t",a[i]);
	}
	printf("\n");
}
void Binarysearch(int a[1000],int low,int high,int key){
	while(low<=high){
		int mid=((high+low)/2);
		if(a[mid]<key){
			low=mid+1;
		}
		else if (a[mid]==key){
			printf("key found at index:%d",mid);
			break;
    	}
		else {
			high=mid-1;
		}
    }
    if(low>high){
    	printf("key not found");
	}
}
