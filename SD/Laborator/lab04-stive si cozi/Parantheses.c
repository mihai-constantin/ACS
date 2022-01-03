#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char Item;
#include "stack.h"

int isBalanced2(char s[100])
{
    int ND, NI, i, balanced = 1;

    TStack stack = InitStack();

    ND = NI = 0;

    for(i = 0; i < strlen(s); i++)
    {
        stack = Push(stack, s[i]);

        if(s[i] == '(')
            ND++;
        else
            NI++;

        if(NI > ND)
        {
            balanced = 0;
            return balanced;
        }
    }

    if(ND != NI)
      balanced = 0;

    return balanced;
}

int isBalanced(char s[100])
{
    TStack stack = InitStack();

    for(int i = 0; i < strlen(s); i++)
    {
    	if(s[i] == '(')
        	stack = Push(stack, s[i]);
        else
        {
        	if(IsEmptyStack(stack) == 1)
        		return 0;

        	stack = Pop(stack, &s[i]);
        }
    }

    if(IsEmptyStack(stack) == 1)
    	return 1;

    return 0;
}

int main()
{
    char s1[100]="((()))()", s2[100]="((())(";

    if(isBalanced(s1))
      printf("Balanced | ");
    else
      printf("Not balanced | ");

    if(isBalanced(s2))
      printf("Balanced | ");
    else
      printf("Not balanced | ");
    printf("\n");
    return 0;
}
