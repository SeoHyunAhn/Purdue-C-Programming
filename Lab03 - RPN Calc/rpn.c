/*
 Reads the file in “fileName” and separates the file into words and evaluates it.
 The functions you will implement in rpncalc are: +, -, *, /,  sin, cos, pow, log, exp. The log operator is the natural logarithm.
 */
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "rpn.h"
#include "nextword.h"
#include "stack.h"

double rpn_eval(char * fileName, double x) {
    double answer;
    
    FILE*fp = fopen(fileName, "r");
    
    char * word;
    double a, b, c;
    int count=0,opp=0;
    while ((word = nextword(fp)) != NULL) {
        if (strcmp(word, "+") == 0) {
            a=stack_pop();
            b=stack_pop();
            c=a+b;
            stack_push(c);
            opp++;
        }
        else if (strcmp(word, "-") == 0 && (strlen(word) == 1)) {
            a=stack_pop();
            b = stack_pop();
            c=b-a;
            stack_push(c);
            opp++;
        }
        else if (strcmp(word, "*") == 0) {
            a=stack_pop();
            b=stack_pop();
            c=a*b;
            stack_push(c);
            opp++;
        }
        else if (strcmp(word, "/") == 0) {
            a=stack_pop();
            b = stack_pop();
            c=b/a;
            stack_push(c);
            opp++;
        }
        else if (strcmp(word, "sin") == 0) {
            a=stack_pop();
            c=sin(a);
            stack_push(c);
            opp++;
        }
        else if (strcmp(word, "cos") == 0) {
            a=stack_pop();
            c=cos(a);
            stack_push(c);
            opp++;
        }
        else if (strcmp(word, "pow") == 0) {
            a = stack_pop();
            b = stack_pop();
            c = pow(b, a);
            stack_push(c);
            opp++;
        }
        else if (strcmp(word, "log") == 0) {
            a = stack_pop();
            c = log(a);
            stack_push(c);
            opp++;
        }
        else if (strcmp(word, "exp") == 0) {
            a = stack_pop();
            c = exp(a);
            stack_push(c);
            opp++;
        }
    
        else if ((strcmp(word, "x") == 0) && strlen(word) == 1) {
            stack_push(x);
            count++;
        }
        else {
            double p = atof(word);
            stack_push(p);
            count++;
        }
        
}
    
    if(opp!=0){
        return stack_pop();
    }
    else if (stack_pop()>0) {
        printf("Elements remain in the stack\n");
        exit(0);
    }
}
