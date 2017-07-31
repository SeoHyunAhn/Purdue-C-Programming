
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WordTable.h"

int isLetter(char ch);

// Initializes a word table
void wtable_init(WordTable * wtable)
{
	// Allocate and initialize space for the table
	wtable->nWords = 0;
	wtable->maxWords = 10;
	wtable->wordArray = (WordInfo *) malloc(wtable->maxWords * sizeof(WordInfo));
	for (int i = 0; i < wtable->maxWords; i++) {
		llist_init(&wtable->wordArray[i].positions);
	}
}
// Add word to the tableand position. Position is added to the corresponding linked list.
void wtable_add(WordTable * wtable, char * word, int position)
{
	// Find first word if it exists
    int i;
	for (i = 0; i < wtable->nWords; i++) {
		if ( strcmp(wtable->wordArray[i].word, word)== 0 ) {
			llist_insert_last(&wtable->wordArray[i].positions, position);
			return;
		}
    }
	// Word not found.
    if (i>=wtable->maxWords) {
        wtable->maxWords = 2*(wtable->maxWords);
        wtable->wordArray=(WordInfo *)realloc(wtable->wordArray,  wtable->maxWords * sizeof(WordInfo));
    }
	// Make sure that the array has space.
	// Expand the wordArray here.
    

	// Add new word and position
	wtable->wordArray[wtable->nWords].word = strdup(word);
	llist_insert_last(&wtable->wordArray[wtable->nWords].positions, position);
	wtable->nWords++;
}

// Print contents of the table.
void wtable_print(WordTable * wtable, FILE * fd)
{
	fprintf(fd, "------- WORD TABLE -------\n");

	// Print words
	for (int i = 0; i < wtable->nWords; i++) {
        if (wtable->wordArray[i].word!=NULL) {
            char * s=wtable->wordArray[i].word;
            fprintf(fd, "%d: %s: ", i, s);
            llist_print( &wtable->wordArray[i].positions);
        }
	}
}

// Get positions where the word occurs
LinkedList * wtable_getPositions(WordTable * wtable, char * word)
{
    int i;
    for (i = 0; i < wtable->nWords; i++) {
        if ( strcmp(wtable->wordArray[i].word, word)== 0 ) {
            return &(wtable->wordArray[i].positions);
        }
	// Write your code here
	//return NULL;
    }
    
}

//
// Separates the string into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;
int wordCount;
int charCount;
int wordPos=0;

// It returns the next word from stdin.
// If there are no more more words it returns NULL.
// A word is a sequence of alphabetical characters.
static char * nextword(FILE * fd) {
	// Write your code here
    int c;
    int i = 0;
    wordLength = 0;
    // While it is not EOF read char
    while ((c= fgetc(fd)) != EOF) {
        if (c == ' '|| c == '\n' || c == '\t'|| c == '\r'||c=='-'||c==39) {
            if (wordLength > 0){
                word[i]='\0';
                //printf("%d: word %s, pos: %d\n\n", temp, word, hello);
                return word;
            }
        }
        else if((c>='A'&&c<='Z')||(c>='a'&&c<='z')){
            word[i] = c;
            i++;
            wordLength++;
        }
    }
    if (wordLength > 0)
        return word;
    else
        return NULL;
}


// Conver string to lower case
void toLower(char *s) {
	// Write your code here
        int i = 0;
        for(; s[i] != '\0'; i++){
            if(s[i] >= 'A' && s[i] <= 'Z'){
                s[i] = s[i]+32;
            }
        }
        s[i] = '\0';
}


// Read a file and obtain words and positions of the words and save them in table.
int wtable_createFromFile(WordTable * wtable, char * fileName, int verbose)
{
    char buff;
    FILE *fp=fopen(fileName, "r");
    int i=0;
    if (fp==NULL) {
        return 0;
    }
    int sum=0;
    char * word;
    while ( (word=nextword(fp)) != NULL) {
        toLower(word);
       int current_pos = ftell(fp);
        int pos = current_pos - strlen(word);
        int back = -2;
        char c = ' ';
        while (!isLetter(c)) {
            fseek(fp, back, SEEK_CUR);
            fread(&c, 1, 1, fp);
            back--;
            fseek(fp, current_pos, SEEK_SET);
            pos--;
        }
        wtable_add(wtable, word, pos);
    if (verbose ==1) {
            printf("%d: word=%s, pos=%d\n", i, word, pos);
            i++;
        }
    }
    
}

// Sort table in alphabetical order.
void wtable_sort(WordTable * wtable)
{// Found word. Add position in the list of positions
    int i=0, j=0;
    LinkedList wordPos;
    LinkedList tempList;
    char *temp;
    for(;i<wtable->nWords-1;i++){
        int j = i+1;
        for(j=i+1;j<wtable->nWords;j++){
            if(strcmp(wtable->wordArray[i].word, wtable->wordArray[j].word)>=1){
                temp = wtable->wordArray[i].word;
                wtable->wordArray[i].word = wtable->wordArray[j].word;
                wtable->wordArray[j].word = temp;
                tempList = wtable->wordArray[i].positions;
                wtable->wordArray[i].positions=wtable->wordArray[j].positions;
                wtable->wordArray[j].positions=tempList;
            }
        }
    }
}

// Print all segments of text in fileName that contain word.
// at most 200 character. Use fseek to position file pointer.
// Type "man fseek" for more info. 
int wtable_textSegments(WordTable * wtable, char * word, char * fileName)
{
    
    FILE *fp = fopen(fileName, "r+");
    int i=0, j=0, k, temp;
    long int pop;
    char c;
    char words[MAXWORD];
    printf("===== Segments for word \"%s\" in book \"%s\" =====\n", word, fileName);
    for (; i<wtable->nWords; i++) {
        if (strcmp(word, wtable->wordArray[i].word)==0) {
            temp=llist_number_elements(&wtable->wordArray[i].positions);
            for (; j<temp; j++) {
                llist_get_ith(&wtable->wordArray[i].positions, j, &pop);
                k=0;
                fseek(fp, pop, SEEK_SET);
                while (k<MAXWORD) {
                    c=fgetc(fp);
                    words[k]=c;
                    k++;
                }
                printf("---------- pos=%d-----\n", pop);
                printf("......%s......\n", words);
            }
        }
    }
}

int isLetter(char c) {
    if(c >= 'a' && c <= 'z') {
        return 1;
    }
    if(c >= 'A' && c <= 'Z') {
        return 1;
    }
    return 0;
}

