 #include<stdio.h>
#include<string.h>

void end_indices(char text[100],char pattern[100]){
	int strLen = strlen(text);
    int patLen = strlen(pattern);
    int index = 0;
    int count=0;
    int found = 0;
    for (int i = 0; i <= strLen - patLen; i++) { 
        count = 2; 
        if (pattern[0] == text[i] && pattern[patLen - 1] == text[i + patLen - 1]) {
            int pos = i + 1; 
            index = i; 
            for (int j = 1; j < patLen - 1; j++) {
                if (pattern[j] == text[pos]) {
                    count++;
                    pos++;
                    if (count == (patLen)) { 
                        printf("Pattern found at index %d\n",index);
                        found = 1;
                    }
                }
            }
        } 
    }

    if (!found) {
        printf("Pattern not found!!!\n");
    }
}

void kmpalgo(char text[100],char pattern[100]){
	int pi[100]={0};

    void pitable(char p[]){
	    int n=strlen(p);
	    int j=0;
	    for(int i=1;i<n;i++){
		    while(j>0 && p[i]!=p[j]){
			    j=pi[j-1];
		    }
		    if(p[i]==p[j]){
		     	j++;
		    }
		    pi[i]=j;
	    }
    }
    
	int n=strlen(text);
    int m=strlen(pattern);
    int i=0,j=0;
    pitable(pattern);
    int found=0;
    while(i<n){
    	if(text[i]==pattern[j]){
	   		i++;
	   		j++;
	   	}
    	if(j==m){
    		found=1;
     		printf("Pattern found at index :%d\n",i-j);
    		j=pi[j-1];
    	}
    	else if(i<n && text[i]!=pattern[j]){
    		if(j!=0){
     			j=pi[j-1];
      		}
     		else{
     			i++;
	     	}
    	}
   	}
   	if(!found){
    	printf("Pattern not found!!!");
   	}
}

int main(){
	char text[100],pattern[100];
	printf("Enter the main string :");
	scanf("%s",text);
	printf("Enter the pattern to be found :");
	scanf("%s",pattern);
	int option;
	printf("\nOptions :\n");
	printf("1.Pattern Matching through End Indices\n");
	printf("2.Pattern Matching through KMP Algorithm\n");
	printf("Enter any of the options above :");
	scanf("%d",&option);
	printf("\n");
	
	switch(option){
		case 1:
			end_indices(text,pattern);
			break;
		case 2:
			kmpalgo(text,pattern);
			break;
		default:
			printf("INVALID OPTION!!!");
	}
return 0;
}
