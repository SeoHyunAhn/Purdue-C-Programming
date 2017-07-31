#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//strpbrk(char *  str, char * accept) -- function locates the first occurrence in the string str of any of the characters in the string accept. Returns a pointer in str to the first occurrence. Returns null if no such character is found.

char * brk(char *  str, char * accept){
    char c, *p;
    
    for (c = *str; c != 0; str++, c = *str) {
        for (p = accept; *p != 0; p++) {
            if (c == *p) {
                return str;
            }
        }
    }
    return NULL;
}

int main(){
    char sample1[10]="a bannana";
    char sample2[10]="is good";
    
    printf("%s\n", brk(sample1, "na"));
    printf("%s\n", brk(sample1, "n"));
    printf("%s\n", brk(sample2, "go"));
    
    
    char str1[] = "abcde2fghi3jk4l";
    char str2[] = "34";
    char *ret;
    
    ret = brk(str1, str2);
 
    printf("First matching character: %c\n", *ret);
    
    
    char str[] = "This is a sample string";
    char key[] = "aeiou";
    char * pch;
    printf ("Vowels in '%s': ",str);
    pch = strpbrk (str, key);
    while (pch != NULL)
    {
        printf ("%c " , *pch);
        pch = strpbrk (pch+1,key);
    }
    printf ("\n");
    
    char *result, *string = "A Blue Danube";
    char *chars = "ab";
    
    result = strpbrk(string, chars);
    printf("The first occurrence of any of the characters \"%s\" in "
           "\"%s\" is \"%s\"\n", chars, string, result);

    return 0;



}
