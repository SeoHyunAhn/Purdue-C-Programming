#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"
void llist_init(LinkedList * list)
{
    list->head = NULL;
}

//
// It prints the elements in the list in the form:
// 4, 6, 2, 3, 8,7
//
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

//
// Appends a new node with this value at the beginning of the list
//
void llist_add(LinkedList * list, int value) {
    // Create new node
    ListNode * n = (ListNode *) malloc(sizeof(ListNode));
    n->value = value;
    
    // Add at the beginning of the list
    n->next = list->head;
    list->head = n;
}

int llist_remove(LinkedList * list, int value) {
    ListNode *e =list->head;
    if (e->value==value) {
        printf("%d 1\n", e->value);
        free(e);
        e=e->next;
        list->head=e;
        return 1;
    }
    while(e->next!=NULL){
        printf("%d 0\n", e->value);
        if (e->next->value==value) {
            e->next =e->next->next;
            return 1;
        }
        e=e->next;
    }
    
    
    return 0;
}


int main(){
    int i = 0;
    int result;
    LinkedList list;
    
    llist_init(&list);
    
    llist_print(&list);
    
    for (i=0; i < 30; i+=3) {
        printf("Adding %d\n", i);
        llist_add(&list, i);
    }
    
    llist_print(&list);
    
    printf("remove 0\n");
    result = llist_remove(&list, 0);
    printf("result1=%d\n", result);
    
    llist_print(&list);
    
    printf("remove 18\n");
    result = llist_remove(&list, 18);
    printf("result2=%d\n", result);
    
    llist_print(&list);
    
    printf("remove 64\n");
    result = llist_remove(&list, 27);
    printf("result3=%d\n", result);
    
    llist_print(&list);
}
