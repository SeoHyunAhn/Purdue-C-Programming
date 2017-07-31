#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//
// Sort an array of element of any type
// it uses "compFunc" to sort the elements.
// The elements are sorted such as:
//
// if ascending != 0
//   compFunc( array[ i ], array[ i+1 ] ) <= 0
// else
//   compFunc( array[ i ], array[ i+1 ] ) >= 0
//
// See test_sort to see how to use mysort.
//

void mysort( int n,                      // Number of elements
            int elementSize,            // Size of each element
            void * array,               // Pointer to an array
            int ascending,              // 0 -> descending; 1 -> ascending
            CompareFunction compFunc )  // Comparison function.
{
    // Add your code here
    void * tmp = (void*)malloc(elementSize);
    int i, j;
    void * e1, *e2;
   
    for(i = 0; i < n; i++) {
        for(j = 0; j < n - 1;j++) {
            //compute pointer to entry j
            e1 = (void*)((char*)array + j * elementSize);
            e2 = (void*)((char*)array + (j + 1) * elementSize);
          
            if ( (ascending == 1) && ((*compFunc)(e1 , e2) > 0)){
                memcpy(tmp, e1, elementSize);
                memcpy(e1, e2, elementSize);
                memcpy(e2, tmp, elementSize);
            }
            
            if ((ascending == 0) && ((*compFunc)(e1 , e2) < 0)) {
                memcpy(tmp, e1, elementSize);
                memcpy(e1, e2, elementSize);
                memcpy(e2, tmp, elementSize);
            }
            
        }
    }
    free(tmp);
}
