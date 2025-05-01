#include<stdio.h>
#include<string.h>
int brute(char pat[100],char sub[100]){
	int last_p=strlen(pat)-1;
	int last_s=strlen(sub)-1;
	int p=0;
	int e=last_s;
	for(int i=0;e<=last_p;p++,e++){
		if(pat[e]==sub[last_s]){
			for(int j=0,i=p;j<last_s && pat[i]==sub[j];i++,j++){
				if(j==strlen(sub)){
					return p;
				}
			}
			return -1;
		}
	}
}
int main(){
	char pat[100],sub[100];
	printf("enter the main string :");
	scanf("%s",pat);
	printf("enter the sub string :");
	scanf("%s",sub);
	int result=brute(pat,sub);
	if(result ==-1){
		printf("pattern not matching with sub string");
	}
	else{
		printf("pattern found at index :%d",result);
	}
}
