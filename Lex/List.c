//-----------------------------------------------------------------------------
// List.c by Antonio Guizar Orozco
// CruzID: aguizaro
// PA1
// This is the implementation file for the List module.
//-----------------------------------------------------------------------------
#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

#define FORMAT "%d"

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
    ListElement data; // ListElement value stored in NodeObj
    Node next; // refers to next node
    Node prev; // refers to previous node
} NodeObj;

//private ListObj type
typedef struct ListObj{
    Node front; //refers to first node
    Node back; // refers to last node
    Node cursor;
    int length; //length of list
    int index; //index of the cursor element
} ListObj;


//------------------------Constructors-Destructors ---------------------------

// Node constructor
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(ListElement data){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data= data;
   N->next= NULL;
   N->prev= NULL;
   return(N);
}

// Node destructor
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// List constructor
// Returns reference to new empty List object.
List newList(){
   List L;
   L = malloc(sizeof(ListObj));
   assert( L!=NULL );
   L->front = L->back = L->cursor= NULL;
   L->length = 0;
   L->index= -1;
   return(L);
}

// List destructor
// Frees all heap memory of List *pL, and sets *pL to NULL.
void freeList(List* pL){
    clear(*pL);
    free(*pL);
    *pL= NULL;
}

//---------------------------Access functions -------------------------------

// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->index;
}

