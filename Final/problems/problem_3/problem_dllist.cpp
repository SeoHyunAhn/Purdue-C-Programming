#include <iostream>
#include <string>
#include "DLList.h"

// Constructor
// DO NOT CHANGE
DLList::DLList() 
{
    head = new ListNode();
    head->next = head;
    head->prev = head;
}

// Prints the list
// DO NOT CHANGE
void DLList::print_list() 
{
    std::cout << "Printing List..." << std::endl;
    if ( head->next == head ) {
	std::cout << "Empty List" << std::endl;
    }
    else {
	ListNode * e = head->next;  
	while ( e != head) {
	    if ( e->next != head )
		std::cout << e->value << ", ";
	    else 
		std::cout << e->value;
	    e = e->next;
	}
	std::cout << std::endl;
    }
}

// Prints the list given a list name
// DO NOT CHANGE
void DLList::print_list( std::string list_name ) 
{
    std::cout << "Printing " << list_name << "..." << std::endl;
    if ( head->next == head ) {
	std::cout << "Empty List" << std::endl;
    }
    else {
	ListNode * e = head->next;  
	while ( e != head) {
	    if ( e->next != head )
		std::cout << e->value << ", ";
	    else 
		std::cout << e->value;
	    e = e->next;
	}
	std::cout << std::endl;
    }
}

// Problem (1/5)
/******************************************************************************
 * TODO: Write the destructor. The destructor should delete all of the 
 * list nodes from the list. 
 *****************************************************************************/
void DLList::removeLast()
{
    ListNode *e = head->next;
    
    while(e->next != head){
        e = e->next;
    }
    e->next->prev = e->prev;
    e->prev->next = e->next;
    delete(e);
    
}


DLList::~DLList()
{
    // Write Your Code Here
    ListNode *e = head;
    
    while(e->next != head){
        removeLast();
    }
    delete head;
    
}


// Problem (2/5)
/******************************************************************************
 * TODO: Insert a new ListNode to the end of the double linked list. 
 * Remember the list head is a sentinel node, do not change head. 
 * Set the value of the new node to the parameter 'value'.
 * 
 * Parameters: value -- set the value of the node equal to this
 *
 * Return: void 
 *
 * Return Type: void
 *****************************************************************************/
void DLList::insert_last( int value ) 
{
    ListNode * temp = new ListNode();
    
    temp->value=value;
    temp->next = head;
    temp->prev = head->prev;
    head->prev->next = temp;
    head->prev=temp;
    
    // Write Your Code Here
}

// Problem (3/5)
/******************************************************************************
 * TODO: Remove the node from the double linked list whose value equals the 
 * parameter 'value', return true after deleting the node. If the node does not
 * exist in the list or the list is empty, return false;
 * 
 * Parameters: value -- remove the node whose value is equal to this
 *
 * Return: true if the node was removed successfully
 *         false if the value does not exist in the list or the list is empty
 *
 * Return Type: void
 *****************************************************************************/
bool DLList::remove( int value ) 
{
    ListNode * e = head->next;
    while ( e != head) {
        if ( e->value == value ){
            ListNode *temp = e;
            temp->next->prev = e->prev;
            temp->prev->next = e->next;
             delete(e);
            return true;
            
        }
        e=e->next;
    }
    // Write Your Code Here
    return false;
}

// Problem (4/5)
/*****************************************************************************
* TODO: Return the ith node inside of the double linked list. If the list is
* empty or has less than 'ith' entries, return NULL.
* 
* Return: the 'ith' node in the list
*         NULL if the node does not exist
*
* Return Type:  
*****************************************************************************/
ListNode * DLList::get_ith( int ith ) 
{
    int i=0;
    ListNode * e = head->next;
    while (e!=head) {
        if (i==ith) {
            return e; 
        }
        e=e->next;
        i++;
    }
    // Write Your Code Here
   return NULL;
}

// Problem (5/5)
/*****************************************************************************
* TODO: Overload the operator '==' for comparison. The comparison operator
* should compare the two lists to check if they have the all of the same
* elements. Return true if the two lists are equal, return false otherwise.
*****************************************************************************/
bool DLList::operator == (const DLList & listB) 
{
    // Write Your Code Here
    ListNode * e = head->next;
    ListNode * p = listB.head->next;

    while(e != head) {
        
        if(e->value != p->value) {
            return false;
        }
        
        e = e->next;
        p = p->next;
        
    }
    
    e = head->next;
    p = listB.head->next;
    
    while(p != listB.head) {
        
        if(e->value != p->value) {
            return false;
        }
        
        e = e->next;
        p = p->next;
        
    }
    
    
    return true;
}

