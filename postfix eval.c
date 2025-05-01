// postfix evaluation
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int s[50]={0};
int top=-1;
int ch;

void push(int ele)
{
    if(top==49)
    {
        printf("stack is full\n");
    }
    else{
        top++;
        s[top]=ele;
    }
}

int pop()
{
    if(top==-1)
    {
        printf("top is empty\n");
    }
    else{
        ch=s[top];
        top--;
    }
    return ch;
}
int main()
{
    char postfix[30]={'\0'},ele;
    int i,a,b,res;
    printf("enter the postfix expression:");
    scanf("%s",postfix);

    int plen=strlen(postfix);
    i=0;

    while(i<=plen-1)
    {
        ele=postfix[i];
        if(isdigit(ele))
        {
            push(ele-'0');
        }
        else{
            a=pop();
            b=pop();
            switch(ele)
            {
                case '^':res=pow(b,a);
                break;

                case '+':res=b+a;
                break;

                case '-':res=b-a;
                break;

                case '*':res=b*a;
                break;

                case '/':res=b/a;
                break;

            }
             push(res);

        }
        i++;
    }

    printf("result is %d\n",pop());
    return 0;

}
