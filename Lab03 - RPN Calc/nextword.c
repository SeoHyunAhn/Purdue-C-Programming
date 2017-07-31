/*
 Implement a function named char * nextword(FILE *fd) that reads the next word in the file “fd” and skips space characters.
 */
#include <stdio.h>
#include <stdlib.h>

//
// Separates the file into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;
char * nextword(FILE * fd) {
    int c;
    int i = 0;
    wordLength = 0;
    // While it is not EOF read char
    while ((c= fgetc(fd)) != EOF) {
        if (c == ' '|| c == '\n' || c == '\t'|| c == '\r') {
            if (wordLength > 0)
                return word;
        }
        else {
            word[i] = c;
            i++;
            word[i]='\0';
            wordLength++;
        } 
    }
    if (wordLength > 0)
        return word;
	else
		return NULL;
}
