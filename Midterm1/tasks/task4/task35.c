/*
 *  CS 24000 First mid-semester exam.
 *   Problem #22
 *
 *  int isPalindrome(char * str)
 *
 *  Arguments:
 *		char * str -- a pointer to a string
 *
 *  Return:
 *		1 if the string is a palindrome, 0 otherwise
 *		
 *  Description:
 *		Given a string of input, return 1 if str is a palindrome, 0 otherwise. A 
 * 		palindrome is a word, phrase, or sequence that reads the same backward as
 *		forward. The function ignores all white spaces (space, tab, newline or 
 * 		carriage return). For example, "madam" and "nurses run" are palindromes.
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
int getlen(char *str){
    int len = 0;
    
    while(str[len] != '\0'){
        len++;
    }
    
    return len;
}

int sp(char *str1, char *str2){

	int i = 0;

	while(str1[i] != '\0' && str2[i] != '\0'){
		
		if(str1[i] < str2[i]){
			return -1;
		}
		else if(str1[i] > str2[i]){
			return 1;
		}
		else
            i++;

	}
	return 0;

}


int isPalindrome(char * str)
 {
	/*char* src[]=str;*/
	int n=getlen(str)-1;
	int i=0, j=n;
	int a=1;
    
     if(n<=0)
         return 1;
     while (i<=((n+1)/2)) {
         if(i==j)
             break;
         if (str[i]!=' '&&str[i]!='\n'&&str[i]!='\t'&&str[i]!='\r') {
             if (str[j]==' '||str[j]=='\n'||str[j]=='\t'||str[j]=='\r') {
                 j--;
                 continue;
             }
         if (str[i]!=str[j]) {
             a=0;
             break;
         }
         i++;
         j--;
     }
         else{
             if (str[j]==' '||str[j]=='\n'||str[j]=='\t'||str[j]=='\r'){
                 j--;
             }
             i++;
             continue;
         }
     }
     return a;
 }

/*
 
 나누기 2가 안되는 이유는 
 빈칸을 다 지우고 돌려보낼때 지워진채로 나가기 때문에 
 안됩니다
 for(;i<n;i++){
 if(str[i]!=' '|| str[i]!='\t'||str[i]!='\r'||str[i]!='\n'||str[i]!='\0'){
 src[a]=str[i];
 a++;
 }
	}
 src[a]='\0';
	int b=getlen(src);
	if(n==1) return 1;
 
	for(i=0; i<(b/2); i++){
 if(src[i]!=src[b-i-1])
 return 0;
	}
 return 1;
 }
 }*/

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
	
	result = isPalindrome(argv[1]);

	printf("%s %s a palindrome\n", argv[1], (result == 1) ? "is" : "is not");
	
	return 0;
}
