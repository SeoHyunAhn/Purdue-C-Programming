
// String Implementation
// IMPORTANT: Do not use any of the functions in the string C runtime library
// Example. Do not use strcpy, strcmp, etc. Implement your own

// IMPORTANT: See the MyString.h file for a description of
// what each method needs to do.

#include <stdio.h>
#include "MyString.h"

// My own implementation of strlen
int
MyString::slength(const char *s) const
{
    int i=0;
    while (s[i]!='\0') {
        i++;
    }
  return i;
}

// Initialize _s. Allocate memory for _s and copy s into _s
void
MyString::initialize(const char * s)
{
    _s = new char[slength(s)];
    
    for (int i=0; s[i]!='\0'; i++) {
        _s[i]=s[i];
    }
 }

// Create a MyString from a C string
MyString::MyString(const char * s)
{
  initialize(s);
}

// Create a MyString from a copy of another string
MyString::MyString(const MyString &s)
{
  initialize(s._s);
}

// Create a MyString with an empty string
MyString::MyString()
{
  _s = new char[1];
  *_s = 0;
}

// Assignment operator. Without this operator the assignment is
// just a shallow copy that will copy the pointer _s. If the original _s
// goes away then the assigned _s will be a dangling reference.
MyString &
MyString::operator = (const MyString & other) {
  if (this != &other) // protect against invalid self-assignment
  {
    // deallocate old memory
    delete [] _s;

    // Initialize _s with the "other" object.
    initialize(other._s);

    // by convention, always return *this
    return *this;
  }
}

// Obtain a substring of at most n chars starting at location i
// if i is larger than the length of the string return an empty string.
MyString
MyString::substring(int i, int n)
{
    char * temp = new char[n];
    if (i>slength(_s)) {
        return *(new MyString());
    }
    int a=0;
    for (; _s[i]!='\0';i++ ) {
        temp[a]=_s[i];
        a++;
        if (a==n) {
            break;
        }
    }
    temp[a]='\0';
  return *(new MyString(temp));
}

// Remove at most n chars starting at location i
void
MyString::remove(int i, int n)
{
    if (i>slength(_s)) {
        return;
    }
    int count=0;
    for (; _s[i]!='\0'; i++) {
        _s[i]=_s[i+n];
    }
    _s[i+n]='\0';
}

// Return true if strings "this" and s are equal
bool
MyString::operator == (const MyString & s)
{
    for (int i=0; s[i]!='\0'; i++) {
        if (_s[i]!=s._s[i]) {
            return false;
        }
    }
  return true;
}


// Return true if strings "this" and s are not equal
bool
MyString::operator != (const MyString &s)
{
    for (int i=0; s[i]!='\0'; i++) {
        if (_s[i]==s._s[i]) {
            return true;
        }
    }
  return false;
}

int MyString::mystrcmp(char * s1, char * s2) {
    char temp1, temp2;
    while(1){
        temp1=*s1++;
        temp2=*s2++;
        if(temp1!=temp2)
            return temp1<temp2 ?-1:1;
        if(!temp1)
            break;
    }
    return 0;
}

// Return true if string "this" and s is less or equal
bool
MyString::operator <= (const MyString &s)
{
    int result = mystrcmp(_s, s._s);
    
    if (result == -1 || result == 0) return true;
  return false;
}

// Return true if string "this" is greater than s
bool
MyString::operator > (const MyString &s)
{
    for (int i=0; s[i]!='\0'; i++) {
        if (_s[i]<=s._s[i]) {
            return true;
        }
    }
    return false;
}

// Return character at position i.  Return '\0' if out of bounds.
char
MyString::operator [] (int i) const
{
    if (_s[i]!='\0') {
        return _s[i];
    }
  // Add implementation here
  return '\0';
}

// Return C representation of string
const char *
MyString::cStr()
{
  // Add implementation here
    return _s;
}

// Get string length of this string.
int
MyString::length() const
{
  // Add implementation here
  return slength(_s);
}

// Destructor. Deallocate the space used by _s
MyString::~MyString()
{
  // Add implementation here
  delete [] _s;
}

// Concatanate two strings (non member method)
MyString operator + (const MyString &s1, const MyString &s2)
{
    
    int lengths1 = s1.slength(s1._s);
    int lengths2 = s2.slength(s2._s);
    int finalLength = lengths1 + lengths2;
    
    char * s = new char[finalLength];
    int i;
    
    for (i = 0; i < lengths1; i++) {
        s[i] = s1[i];
    }
    
    int j;
    for (j=0; j<lengths2; j++) {
        s[i+j] = s2[j];
    }
    s[i+j]='\0';
    
  return *(new MyString(s));
}

