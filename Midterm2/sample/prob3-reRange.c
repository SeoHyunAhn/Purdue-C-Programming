#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LinkedList.h"

//Initialize the linked list
void llist_init(LinkedList * list)
{
    list->head = NULL;
}

// Prints the linked list
void llist_print(LinkedList * list) {
    
    ListNode * e;
    
    if (list->head == NULL) {
        printf("{EMPTY}\n");
        return;
    }
    
    printf("{");
    
    e = list->head;
    while (e != NULL) {
        printf("%d", e->value);
        e = e->next;
        if (e!=NULL) {
            printf(", ");
        }
    }
    printf("}\n");
}

//list_removeRange(LinkedList * list, int low, int high) -- Remove the elements in the given range from low to high in the list. This includes elements in index low and index high.

void llist_removeRange(LinkedList * list, int low, int high) {
    ListNode *e =(ListNode *)malloc(sizeof(ListNode));
     ListNode *lastVal =(ListNode *)malloc(sizeof(ListNode));
    e=list->head;
    int count=0;
    
    while (e !=NULL) {
        if (count==low) {
            ListNode * temp=e;
            while (count<=high) {
                e=e->next;
                free(temp);
                temp=e;
                count++;
            }
            lastVal->next=e;
        }
        lastVal=e;
        e=e->next;
        count++;
    }

}

void llist_add(LinkedList * list, int value){
    ListNode * e =(ListNode *)malloc(sizeof(ListNode));
    e->value=value;
    
    e->next=list->head;
    list->head=e;

}


int main(){
    LinkedList list1;
    llist_init(&list1);
    
    int i;
    
    for (i = 30; i >= 0; i=i-3) {
        llist_add(&list1, i);
    }
    printf("List 1\n");
    llist_print(&list1);
    
    llist_removeRange(&list1, 2, 5);
   
    llist_print(&list1);
    
}
