#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//The words are alphanumeric and separated by non-alphanumeric characters. The function will allocate memory for the word returned, and return a pointer to it.

char * ithword(char *str, int i){

    int col=0;
    int row=0;
    char words[100][100]={'\0',};
    char * result=(char *)malloc(sizeof(char)*100);
    int k=0;
    
    while (str[k]!=NULL) {
        if ((str[k]>='A'&&str[k]<='Z')|| (str[k]>='a'&&str[k]<='z')) {
            words[col][row]=str[k];
            row++'
        }
        else{
            row=0;
            col++;
        }
    }
    
    k=0;
    while (words[i-1][k]!=NULL) {
        result[k]=words[i-1][k];
        k++;
    }
    
    result[k]='\0';
    return result;
}
