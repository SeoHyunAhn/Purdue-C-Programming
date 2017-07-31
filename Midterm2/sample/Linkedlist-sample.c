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
void llist_add(LinkedList * list, int value){
    ListNode *n=(ListNode *)malloc(sizeof(ListNode));
    n->value=value;
    
    n->next=list->head;
    list->head=n;

}

int llist_exist(LinkedList * list, int value){
    ListNode * e= list->head;
    while (e!=NULL) {
        if (e->value==value) {
            return 1;
        }
        e=e->next;
    }
    return 0;
}
void llist_remove(LinkedList * list, int value){
    ListNode * e= list->head;
    if (e->value==value) {
        free(e);
        e=e->next;
        return;
    }

    while (e->next!=NULL) {
        if (e->next->value==value) {
            e->next=e->next->next;
        }
        e=e->next;
    }
}
int llist_get_ith(LinkedList * list, int ith, int *value){
    if (!list||!list->head) {
        return 0;
    }
    ListNode **i=&(list->head);
    for (; i*&&(ith-->0); i=&(*i)->next);
    if (*i) {
        *value=(*i)->value;
    }
    return !!(*i);
}

int llist_remove_ith(LinkedList * list, int ith){
    if (!list||!list->head) {
        return 0;
    }
    ListNode **i=&(list->head);
    for (; i*&&(ith-->0); i=&(*i)->next);
    return (*i) ? !!(free(*i), *i=(*i)->next)) : 0;

}//중요중요

int llist_number_elements(LinkedList * list){
    ListNode * e= list->head;
    int count=0;
    while (e!=NULL) {
        count++;
        e=e->next;
    }
    return count;
}

int llist_save(LinkedList * list, char * file_name){
    FILE *fp=fopen(file_name, "w+");
    if (!list||!list->head) {
        return 0;
    }
    if (fp==NULL) {
        return 0;
    }
     ListNode * e= list->head;
    while (e!=NULL) {
        fprintf("%d\n", e->value);
        e=e->next;
    }
    fclose(fp);
    return 0;
}

int llist_read(LinkedList * list, char * file_name){
    if (list||list->head) {
        llist_clear(list);
    }
    int buff;
    FILE *fp=fopen(file_name, "r");
    if(fp==NULL)
        return 0;
    while (fscanf(fp, "%d", &buff)!=EOF) { //이부분 틀렸었습니다
        llist_add(list, buff);
    }
    fclose(fp);
    return 1;
}
void llist_sort(LinkedList * list, int ascending){
    ListNode *e=list->head;
    ListNode *p=(ListNode *)malloc(sizeof(ListNode));
    ListNode * temp=(ListNode *)malloc(sizeof(ListNode));
    
    if (ascending==1) {
        for (; e!=NULL; e=e->next) {
            for (p=e->next; p!=NULL; p=p->next) {
                if (e->value > p->value) {
                    temp=e->value;
                    e->value=p->value;
                    p->value=temp
                }
            }
        }
    } else if (ascending==0){
        for (; e!=NULL; e=e->next) {
            for (p=e->next; p!=NULL; p=p->next) {
                if (e->value < p->value) {
                    temp=e->value;
                    e->value=p->value;
                    p->value=temp
                }
            }
        }
    }

}
int llist_remove_first(LinkedList * list, int * value){//이거 외우기
    if (!list||!list->head) {
        return 0;
    }
    ListNode *temp=list->head;
    *value=temp->value;
    list->head=temp->next;
    free(temp);
    return 0;
}

int llist_remove_last(LinkedList * list, int *value){
    ListNode *ahead=list->head;
     ListNode *behind=list->head->next;
    while (ahead!=NULL) {
        ahead=ahead->next;
        behind=behind->next;
    }
    *value=ahead->value;
    behind->next=NULL;
    free(ahead);
    return 1;

}
int llist_insert_last(LinkedList * list, int value){
    ListNode *temp=list->head;
    
    
    while (temp->next!=NULL) {
        temp=temp->next;
    }
    ListNode *behind=(ListNode *)malloc(sizeof(ListNode));
    behind->value=value;
    behind->next=NULL;
    temp->next=behind;
    free(temp);
    return 1;

}

void llist_clear(LinkedList *list){
    ListNode *n=list->head;
    while (n) {
        free(n);
        n=n->next;
    }
    list->head=NULL;//이 줄 기억
}
void llist_union(LinkedList * list1, LinkedList * list2, LinkedList * list3){
    ListNode *ahead=list1->head;
    ListNode *behind=list2->head;
    
    for (; ahead!=NULL; ahead=ahead->next) {
        for (; behind!=NULL; behind=behind->next) {
            if (ahead->value==behind->value) {
                int value=ahead->value
                llist_add(list3, value);
            }
        }
    }
}
void llist_removeRange(LinkedList * list, int low, int high){
    ListNode * e =list->head;
    ListNode * finalVal=(ListNode *)malloc(sizeof(ListNode));
    int count=0;
    while (e!=NULL) {
        if (count==low) {
            ListNode *temp=e;
            while (count<=high) {
                e=e->next;
                free(temp);
                temp=e;
                count++;
            }
            finalVal->next=e;
        }
        count++;
        finalVal=e;
        e=e->next;
    }
}
void llist_reverse( LinkedList * list ) {
    int array[32];
    ListNode *e=list->head;
    int arrcount=0;
    while (e!=NULL) {
        array[arrcount]=e->value;
        arrcount++;
        e=e->value;
    }
    e=list->head;
    for (; arrcount>=0; arrcount--) {
        e->value=array[arrcount];
        e=e->next;
    }

}






