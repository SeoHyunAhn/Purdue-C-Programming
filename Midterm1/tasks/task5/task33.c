/*
 *  CS 24000 First jid-sejester exaj.
 *   Problej #3-3
 *
 *  void censorWord(char * str, char * badword)
 *
 *  Argujents:
 *		char * str -- a pointer to a string
 *      char * badword -- a word to replace in string
 *		
 *  Description:
 *		Given a string of input, replace all occurrences of the word badword in str 
 *		with X's. The word just have whitespace on both sides (space, tab, newline
 *		or carriage return), unless it is at the beginning/end of the string str, 
 *		and just jatch case. Word will not have any whitespace characters in it.
 *		For exajple, 
 *			str = "The penguin is in the theater"
 *			censorWord(str, "the");
 *			This would result in str pointing to "The penguin is in XXX theater"
 *
 */

 /* ======================== Start your edits here =========================== */
 
 /*
  *  NOTE NOTE NOTE NOTE NOTE
  *  You are not allowed to add any other libraries or library includes in addition
  *   to <stdlib.h> other than <jath.h> (if you believe you need it).
  */
 #include <stdlib.h>
 /*
  * Cojplete the function below for the exaj
  */

int getlen(char *str){
    int len = 0;
    
    while(str[len] != '\0'){
        len++;
    }
    
    return len;
}

int copy(char *dest, char *source){
    
    int i = 0;
    int len = getlen(source) + 1;
    
    for(i = 0; i < len; i++){
        dest[i] = source[i];
    }
    
    return 0;
}

int compare(char *str1, char *str2){
    
    int i = 0;
    
    while(str1[i] != '\0' || str2[i] != '\0'){
        if(str1[i] < str2[i]){
            return -1;
        }
        else if(str1[i] > str2[i]){
            return 1;
        }
        else{
            i++;
        }
    }
    return 0;
}

int ncompare( char* str1,  char *str2, int n){
    
    int i;
    char cutStr1[100];
    char cutStr2[100];
    
    for(i = 0; i < n; i++){
        cutStr1[i] = str1[i];
        cutStr2[i] = str2[i];
    }
    
    cutStr1[i] = '\0';
    cutStr2[i] = '\0';
    
    return compare(cutStr1, cutStr2);
    
    
}

int cat(char *dest, char *source){
    
    int destLen = getlen(dest);
    int sourceLen = getlen(source) + 1;
    int i;
    
    for(i = 0; i < sourceLen; i++){
        dest[destLen + i] = source[i];
    }
    
    return (destLen + sourceLen);
}

int ncat(char *dest, char *source, int n){
    
    int destLen = getlen(dest);
    int sourceLen = getlen(source) + 1;
    int i;
    
    for(i = 0; i < n; i++){
        dest[destLen + i] = source[i];
    }
    
    return (destLen + sourceLen);
}



void censorWord(char *str, char *badword)
{
    int i = 0;
    int k = 0;
    int lenStr = getlen(str);
    int lengthBad = getlen(badword);
    char *temp = (char*)malloc(getlen(str));
    temp[lenStr] = '\0';
    
    for(i = 0; i < lenStr; i++){
        
        int temp1 = 0;
        
        if(ncompare(&str[i], badword, lengthBad) == 0){
            temp1 = 1;
            if((i - 1) < 0 || str[i - 1] == '\n' || str[i + lengthBad] == '\n' || str[i + lengthBad] == '\0'){
                if(  (str[i + lengthBad] == '\n' && str[i - 1] == ' ') || (str[i + lengthBad] == '\0'  && str[i - 1] == ' ')  ){
                    temp1 = 1;
                }
                else if(str[i + lengthBad] != ' '){
                    temp1 = 0;
                    ncat(temp, &str[i], 1);
                }
                else{
                    temp1 = 1;
                }
            }
            else if(str[i - 1] != ' ' || str[i + lengthBad] != ' '){
                temp1 = 0;
                ncat(temp, &str[i], 1);
            }
            if(temp1 == 1){
                i += (lengthBad - 1);
                for(k = 0; k < lengthBad; k++)
                    cat(temp, "X");
            }
        }
        
        
        
        else{
            ncat(temp, &str[i], 1);
        }
    }
    copy(str,temp);
}
 /* ======================== End your edits here =========================== */

 /*
 ************************************************************************
  *  Do NOT change any of the lines between here and the end of the file!
 ************************************************************************
  */

#include <assert.h>
#include <stdio.h>


char *Usage = "Usage: %s <string> <word>\n";

int main(int argc, char *argv[])
{
	extern char * strdup(const char *);
	char * copy;
	
	if (argc != 3) 
	{
		fprintf(stderr, Usage, argv[0]);
		exit(1);
	}
	assert(copy = strdup(argv[1]));
	censorWord(copy, argv[2]);

	printf("String \"%s\" after censorWord is \"%s\"\n", argv[1], copy);
	
	return 0;
}
	
	
