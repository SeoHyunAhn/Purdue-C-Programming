/*
 A stack is a basic data structure that has the functions push(x) and x=pop(). push(x) pushes an element to the top of the stack.
 A stack can be implemented with an array and a variable called top that keeps track of the top element in the stack.
 */
#include <stdio.h>
#include "stack.h"
#include <stdlib.h>

int top=0;
double stack[MAXSTACK];

void stack_clear()
{
    top = 0;
}

double stack_pop()
{
    if (top ==0) {
        printf("Stack underflow\n");
        exit(0);
    }
    double temp = stack[top];
    stack[top] = stack[top+1];
    top--;
    
    return temp;
}

void stack_push(double val)
{
    top++;
    stack[top] = val;
}

void stack_print()
{
    printf("Stack:\n");
    if (top == 0)
        printf("Stack is empty");
    else{
        int i = 1;
        int j = 0;
        for (i; i <= top; i++)  {
            printf("%d: %06f\n", j, stack[i]);
            j++;
        }
    }
}

int stack_top()
{
    return top;
}

int stack_max()
{
    return MAXSTACK;
}

int stack_is_empty()
{
    return top == 0;
}


