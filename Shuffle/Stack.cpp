//-----------------------------------------------------------------------------
// Stack.cpp
// Implementation file for Stack ADT
//-----------------------------------------------------------------------------
#include<string>
#include<iostream>
#include<stdexcept>
#include"Stack.h"


// Private Constructor --------------------------------------------------------

// Node constructor
Stack::Node::Node(StackElement x){
   data = x;
   next = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates new Stack in the empty state.
Stack::Stack(){
   top = nullptr;
   height = 0;
}

// Copy constructor.
Stack::Stack(const Stack& S){

   // make this an empty Stack
   top = nullptr;
   height = 0;

   // if S is non-empty, load its elements into this
   if( S.top!=nullptr ){
      Node* N = S.top;
      Node* M = new Node(N->data);
      top = M;
      while( N->next != nullptr ){
         N = N->next;
         M->next = new Node(N->data);
         M = M->next;
      }
      height = S.height;
   }
}

// Destructor
Stack::~Stack(){
   while( height>0 ){
      pop();
   }
}


// Access functions -----------------------------------------------------------

// isEmpty()
// Returns true if Stack is empty, otherwise returns false.
bool Stack::isEmpty() const{
   return(height==0);
}

// getTop()
// Returns the value at top of Stack.
// Pre: !isEmpty()
StackElement Stack::getTop() const{
   if( height==0 ){
      throw std::length_error("Stack: getTop(): empty Stack");
   }
   return(top->data);
}

// getHeight()
// Returns the height of Stack.
int Stack::getHeight() const{
   return(height);
}


// Manipulation procedures ----------------------------------------------------

// push()
// Places new data element on top of Stack.
void Stack::push(StackElement x)
{
   Node* N = new Node(x);

   if( height==0 ) { 
      top = N; 
   }else{ 
      N->next = top;
      top = N;
   }
   height++;
}

// pop()
// Deletes data element on top of Stack.
// Pre: !isEmpty()
void Stack::pop(){
   if( height==0 ){
      throw std::length_error("Stack: pop(): empty Stack");
   }
   
   Node* N = top;
   top = N->next;
   height--;
   delete N;
}


// Other Functions ------------------------------------------------------------

// to_string()
// Returns a string representation of Stack consisting of a space separated 
// list of data values.
std::string Stack::to_string() const{
   Node* N = nullptr;
   std::string s = "";

   for(N=top; N!=nullptr; N=N->next){
      s += std::to_string(N->data)+" ";
   }
   
   return s;
}

// equals()
// Returns true if and only if this Stack is the same sequence as S.
bool Stack::equals(const Stack& S) const{
   bool eq = false;
   Node* N = nullptr;
   Node* M = nullptr;

   eq = ( this->height == S.height );
   N = this->top;
   M = S.top;
   while( eq && N!=nullptr){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}


// Overriden Operators --------------------------------------------------------

// operator<<()
// Inserts string representation of S, as defined by member function to_string(),
// into stream.
std::ostream& operator<< ( std::ostream& stream, const Stack& S ) {
   return stream << S.Stack::to_string();
}

// operator==()
// Returns true if and only if A equals B, as defined by member function equals().
bool operator== (const Stack& A, const Stack& B){
   return A.Stack::equals(B);
}

// operator=()
// Overwrites the state of this Stack with state of S, then returns a reference
// to this Stack.
Stack& Stack::operator=( const Stack& S ){
   if( this != &S ){ // not self assignment
      // make a copy of S
      Stack temp = S;

      // then swap the copy's fields with fields of this
      std::swap(top, temp.top);
      std::swap(height, temp.height);
   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return   
}