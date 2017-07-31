/*
 *  CS 24000 First mid-semester exam.
 *   Problem #29
 *
 *   unsigned int emptyLinesCounter(const char * str)
 *
 *  Arguments:
 *		char * str -- a pointer to a string
 *
 *  Description:
 *		Given a string of input, counts number of empty lines in str. An
 *		empty line is defined as a line that contain no character except for newline
 *		('\n') character or that may contain only white spaces (' ', '\t', '\r')
 *		and a newline character ('\n'))
 *
 */

/* ======================== Start your edits here =========================== */

/*
 *  NOTE NOTE NOTE NOTE NOTE
 *  You are not allowed to add any other libraries or library includes in addition
 *   to <stdlib.h> other than <math.h> (if you believe you need it).
 */
#include <stdlib.h>
/*
 * Complete the function below for the exam
 */

int hello(const char * str){
    int len=0;
    while(str[len]!='\0'){
        len++;
    }
    return len;
}

unsigned int emptyLinesCounter(const char * str)
{
    int i=0;
    int count=0;
    int length=hello(str);
    while(i<length){
        int temp=0;
        while(str[i]!='\n'&&i<length){
            if(str[i]!=' '||str[i]!='\t'||str[i]!='\r'||str[i]!='\n'){
                temp=1;
            }
            i++;
        }
        if(!temp){
            count++;
        }
        i++;
    }
    
    return count;
}



/*
 for(i=0; i<n; i++){
 if(str[i]=='\n')
 ncount++;
 }
 int k=0,j=0;
 i=0;
 for(; i<ncount;i++){
 for(k=0; str[i]!='\n';k++){
 last[i][k]=str[k];
 }
 }
 i=0;
 for(; i<ncount;i++){
 for(; j<n; j++){
 if(last[i][j]==' '){
 blankCount1++;
 if (blankCount1==j) {
 count++;
 }
 }
 else if(last[i][j]=='\t')
 blankCount2++;
 if (blankCount2==j) {
 count++;
 }
 }
 }
 i=0;
 for(;i<n;i++){
 if(str[i]==' '||str[i]	=='\t'||str[i]=='\r')
 count++;
 }
 
 
	c=str[i];
	for(; i<n;i++){
	if(str[i]==' '||str[i]=='\t'||str[i]=='\r')
 count++;
	else if(
	}
	return count;
 }
 */

/* ======================== End your edits here =========================== */

/*
 ************************************************************************
 *  Do NOT change any of the lines between here and the end of the file!
 ************************************************************************
 */

#include <stdio.h>
#include <assert.h>

char *Usage = "Usage: %s <string>\n";

int main(int argc, char *argv[])
{
    unsigned int result;
    
    if (argc != 2)
    {
        fprintf(stderr, Usage, argv[0]);
        exit(1);
    }
    
    result = emptyLinesCounter(argv[1]);
    printf("Empty lines: %u\n", result);
    
    return 0;
}


