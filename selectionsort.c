#include<stdio.h>
int main(){
	int a[10];
	int n=5;
	int k;
	for(k=0;k<n;k++){
		scanf("%d",&a[k]);
	}
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
	return 0;
}
