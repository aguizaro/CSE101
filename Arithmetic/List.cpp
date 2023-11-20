//-----------------------------------------------------------------------------
// List.cpp by Antonio Guizar Orozco 
// PA6
// CruzID: aguizaro
//
// Implementatin file for the List module.
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"

#define DUMMY -2147483647 // DUMMY = INT_MIN

// Class Constructors & Destructors ----------------------------------------

// Creates new Node with data= x
List::Node::Node(ListElement x){
    data= x;
    next= nullptr;
    prev= nullptr;
}
// Creates new List in the empty state.
List::List(){
    frontDummy= new Node(DUMMY);
    backDummy= new Node(DUMMY);
    frontDummy->next= backDummy;
    frontDummy->prev= nullptr;
    backDummy->next= nullptr;
    backDummy->prev= frontDummy;
    beforeCursor= frontDummy;
    afterCursor= backDummy;
    pos_cursor= 0;
    num_elements= 0;

}

// Copy constructor.
List::List(const List& L){
    //make an empty List
    frontDummy= new Node(DUMMY);
    backDummy= new Node(DUMMY);
    frontDummy->next= backDummy;
    frontDummy->prev= nullptr;
    backDummy->next= nullptr;
    backDummy->prev= frontDummy;
    beforeCursor= frontDummy;
    afterCursor= backDummy;
    pos_cursor= 0;
    num_elements= 0;

    // load elements of L into this List
    Node* N = L.frontDummy->next;

    while( N->data != DUMMY ){
       this->insertBefore(N->data);
       N = N->next;
    }
    
}

// Destructor
List::~List(){
    clear();
    delete this->frontDummy;
    delete this->backDummy;
}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    if (num_elements <= 0){
        throw std::length_error("List: front(): empty list");
    }
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    if (num_elements <= 0){
        throw std::length_error("List: back(): empty list");
    }
    return backDummy->prev->data;

}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    if (pos_cursor >= num_elements){
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    if (pos_cursor <= 0){
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return beforeCursor->data;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    moveFront();
    while(pos_cursor < num_elements){
        eraseAfter();
    }

}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    pos_cursor= 0;
    beforeCursor= frontDummy;
    afterCursor= frontDummy->next;

}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    pos_cursor= num_elements;
    beforeCursor= backDummy->prev;
    afterCursor= backDummy;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
    if (pos_cursor >= num_elements){
        throw std::range_error("List: moveNext(): cursor at back");
    }
    Node* next= afterCursor;
    beforeCursor= beforeCursor->next;
    afterCursor= afterCursor->next;
    pos_cursor++;
    return next->data;

}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
    if (pos_cursor <= 0){
        throw std::range_error("List: movePrev(): cursor at front");
    }
    Node* previous= beforeCursor;
    beforeCursor= beforeCursor->prev;
    afterCursor= afterCursor->prev;
    pos_cursor--;
    return previous->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    Node* N= new Node(x);
    // if List is in the empty state
    if ((beforeCursor->data == DUMMY) && (afterCursor->data == DUMMY)){
        frontDummy->next= N;
        backDummy->prev= N;
        N->prev= frontDummy;
        N->next= backDummy;
        afterCursor= N;
    }else{
        beforeCursor->next= N;
        afterCursor->prev= N;
        N->next= afterCursor;
        N->prev= beforeCursor;
        afterCursor= afterCursor->prev;
    }
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    Node* N= new Node(x);
    // if List is in the empty state
    if ((beforeCursor->data == DUMMY) && (afterCursor->data == DUMMY)){
        frontDummy->next= N;
        backDummy->prev= N;
        N->next= backDummy;
        N->prev= frontDummy;
        beforeCursor= N;
    }else{
        beforeCursor->next= N;
        afterCursor->prev= N;
        N->next= afterCursor;
        N->prev= beforeCursor;
        beforeCursor= beforeCursor->next;

    }
    num_elements++;
    pos_cursor++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    if (pos_cursor >= num_elements){
        throw std::range_error("List: setAfter(): cursor at back");
    }
    afterCursor->data= x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if (pos_cursor <= 0){
        throw std::range_error("List: setBefore(): cursor at front");
    }
    beforeCursor->data= x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    if (pos_cursor >= num_elements){
        throw std::range_error("List: eraseAfter(): cursor at back");
    }
    beforeCursor->next= afterCursor->next;
    afterCursor->next->prev= beforeCursor;
    //update afterCursor
    Node* temp= afterCursor->next;
    delete afterCursor;
    afterCursor= temp;
    num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if (pos_cursor <= 0){
        throw std::range_error("List: eraseBefore(): cursor at front");
    }
    beforeCursor->prev->next= afterCursor;
    afterCursor->prev= beforeCursor->prev;
    //update afterCursor
    Node* temp= beforeCursor->prev;
    delete beforeCursor;
    beforeCursor= temp;
    num_elements--;
    pos_cursor--;

}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
    while(pos_cursor < num_elements){
        // if element is found, leave the cursor after the element
        // and return the current position of the cursor
        if (moveNext() == x){ return pos_cursor;}
    }
    return -1; //return -1 and leave cursor at the end of the list

}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    while(pos_cursor > 0){
        // if element is found, leave the cursor before the element
        // and return the current position of the cursor
        if (movePrev() == x){ return pos_cursor;}
    }
    return -1; //return -1 and leave cursor at the front of the list
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    int i= 0;
    Node* N= frontDummy;
    while (i < pos_cursor){
        N= N->next;
        i++;
    }
    beforeCursor= N;
    afterCursor= N->next;

    Node* current= frontDummy->next;
    while (current->data != DUMMY){
        N= current->next;
        while(N->data != DUMMY){
            //if this element's data is equal to the current element's data, delete it
            if (current->data == N->data){
                //keep cursor pointer positions 
                if (N == beforeCursor){ beforeCursor= beforeCursor->prev;}
                else if (N == afterCursor){ afterCursor= afterCursor->next;}
                //link up nodes and set N to be the next node after deletion
                N->prev->next= N->next;
                N->next->prev= N->prev;
                Node* temp= N->next;
                delete N;
                num_elements--;
                N= temp;
            }else{ //if data does not match, move next
                N= N->next;
            }
        }
    current= current->next;
    }
    //set cursor position to where it should be relative to cursor pointers
    pos_cursor= 0;
    N= frontDummy->next;
    while (N != afterCursor){
        pos_cursor++;
        N= N->next;
    }

}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    List J;
    Node* N = this->frontDummy->next;
    Node* M = L.frontDummy->next;
    while( N->data != DUMMY ){
        J.insertBefore(N->data);
        N = N->next;
    }
    while( M->data != DUMMY ){
        J.insertBefore(M->data);
        M = M->next;
    }
    J.moveFront();
   return J;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    Node* N = nullptr;
    std::string s = "(";
    std::string delim= "";
    for(N=frontDummy->next; N!=backDummy; N=N->next){
        s += delim + std::to_string(N->data);
        delim= ", ";
    }
    return s += ")";
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = ( this->num_elements == R.num_elements );
    N = this->frontDummy->next;
    M = R.frontDummy->next;
    while( eq && N->data != DUMMY){
        eq = (N->data==M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
   if( this != &L ){ // not self assignment
      // make a copy of L
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(pos_cursor, temp.pos_cursor);
      
    }
   // return this with the new data installed
   return *this;
   // the copy, if there is one, is deleted upon return
}
