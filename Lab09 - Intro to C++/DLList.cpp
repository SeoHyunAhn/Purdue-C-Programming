#include "DLList.h"
#include <stdio.h>

/**
 * @brief      Constructor for the DLList.
 */
DLList::DLList()
{
    head = new DLNode();
    head->data = 0;
    head->next = head;
    head->prev = head;
	/** @todo Write a constructor for a dllist. Check slides! **/
}

/**
 * @brief     Destructor for the DLList.
 */
DLList::~DLList()
{
    
	/** @todo Clean up your mess! **/
}

/**
 * @brief      Print the DLList line by line.
 */
void DLList::print()
{
    DLNode * e=head->next;
    while (head!=e) {
        printf("%d\n", e->data);
        e=e->next;
    }
}

/**
 * @brief      Sort and print the list.
 * 
 * This function should sort and print the list.
 * Note: the actual list is NOT to be modified.
 * In other words, it should only *print* in a
 * sorted order, not actually sort the list.
 */
void DLList::printSorted()
{
    DLNode * behind = head->prev;
    DLNode * ahead = head;
    
    while (behind!=head) {
        printf("%d\n", behind->data);
        behind=behind->prev;
    }
}

/**
 * @brief      Add to the front of the list.
 *
 * @param[in]  data  Item to add to front.
 */
void DLList::insertFront(int data)
{
    DLNode * temp =new DLNode();
    temp->data=data;
    temp->next=head->next;
    head->next = temp;
    temp->next->prev=temp;
    temp->prev=head;
}

/**
 * @brief      Removes & stores the last element.
 *
 * The last element is removed and stored in the
 * referenced variable data.
 * 
 * @param      data  Thing in which we are storing the data.
 *
 * @return     True upon successful removal.
 */
bool DLList::removeLast(int & data)
{
    DLNode * e= head->prev;
    if(e!=head){
        DLNode * temp = e;
        data = e->data;
        e=e->prev;
        free(temp);
        head->prev=e;
        e->next=head;
        temp=e;
        return true;
    }
    return false;
}

/**
 * @brief      Difference of two lists.
 *
 * @param      list  Subtrahend.
 *
 * @return     Returns a pointer to the difference.
 */
DLList * DLList::difference(DLList & list)
{
	DLList * diff = new DLList();
    
    DLNode * e = head->next;
    DLNode * temp = list.head->next;
    bool flag=true;
    
    while (e!=head) {
        while (temp!=list.head) {
            if (e->data==temp->data) {
                flag=false;
                break;
            }
            temp=temp->next;
        }
        if (flag==true) {
            DLNode * save = new DLNode();
            save->data = e->data;
            save->next= diff->head->next;
            save->prev = diff->head;
            save->next->prev= save;
            save->prev->next=save;
        }
        flag= true;
        e= e->next;
        temp=list.head->next;
    }
	return diff;
}

/**
 * @brief      Returns a sublist of items in a range.
 *
 * @param[in]  start  First index.
 * @param[in]  end    Second index.
 *
 * @return     Elements between first and second index.
 */
DLList * DLList::getRange(int start, int end)
{
	DLList * range = new DLList();
    DLNode * e = head->next;
    while (e!=head) {
        if (e->data>=start || e->data<=end) {
            DLNode * save = new DLNode();
            save->data = e->data;
            save->next= range->head->next;
            save->prev = range->head;
            save->next->prev= save;
            save->prev->next=save;
        }
        e=e->next;
    }
	return range;
}

/**
 * @brief      Intersection of this list and another list.
 *
 * @param      list  The other list.
 *
 * @return     Elements list shares with this one.
 */
DLList * DLList::intersection(DLList & list)
{
	DLList * inter = new DLList();
    DLNode *e = head->next;
    DLNode * le= list.head->next;
    while(e != head){
        while(le != list.head){
            if (le->data == e->data) {
                DLNode * temp = new DLNode();
                temp->data =  le->data;
                temp->next = inter->head;
                temp->prev = inter->head->prev;
                temp->prev->next = temp;
                inter->head->prev = temp;
            }
            le=le->next;
        }
        e=e->next;
        le=list.head->next;
    }
	return  inter;
}

/**
 * @brief      Removes nodes in the start-end range.
 *
 * @param[in]  start  First node.
 * @param[in]  end    Second node.
 */
void DLList::removeRange(int start, int end)
{
    DLNode * e = head->next;
    while (e!=head) {
        if (e->data<start || e->data>end) {
            DLNode * temp = e;
            e=e->prev;
            free(temp);
            head->prev=e;
            e->next=head;
            temp=e;
        }
        e=e->next;
    }
}
