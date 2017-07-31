
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

//
// Initialize a linked list
//
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

//
// Returns true if the value exists in the list.
//
int llist_exists(LinkedList * list, int value) {
    ListNode *e =list->head;
    while(e!=NULL){
        if (e->value==value) {
            return 1;
        }
        e=e->next;
    }
    return 0;
}

//
// It removes the entry with that value in the list.
int llist_remove(LinkedList * list, int value) {
    ListNode *e =list->head;
    if (e->value==value) {
        free(e);
        e=e->next;
        list->head=e;
        return 1;
    }
    while(e->next!=NULL){
        if (e->next->value==value) {
            e->next =e->next->next;
            return 1;
        }
        e=e->next;
    }
    return 0;
}

//
// It stores in *value the value that correspond to the ith entry.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_get_ith(LinkedList * list, int ith, int * value) {
    if (!list ||!list->head) {
        return 0;
    }
    ListNode **i=&(list->head);
    for (; *i&&(ith-->0);i=&(*i)->next);
    if (*i) {
        *value=(*i)->value;
    }
    return !!*i;
}

//
// It removes the ith entry from the list.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_remove_ith(LinkedList * list, int ith) {
    if (!(list ||list->head)) {
        return 0;
    }
    ListNode **i=&(list->head);
    for (; *i&&(ith-->0);i=&(*i)->next);
    return (*i) ? !!(free(*i), *i=(*i)->next) : 0;
}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LinkedList * list) {
    ListNode *e=list->head; 
    int i=0;
    while (e!=NULL) {
        i++;
        e=e->next;
    }
    return i;
}


//
// It saves the list in a file called file_name. The format of the
// file is as follows:
//
// value1\n
// value2\n
// ...
//
int llist_save(LinkedList * list, char * file_name) {
    ListNode *e=list->head;
    FILE *fp=fopen(file_name, "w+");
    if (fp==NULL) {
        return 0;
    }
    while (e!=NULL) {
        fprintf(fp, "%d\n", e->value);
        e=e->next;
    }
    fclose(fp);
    return 0;
}

//
// It reads the list from the file_name indicated. If the list already has entries,
// it will clear the entries.
//
int llist_read(LinkedList * list, char * file_name) {
    ListNode *e=list->head;
    int buff;
    FILE *fp=fopen(file_name, "r");
    if (fp==NULL) {
        return 0;
    }
    while (fscanf(fp, "%d", &buff)!=EOF) {
       // fprintf(fp, "", e->value);
        
        llist_add(list, buff);
    }
    fclose(fp);
    return 1;
}


//
// It sorts the list. The parameter ascending determines if the
// order si ascending (1) or descending(0).
//
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

//
// It removes the first entry in the list and puts value in *value.
// It also frees memory allocated for the node
//
int llist_remove_first(LinkedList * list, int * value) {
    
    if (!list ||!list->head) {
        return 0;
    }
    ListNode * temp = list->head;
    *value=temp->value;
    list->head = temp->next;
    free(temp);
    return 1;
}

//
// It removes the last entry in the list and puts value in *value/
// It also frees memory allocated for node.
//
int llist_remove_last(LinkedList * list, int *value) {
  
    if (!list ||!list->head) {
        return 0;
    }
    ListNode * ahead = list->head->next;
    ListNode * behind = list->head;
    while(ahead->next){
        ahead = ahead->next;
        behind = behind->next;
    }
    *value = ahead->value;
    behind->next = NULL;
    free(ahead);
    return 1;
}

//
// Insert a value at the beginning of the list.
// There is no check if the value exists. The entry is added
// at the beginning of the list.
//
void llist_insert_first(LinkedList * list, int value) {
    ListNode * n = (ListNode *) malloc(sizeof(ListNode));
    n->value = value;
    
    // Add at the beginning of the list
    n->next = list->head;
    list->head = n;
}

//
// Insert a value at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
//
void llist_insert_last(LinkedList * list, int value) {
    
    ListNode * ahead = list->head;

    if(!(list->head)){
    	list->head =ahead;
	ahead->value = value;
	list->head->next = NULL;
    }
    while(ahead->next!=NULL){
    	ahead = ahead ->next;
    }
    
    ListNode * temp = (ListNode *)malloc(sizeof(ListNode));
    temp->value = value;
    temp->next=NULL;
    ahead->next=temp;
    
}

//
// Clear all elements i/*n the list and free the nodes

void llist_clear(LinkedList *list)
{
    ListNode * n = list->head;
    while(n){
        n = n->next;
        free(n);
    }
    list->head = NULL;
    
}
