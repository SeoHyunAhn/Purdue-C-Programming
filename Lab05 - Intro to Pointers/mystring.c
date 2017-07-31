/*
 Implement the string functions indicated using pointers
 */
#include <stdlib.h>
#include "mystring.h"

int mystrlen(char * s) {
    char * src;
    for (src=s; *src!='\0'; ++src);
    return src-s;
}

char * mystrcpy(char * dest, char * src) {
    char *str=dest;
    while((*dest++=*src++)!='\0');
    return str;
}

char * mystrcat(char * dest, char * src) {
    char * str=dest;
    while(*dest) dest++;
    while((*dest++=*src++)!='\0');
    return str;
}

int mystrcmp(char * s1, char * s2) {
    char temp1, temp2;
    while(1){
        temp1=*s1++;
        temp2=*s2++;
        if(temp1!=temp2)
            return temp1<temp2 ?-1:1;
        if(!temp1)
            break;
    }
    return 0;
}

char * mystrstr(char * hay, char * needle) {
	while(*hay!=0){
		if(!mymemcmp(hay++, needle, 10))
			return hay-1;
	}

return 0;
}

int mymemcmp(char * s1, char * s2, int n){
    char *str=s1, *str2=s2;
    while(n--)
        if(*str!=*str2)
            return !str-*str2;
        else
            str++, str2++;
    return 0;
}


char * mystrdup(char * s) {
	char *temp =malloc(mystrlen(s)+1);
	if(temp ==NULL) return NULL;
	mystrcpy(temp, s);
	return temp;
}

char * mymemcpy(char * dest, char * src, int n)
{
    char *temp=dest;
    char *s= src;
    while(n--)
        *temp++=*s++;
    
    return dest;
}


