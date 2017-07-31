#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "review.h"

// Problem (1/4)
/******************************************************************************
 * TODO: Return a pointer to the first occurrence of the character 'c' in the 
 * string 's'. Return NULL if the character is not found.
 * 
 * Parameters: s -- string
 *             c -- search for this character in the string 's'
 *
 * Return: pointer to the first occurene of the character c in the string s
 *
 * Return Type: char pointer
 *****************************************************************************/
char *strchr(const char *s, int c) 
{
    const char ch = c;
    
    for ( ; *s != ch; s++)
        if (*s == '\0')
            return 0;
    return (char *)s;
}

// Problem (2/4)
/******************************************************************************
 * TODO: Return the maximum element in the array
 * 
 * Parameters: array -- an integer array
 *             n -- number of elements in the array
 *
 * Return: the maximum element in the array
 *
 * Return Type: integer
 *****************************************************************************/
int max_array( int * array, int n )
{
    int i=0;
    int check=array[0];
    for (; i<n; i++) {
        if (array[i]>check) {
            check=array[i];
        }
    }
    // Write Your Code Here
    return check;
}

// Problem (3/4)
/******************************************************************************
 * TODO: Return the 'ith' bit in 'bitmap' (either 0 or 1)
 * 
 * Parameters: bitmap -- unsigned integer
 *             ith -- index of the bit to be returned
 *
 * Return: the largest element in the array 
 *
 * Return Type: integer
 *****************************************************************************/
int get_bit_at( unsigned int bitmap, int ith )
{
    unsigned int shift = (1<<ith);
    if (shift&bitmap) {
        return 1;
    }
    return 0;
}

// Problem (4/4)
/******************************************************************************
 * TODO: Read from the file and store the entries in to a single linked list.
 * Return the list. Use the function llist_add( List * list, int value ) to
 * add entries to the list. 
 *
 * The file format will be:
 * value\n
 * value\n
 * value\n
 * ...
 *
 * Parameters: filename -- the name of the file you will be reading from
 *
 * Return: a singled linked list which contains the values read from the file
 *
 * Return Type: pointer to a single linked list
 *****************************************************************************/
List * llist_read( char * filename ) 
{
    // Write Your Code Here
    ListNode * n = (ListNode *)malloc(sizeof(ListNode));
    List * tmp = (List *)malloc(sizeof(List));
    
    n = tmp->head;
    
    int buff;
    
    FILE* fd = fopen(filename, "w+");
    
    if(fd == NULL) {
        return NULL;
    }
    
    while(fscanf(fd,"%d",&buff) != EOF) {
        llist_add(tmp, buff);
    }
    
    fclose(fd);
    return tmp;
}
