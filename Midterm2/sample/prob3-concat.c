#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LinkedList.h"

//llist_concatenation(LinkedList * list1, LinkedList * list2) -- Append all of the elements in list2 to list1.
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

void llist_concatenation(LinkedList * list1, LinkedList * list2){
    ListNode * e = list1->head;
    while (e!=NULL) {
        e=e->next;
    }
    
    ListNode * li2 = list2->head;
    
    while (li2!=NULL) {
        ListNode * temp = (ListNode *)malloc(sizeof(ListNode));
        temp->value=li2->value;
        
        temp->next=list1->head;
        list1->head=temp;
        li2=li2->next;
    }
    
}
void llist_add(LinkedList * list, int value){
    ListNode *e = (ListNode *)malloc(sizeof(ListNode));
    e->value = value;
    
    e->next=list->head;
    list->head = e;
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
    llist_concatenation(&list1, &list2);
    llist_print(&list2);
    llist_print(&list1);
    return 0;
    
    
}
