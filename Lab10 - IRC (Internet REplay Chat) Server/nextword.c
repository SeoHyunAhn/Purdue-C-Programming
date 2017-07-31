
#include <stdio.h>
#include <stdlib.h>

//
// Separates the file into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;

// It returns the next word from fd.
// If there are no more more words it returns NULL. 
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
// While it is not EOF and it is a non-space char
// store character in word.
// if char is not in word return word so far.
//
// Return null if there are no more words
	else
	  return NULL;
}

