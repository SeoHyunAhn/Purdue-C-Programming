#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LinkedList.h"

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
int llist_number_elements(LinkedList * list) {
    // Write Your Code Here
    int count=0;
    ListNode * e=list->head;
    while (e!=NULL) {
        count++;
        e=e->next;
    }
    return count;
}

void llist_add(LinkedList * list, int value){
    ListNode * e = (ListNode *)malloc(sizeof(ListNode));
    e->value=value;
    
    e->next=list->head;
    list->head=e;

}

void llist_reverse(LinkedList *list){
    
    int i = 0;
    int lenthOfList = llist_number_elements(list);
    int valOfList[lenthOfList];
    ListNode *nodePT;
    nodePT = list->head;
    
    while(nodePT != '\0'){
        valOfList[i] = nodePT->value;
        nodePT = nodePT->next;
        i++;
    }
    
    nodePT = list->head;
    
    for(i = 0; i < lenthOfList; i++){
        nodePT->value = valOfList[lenthOfList - 1 - i];
        nodePT = nodePT->next;
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
    
    llist_reverse(&list1);
    
    llist_print(&list1);
    return 0;


}
