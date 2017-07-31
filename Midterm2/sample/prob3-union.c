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
void llist_add(LinkedList * list, int value) {
    // Create new node
    ListNode * n = (ListNode *) malloc(sizeof(ListNode));
    n->value = value;
    
    // Add at the beginning of the list
    n->next = list->head;
    list->head = n;
}
//llist_union(LinkedList * list1, LinkedList * list2, LinkedList * list3) -- Find the union of values of list1 and list2. Store the union of these two lists inside of list 3. There should be no repeating values in list3.

void llist_union(LinkedList * list1, LinkedList * list2, LinkedList * list3){
    ListNode * l1 = list1->head;
    ListNode * l2 = list2->head;
    ListNode * l3 = (ListNode *)malloc(sizeof(ListNode));
    int value;
    while (l1!=NULL) {
        value = l1->value;
        llist_add(list3, value);
        l1=l1->next;
    }
    while (l2!=NULL) {
        value = l2->value;
       
        l2=l2->next;
        llist_add(list3, value);
    }
    l3->next=NULL;


}

void llist_sort(LinkedList * list, int ascending) {
    ListNode * e =list->head;
    ListNode * p =list->head;
    int temp=0;
    if (ascending==1) {
        for (; e!=NULL; e=e->next) {
            for (p=e->next; p!=NULL; p=p->next) {
                if (e->value > p->value) {
                    temp=e->value;
                    e->value=p->value;
                    p->value=temp;
                }
            }
        }
    }
    else if (ascending==0) {
        for (; e!=NULL; e=e->next) {
            for (p=e->next; p!=NULL; p=p->next) {
                if (e->value < p->value) {
                    temp=e->value;
                    e->value=p->value;
                    p->value=temp;
                }
            }
        }
    }
    
}

void removeintersec(LinkedList * list1){
    ListNode * e=list1->head;
    while ((e->next)!=NULL) {
        if (e->value==e->next->value) {
            e->next=e->next->next;
            continue;
        }
        e=e->next;
    }
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
    
    LinkedList list2;
    llist_init(&list2);
    
    for (i = 30; i >= 0; i=i-5) {
        llist_add(&list2, i);
    }
    
    printf("List 2\n");
    llist_print(&list2);
    
    LinkedList list3;
    llist_init(&list3);
    printf("Intersection of List 1 and List 2\n");
    llist_union(&list1, &list2, &list3);
    llist_sort(&list3, 1);
    llist_print(&list3);
    removeintersec(&list3);
    llist_print(&list3);

}
