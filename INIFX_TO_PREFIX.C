#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#define max 100
char st[max], infix[100], postfix[100], temp[100];
int top=-1;
void push(char st[], char);
char pop(char st[]);
void reverse(char str[]);
void InfixToPostfix(char prefix[], char postfix[]);
int precedence(char);
int main()
{
    printf("\nEnter any infix expression: ");
    gets(infix);
    reverse(infix);
    strcpy(postfix, "");
    InfixToPostfix(temp, postfix);
    printf("\nThe corresponding postfix expression is: ");
    puts(postfix);
    strcpy(temp, "");
    reverse(postfix);
    printf("\nThe prefix expression is: \n");
    puts(temp);
    getch();
    return 0;
}

void reverse(char str[])
{
    int len, i=0, j=0;
    len=strlen(str);
    j=len-1;
    while(j>=0)
    {
        if(str[j]=='(')
            temp[i]=')';
        else if(str[j]==')')
            temp[i]='(';
        else
            temp[i]=str[j];
        i++, j--;
    }
    temp[i]='\0';
}

void InfixToPostfix(char prefix[], char postfix[])
{
    int i=0, j=0;
    strcpy(postfix, "");
    while(prefix[i]!='\0')
    {
        if(prefix[i]=='(')
        {
            push(st, prefix[i]);
            i++;
        }
        else if(prefix[i]==')')
        {
            while((top!=-1)&& (st[top]!='('))
            {
                postfix[j]=pop(st);
                j++;
            }
            if(top==-1)
            {
                printf("\nIncorrect expression");
                exit(1);
            }
            pop(st);
            i++;
        }
        else if(isdigit(prefix[i]) || isalpha(prefix[i]))
        {
            postfix[j]=prefix[i];
            j++; i++;
        }
        else if(prefix[i]=='+' || prefix[i]=='-' ||prefix[i]=='*' ||prefix[i]=='/' ||prefix[i]=='%')
        {
            while((top!=-1) && (st[top]!='(') && (precedence(st[top]) > precedence(prefix[i])))
            {
                postfix[j]=pop(st);
                j++;
            }
            push(st, prefix[i]);
            i++;
        }
        else
        {
            printf("\nIncorrect Element in expression");
            exit(1);
        }
    }
    while((top!=-1) && (st[top]!='('))
    {
        postfix[j]=pop(st);
        j++;
    }
    postfix[j]='\0';
}

int precedence(char op)
{
    if(op=='/' || op=='*'|| op=='%')
        return 1;
    else if(op=='+' || op=='-')
        return 0;
}

void push(char st[], char val)
{
    if(top==max-1)
        printf("\nStack overflow");
    else
    {
        top++;
        st[top]=val;
    }
}

char pop(char st[])
{
    char val=' ';
    if(top==-1)
        printf("\nStack Underflow");
    else
    {
        val=st[top];
        top--;
    }
    return val;
}