//Returns the number of elements in list
int length(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}
// Returns front element of L. Pre: length()>0
ListElement front(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0){
        fprintf(stderr, "List Error: calling front() while L->length <= 0\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}
// Returns back element of L. Pre: length()>0
ListElement back(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0){
        fprintf(stderr, "List Error: calling back() while L->length <= 0\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}
// Returns cursor element of L. Pre: length()>0, index()>=0
ListElement get(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0){
        fprintf(stderr, "List Error: calling get() while L->length <= 0\n");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0){
        fprintf(stderr, "List Error: calling get() while L->index < 0\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;

}
// Returns true iff Lists A and B are in same state, and returns false otherwise.
// used code from provided Queue.c example on the course webpage
bool equals(List A, List B){
    if (A == NULL || B == NULL){
        fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    //iterate through list and check each list element
    bool eq = ( A->length == B->length );
    Node N = A->front;
    Node M = B->front;
    while( eq && N!=NULL){
        eq = ( N->data==M->data );
        N = N->next;
        M = M->next;
    }
    return eq;
}

//--------------------------Manipulation procedures ----------------------------------

// Resets L to its original empty state.
void clear(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    //while there is a front element in the list, delete it
    while(L->front != NULL){
        deleteFront(L);
    }
    L->cursor= NULL; //remove reference to cursor
}
// Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0
void set(List L, ListElement x){
    if (L == NULL){
        fprintf(stderr, "List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0){
        fprintf(stderr, "List Error: calling set() while L->length <= 0\n");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0){
        fprintf(stderr, "List Error: calling set() while L->index < 0\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data= x;
}
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0){
        L->index= 0;
        L->cursor= L->front;
    }
}
// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0){
        L->index= L->length -1;
        L->cursor= L->back;
    }
}
// If cursor is defined and not at front, move cursor one step toward the 
//front of L; if cursor is defined and at front, cursor becomes undefined; 
//if cursor is undefined do nothing
void movePrev(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->index >= 0){ //if cursor is defined
        if (L->index == 0){ //if cursor is at front
            L->index= -1;// make cursor undefined
            L->cursor= NULL;
        }else{//if cursor is defined and not at front, move it one step towards front
            L->index--;
            L->cursor= L->cursor->prev;
        }
    }
}
// If cursor is defined and not at back, move cursor one step toward the back 
 //of L; if cursor is defined and at back, cursor becomes undefined;
 // if cursor is undefined, do nothing
void moveNext(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->index >= 0){ //if cursor is defined
        if(L->index == L->length -1){//if curser at at the back
            L->index= -1; //make it undefined
            L->cursor= NULL;
        }else{//if the cursor is defined not at the back, move it one step towards back
            L->index++;
            L->cursor= L->cursor->next;
        }
    }
}
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, ListElement x){
    if (L == NULL){
        fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node node= newNode(x);
    //if list is non-empty, insert before first node
    if (L->length > 0){
        node->next= L->front;
        L->front->prev= node; 
        L->front= node;
    //if list is empty, update front and back pointers
    }else{ L->front= L->back = node;}
    L->length++; //increment length of list by 1
    //update cursor index if its defined
    if (L->index >= 0){ L->index++;}
}
// Insert new element into L. If L is non-empty, insertion takes place 
// after back element.
void append(List L, ListElement x){
    if (L == NULL){
        fprintf(stderr, "List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node node= newNode(x); //create new node to be inserted
    //if list was not empty insert after last node
    if (L->length > 0){
        node->prev= L->back;
        L->back->next= node;
        L->back= node;
    //if list was empty, update front and back pointers
    }else{ L->front = L->back = node;}
    L->length++;//increment length of list by 1

}
// Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, ListElement x){
    if (L == NULL){
        fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0){
        fprintf(stderr, "List Error: calling insertBefore() while L->length <= 0\n");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0){
        fprintf(stderr, "List Error: calling insertBefore() while L->index < 0\n");
        exit(EXIT_FAILURE);
    }
    Node node= newNode(x);
    node->next= L->cursor;
    node->prev= L->cursor->prev;
    //if cursor is on first element
    if(L->index == 0){ L->front= node;}// update front element
    //if cursor is not on first element
    //update cursor's previous node's next to point to new node
    else{ L->cursor->prev->next= node;}
    L->cursor->prev= node;
    L->index++; //increment index of cursor by 1
    L->length++; //increment length of list by 1

}
// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, ListElement x){
    if (L == NULL){
        fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0){
        fprintf(stderr, "List Error: calling insertAfter() while L->length <= 0\n");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0){
        fprintf(stderr, "List Error: calling insertAfter() while L->index < 0\n");
        exit(EXIT_FAILURE);
    }
    Node node= newNode(x);
    node->next= L->cursor->next;
    node->prev= L->cursor;
    //if cursor is at the back, update back node after insertion.
    if (L->index == L->length -1){ L->back= node;} 
    //if cursor is not at back, set it's next node's previous to be the new node
    else{ L->cursor->next->prev= node;}
    L->cursor->next= node;
    L->length++; //increment length of list by 1
}
// Delete the front element. Pre: length()>0
void deleteFront(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0){
        fprintf(stderr, "List Error: calling deleteFront() while L->length <= 0\n");
        exit(EXIT_FAILURE);
    }
    //if list only has one element
    if (L->length == 1){
        freeNode(&(L->front));
        L->front = L->back = L->cursor= NULL;
        L->index= -1;
    }else{ // if list has more than one element
        L->front= L->front->next;
        freeNode(&(L->front->prev));
        L->front->prev= NULL;
    }
    L->length--;
    if (L->index >= 0){ L->index--;} //update cursor index if it is defined

}
// Delete the back element. Pre: length()>0
void deleteBack(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0){
        fprintf(stderr, "List Error: calling deleteBack() while L->length <= 0\n");
        exit(EXIT_FAILURE);
    }
    //if there is only one element in the list
    if (L->length == 1){//remove it and update front & back pointers to NULL
        freeNode(&(L->front));
        L->front = L->back = L->cursor= NULL;
        L->index= -1;
    }else{ //if there is more than one element in the list
        L->back= L->back->prev;
        freeNode(&(L->back->next));
        L->back->next= NULL;
    }
    //if cursor is on the last element in list, update it to be undefined
    if (L->index == L->length-1){ 
        L->index= -1;
        L->cursor= NULL;
    }
    L->length--; 
}
// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0){
        fprintf(stderr, "List Error: calling delete() while L->length <= 0\n");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0){
        fprintf(stderr, "List Error: calling delete() while L->index < 0\n");
        exit(EXIT_FAILURE);
    }
    //if only 1 element in list
    if (L->length == 1){
        deleteFront(L);
    }else{
        //if element to be deleted is at the front of list
        if(L->cursor->prev == NULL){ 
            L->cursor->next->prev= NULL;
            L->front= L->cursor->next; //update pointer to front element

        //if cursor to be deleted is at the back of the list
        }else if(L->cursor->next == NULL){ 
            L->cursor->prev->next= NULL;
            L->back= L->cursor->prev; //update pointer to back element

        //if element to be deleted is between 2 other elements
        }else{
            L->cursor->prev->next= L->cursor->next;
            L->cursor->next->prev= L->cursor->prev;
        }
        //free node and update list properties
        freeNode(&(L->cursor));
        L->index= -1;
        L->length--;
        L->cursor= NULL;
    }
}

//-----------------------------Other operations ------------------------------

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L){
    Node N = NULL;
    if( L==NULL ){
        fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    for(N = L->front; N != NULL; N = N->next){
        fprintf(out, FORMAT" ", N->data);
    }
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
    Node N= NULL;
    List newL= newList();
    for (N= L->front; N != NULL; N=N->next){
        append(newL, N->data);
    }
    return newL;

}