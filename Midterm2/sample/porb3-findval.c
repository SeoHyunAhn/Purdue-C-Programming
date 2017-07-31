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


void llist_add(LinkedList * list, int value){
    ListNode *e = (ListNode *)malloc(sizeof(ListNode));
    e->value = value;
    
    e->next=list->head;
    list->head = e;
}
//llist_find_value(LinkedList * list, int value)- Iterate through the single linked list and find if any value in the list matches the value passed in the parameter.
int llist_find_value(LinkedList * list, int value){
    ListNode *e = list-> head;
    int count=1;
    while (e!=NULL) {
        if (e->value==value) {
            return count;
        }
        
        count++;
        e=e->next;
    }
    
    return 0;
    
}


int main(){
    LinkedList list1;
    LinkedList list2;
    
    llist_init(&list1);
    llist_init(&list2);
    
    int i;
    
    for (i = 30; i >= 0; i=i-3) {
        llist_add(&list1, i);
    }
    for (i = 30; i >= 0; i=i-5) {
        llist_add(&list2, i);
    }
    llist_print(&list1);
    llist_print(&list2);
    printf("%d\n",llist_find_value(&list1, 12));
    llist_print(&list2);
    llist_print(&list1);
    return 0;
    
    
}
