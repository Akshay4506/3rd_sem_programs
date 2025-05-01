#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int fail[50]={-1};
void pitable(char pat[50]){
    int i=0;
    int n=strlen(pat);
    for(int j=1;j<n;j++){
        i=fail[j-1];
        while(pat[i]!=pat[j+1] && i>=0){
            i=fail[i];
        }
        if(pat[i]==pat[j+1]){
            fail[j]=i+1;
        }
        else{
            fail[j]=-1;
        }
    }
}

void kmp(char str[100],char pat[50]){
    int i=0,j=0;
    int lasts=strlen(str);
    int lastp=strlen(pat);
    pitable(pat);
    int found=0;
    while(i<lasts && j<lastp){
        if(str[i]==pat[j]){
            i++;j++;
            if(j==lastp){
                found=1;
                printf("Pattern found at %d\n",i-j);
                j=0;
            }
        }
        else if(j==0){
            i++;
        }
        else{
            j=fail[j-1]+1;
        }
    }
    if(!found){
        printf("not found!");
    }
}

int main(){
    char str[100],pat[100];
    printf("Enter the main string :");
    scanf("%s",str);
    printf("Enter the pattern :");
    scanf("%s",pat);
    kmp(str,pat);
}
