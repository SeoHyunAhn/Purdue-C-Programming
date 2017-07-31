// Stack Implementation

// Used for cout << "string"
#include <iostream>

using namespace std;

#include "Stack.h"

// Constructor
Stack::Stack(int maxStack) {
	this->maxStack = maxStack;
	stack = new double[maxStack];
	top = 0;
}

// Write other calls here
bool Stack::pop(double & value){
    if(top==0){
        return false;
    }
    top--;
    value=stack[top];
    return true;


}

bool Stack::push(double val){
    if(top==maxStack){
        return false;
    }
    stack[top]=val;
    top++;
    return true;
}

void Stack::print() const{
    cout<<"Stack:\n";
    for (int i=0; i<top; i++) {
        cout<<i<<":" <<stack[i] << "\n";
    }
    cout<<"------"<<"\n";
}

int Stack::getMaxStack() const{
    return maxStack;
}

int Stack::getTop() const{
    return top;
}


//Destructor
Stack::~Stack(){
    delete [] stack;
}
