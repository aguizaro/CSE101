//-----------------------------------------------------------------------------
// Matrix.c by Antonio Guizar Orozco
// CruzID: aguizaro
// PA4
// This is the implementation file for the Matrix module.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"Matrix.h"
#include"List.h"

#define MAX_ROWS 10000001

// private Entry type
typedef struct EntryObj* Entry;

// private EntryObj type
typedef struct EntryObj{
    int col_index;
    double value;
} EntryObj;

typedef struct MatrixObj{
    List entries[MAX_ROWS];
    int size, nnz;
} MatrixObj;

// ------------------------- Constructor / Destructor --------------------------------

// Entry constructor
// Returns reference to new Entry object. Initializes data fields.
Entry newEntry(int col, double val){
   Entry E = malloc(sizeof(EntryObj));
   assert( E!=NULL );
   E->col_index= col;
   E->value= val;
   return(E);
}

// Entry destructor
// Frees heap memory pointed to by *pN, sets *pE to NULL.
void freeEntry(Entry* pE){
   if( pE!=NULL && *pE!=NULL ){
      free(*pE);
      *pE = NULL;
   }
}

// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
    Matrix M;
    M = malloc(sizeof(MatrixObj));
    assert( M!=NULL );
    M->size= n;
    M->nnz= 0;
    for (int i=1; i<=n; i++){
        M->entries[i]= NULL;
    }
    return(M);
}

// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    if (*pM == NULL){
        fprintf(stderr, "Matrix Error: calling freeMatrix() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    makeZero(*pM);
    free(*pM);
    *pM= NULL;
}

// ------------------------ Access functions ----------------------------------------

// Return the size of square Matrix M.
int size(Matrix M){
    if (M == NULL){
        fprintf(stderr, "Matrix Error: calling size() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    return M->size;
}

// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    if (M == NULL){
        fprintf(stderr, "Matrix Error: calling NNZ() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    return M->nnz;
}

// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if (A == NULL || B == NULL){
        fprintf(stderr, "Matrix Error: calling equals() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if ( (A->size != B->size) || (A->nnz != B->nnz) ) return 0;
    if (A == B){ return 1;} //return true if A and B point to the same Matrix
    List currentRow_A, currentRow_B;
    //iterate through both Matricies non-zero entries
    for(int i=1; i<=A->size; i++){
        currentRow_A= A->entries[i];
        currentRow_B= B->entries[i]; 
        if( (currentRow_A != NULL)  && (currentRow_B != NULL)){
            moveFront(currentRow_A); moveFront(currentRow_B);
            while( (index(currentRow_A) != -1) || (index(currentRow_B) != -1)) {
                Entry a= (Entry)get(currentRow_A);
                Entry b= (Entry)get(currentRow_B);
                //return false if entries don't match
                if( (a->col_index != b->col_index) || (a->value != b->value)){ return 0;}
                moveNext(currentRow_A); moveNext(currentRow_B);
            }
        //return false if only one of the rows is NULL
        }else if(currentRow_A != currentRow_B){ return 0;}
    }
    //return true if everything matches
    return 1;
}

// ------------------------- Helper Functions ----------------------------------------

//inserts entry e to the list L in the correct column index order
//if there is a non-zero entry in the jth column of the list, entry is not inserted
static bool insertInOrder(List L, Entry e){
    if (L == NULL){
        fprintf(stderr, "Matrix Error: calling insertInOrder() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    //if list is empty, append entry
    if (length(L) == 0){
        append(L, e);
        return true; //return successful insertion
    }else{ //otherwise insert the enrty in correct column index order
        moveFront(L);
        while(index(L) != -1){
            if (((Entry)get(L))->col_index < e->col_index){
                moveNext(L);
            }else if (((Entry)get(L))->col_index > e->col_index){
                insertBefore(L, e);
                moveBack(L);
                moveNext(L); //make cursor undefined/ break out of loop
                return true; //return successful insertion
            }else{// otherwise, the jth index in the list alredy has a non-zero entry
                moveBack(L);
                moveNext(L);//make cursor undefined/ break out of loop
                return false; //return failed insertion
            }
        }
        //if entry to be inserted goes at the end of the list, append to back of list
        append(L, e);
        return true; //return successful insertion
    }
}

//compute the vector dot product of 2 matrix rows represented as Lists
double vectorDot(List P, List Q){
    if (P == NULL || Q == NULL){
        fprintf(stderr, "Matrix Error: calling vectorDot() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    double result= 0;
    moveFront(P); moveFront(Q);
    while ((index(P) != -1) && (index(Q) != -1)){
        Entry entry_p= (Entry)get(P);
        Entry entry_q= (Entry)get(Q);
        if (entry_p->col_index < entry_q->col_index){ moveNext(P);}
        else if (entry_q->col_index < entry_p->col_index){ moveNext(Q);}
        else if (entry_p->col_index == entry_q->col_index){ 
            result += entry_p->value * entry_q->value;
            moveNext(P); moveNext(Q);
        }
    }
    return result;
}

//compute the sum of vector A and B represented as Lists of Entries
//takes in a sumMatrix as parameter in order to incrememnt the NNZ field
List vectorSum(Matrix M, List A, List B){
    if (A == NULL || B == NULL){
        fprintf(stderr, "Matrix Error: calling vectorSum() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    List sum= newList();
    moveFront(A); moveFront(B);
    while ((index(A) != -1) && (index(B) != -1)){
        Entry entry_A= (Entry)get(A);
        Entry entry_B= (Entry)get(B);
        if (entry_A->col_index < entry_B->col_index){
            Entry copy_A= newEntry(entry_A->col_index, entry_A->value);
            append(sum, copy_A);
            M->nnz++;
            moveNext(A);
        }
        else if (entry_B->col_index < entry_A->col_index){
            Entry copy_B= newEntry(entry_B->col_index, entry_B->value);
            append(sum, copy_B);
            M->nnz++;
            moveNext(B);
        }
        else if (entry_A->col_index == entry_B->col_index){
            double entry_sum= entry_A->value + entry_B->value;
            if ( entry_sum != 0){
                Entry sumEntry= newEntry(entry_A->col_index, entry_sum);
                append(sum, sumEntry);
                M->nnz++;
            }
            moveNext(A); moveNext(B);
        }
    }//if A still has more entries, append them to sum vector
    while (index(A) != -1){
        Entry entry_A= (Entry)get(A);
        Entry copy_A= newEntry(entry_A->col_index, entry_A->value);
        append(sum, copy_A);
        M->nnz++;
        moveNext(A);
    }//If B still has more entries, append them to sum vector
    while (index(B) != -1){
        Entry entry_B= (Entry)get(B);
        Entry copy_B= newEntry(entry_B->col_index, entry_B->value);
        append(sum, copy_B);
        M->nnz++;
        moveNext(B);
    }
    //if sum vector is a zero vector, return NULL
    if (length(sum) == 0){ 
        freeList(&sum);
        return NULL;
    }
    return sum;
} 

// ------------------------ Manipulation procedures ---------------------------------

// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
    if (M == NULL){
        fprintf(stderr, "Matrix Error: calling makeZero() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i= 1; i<=M->size; i++){ 
         //if the ith row has a list
        if (M->entries[i] != NULL){ 
            //free each entry in the list
            for(moveFront(M->entries[i]); index(M->entries[i]) != -1; moveNext(M->entries[i])){
                Entry e= (Entry)get(M->entries[i]);
                freeEntry(&e);
            } //then free the list itself
            freeList(&(M->entries[i]));
        }
    }
    M->nnz= 0; //reset number of non-zero entries to 0
}

// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    if (M == NULL){
        fprintf(stderr, "Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (i > M->size){
        fprintf(stderr, "Matrix Error: calling changeEntry() on i > size(M)\n");
        exit(EXIT_FAILURE);
    }
    if (i < 1){
        fprintf(stderr, "Matrix Error: calling changeEntry() on i < 1\n");
        exit(EXIT_FAILURE);
    }
    if (j > M->size){
        fprintf(stderr, "Matrix Error: calling changeEntry() on j > size(M)\n");
        exit(EXIT_FAILURE);
    }
    if (j < 1){
        fprintf(stderr, "Matrix Error: calling changeEntry() on j < 1\n");
        exit(EXIT_FAILURE);
    }
    //handle x= 0 case
    if (x == 0){
        //if there exists a non-zero entry in this row, check the column index
        if (M->entries[i] == NULL) return;
        List currentRow= M->entries[i];
        for(moveFront(currentRow); index(currentRow) != -1; moveNext(currentRow)){
            Entry currentEntry= (Entry)get(currentRow);
            //if there is a non-zero entry to be removed, remove it
            if (currentEntry->col_index == j){
                freeEntry(&currentEntry);
                M->nnz--;
                delete(currentRow);
            }
        }
        //if the row contains an empty list after removing entry, free the list
        if (length(currentRow) == 0){ freeList(&(M->entries[i])); M->entries[i]= NULL;}
        return;
    }

    List row= M->entries[i];
    //if row has no non-zero entries, make a new list and new entry for that list, then append entry to list & update nnz.
    if (row == NULL){
        M->entries[i]= newList();
        row= M->entries[i];
        Entry newE= newEntry(j, x);
        append(row, newE);
        M->nnz++;
        return; //exit function
    }
    for (moveFront(row); index(row) != -1; moveNext(row)){
        //if ith row and jth column has a non-zero entry, change its value to x
        if (((Entry)get(row))->col_index == j){
            ((Entry)get(row))->value= x;
            return; //exit function after changing value of entry
        }
    }
    //if the ith row and jth col is a zero, make a new entry and insert it to row(list) in increasing column index order
    Entry newE= newEntry(j, x);
    insertInOrder(row, newE);
    //increment number of non-zero entries if changed zero entry to non-zero
    M->nnz++;
}

// ----------------------- Matrix Arithmetic operations --------------------------------------

// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    if (A == NULL){
        fprintf(stderr, "Matrix Error: calling copy() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix copyA= newMatrix(A->size);
    for (int i= 1; i<= A->size; i++){
        if (A->entries[i] != NULL){
            //iterate through each list
            for(moveFront(A->entries[i]); index(A->entries[i]) != -1; moveNext(A->entries[i])){
                //make a new entry using members from A's current entry
                Entry newE= newEntry(((Entry)get(A->entries[i]))->col_index,((Entry)get(A->entries[i]))->value);
                if (copyA->entries[i] == NULL){ copyA->entries[i]= newList();}
                append(copyA->entries[i], newE); //don't need to use InsertInOrder b/c A's rows are already in correct order
                copyA->nnz++;
            }
        }
    }
    return copyA;
}

// Returns a reference to a new Matrix object representing the transpose of A.
Matrix transpose(Matrix A){
    if (A == NULL){
        fprintf(stderr, "Matrix Error: calling transpose() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix aT= newMatrix(A->size);
    List currentRow= NULL, transposeRow= NULL;
    Entry currentEntry, transposeEntry;
    int columnIndex;

    for(int i= 1; i<=A->size; i++){
        currentRow= A->entries[i];
        if (currentRow != NULL){
            for(moveFront(currentRow); index(currentRow) != -1; moveNext(currentRow)){
                currentEntry= (Entry)get(currentRow);
                columnIndex= currentEntry->col_index;
                transposeRow= aT->entries[columnIndex];
                //make a new entry with col_index= currentRow_index, value= currentEntry->value
                transposeEntry= newEntry(i, currentEntry->value);
                //if the transpose matrix at row = columnIndex is NULL, make a new list
                if (transposeRow == NULL){ 
                    aT->entries[columnIndex] = newList();
                    transposeRow= aT->entries[columnIndex];
                }
                //insert the new transposeEntry into the transpose matrix
                append(transposeRow, transposeEntry);
            }
        }
    }
    aT->size= A->size;
    aT->nnz= A->nnz;
    return aT;
}

// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    if (A == NULL){
        fprintf(stderr, "Matrix Error: calling scalarMult() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix scalarM= newMatrix(A->size);
    if (x == 0){ return scalarM;} //return zero Matrix if scalar is zero

    List currentRow, scalarRow;
    Entry currentEntry;
    for(int i=1; i<=A->size; i++){
        currentRow= A->entries[i];
        scalarRow= scalarM->entries[i];
        if (currentRow != NULL){
            for(moveFront(currentRow); index(currentRow) != -1; moveNext(currentRow)){
                currentEntry= (Entry)get(currentRow);
                //copy each entry->value * x to the new matrix
                Entry scalarEntry= newEntry(currentEntry->col_index, currentEntry->value*x);
                if (scalarRow == NULL){
                    scalarM->entries[i]= newList();
                    scalarRow= scalarM->entries[i];
                }
                append(scalarRow, scalarEntry);
                scalarM->nnz++;
            }
        }
    }
    return scalarM;
}

// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    if (A == NULL || B == NULL){
        fprintf(stderr, "Matrix Error: calling sum() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size){
        fprintf(stderr, "Matrix Error: calling sum() on size(A) != size(B)\n");
        exit(EXIT_FAILURE);
    }
    if (A == B){ //if A and B point to the same Matrix
       return scalarMult(2, A);
    }

    Matrix M= newMatrix(A->size);
    for(int i=1; i<=A->size; i++){
        List row_A= A->entries[i];
        List row_B= B->entries[i];
        List out= M->entries[i];
        //if there is a non-zero value in both A's row and B's row, check entries
        if( (row_A != NULL) && (row_B != NULL)){
            M->entries[i]= vectorSum(M, row_A, row_B);
        }else if (row_A != NULL) {
            M->entries[i]= newList();
            out= M->entries[i];
            for (moveFront(row_A); index(row_A) != -1; moveNext(row_A)){
                //append all entries in row_A to row of sum matrix
                Entry entry_A= (Entry)get(row_A);
                Entry newE= newEntry(entry_A->col_index, entry_A->value);
                append(out, newE);
                M->nnz++;
            }    
        }else if (row_B != NULL) {
            M->entries[i]= newList();
            out= M->entries[i];
            for (moveFront(row_B); index(row_B) != -1; moveNext(row_B)){
                //append all entries in row_B to row of sum matrix
                Entry entry_B= (Entry)get(row_B);
                Entry newE= newEntry(entry_B->col_index, entry_B->value);
                append(out, newE);
                M->nnz++;
            }    
        }
    }
    return M; //return sum matrix
}

// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    if (A == NULL || B == NULL){
        fprintf(stderr, "Matrix Error: calling diff() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size){
        fprintf(stderr, "Matrix Error: calling diff() on size(A) != size(B)\n");
        exit(EXIT_FAILURE);
    }

    Matrix tempB= scalarMult(-1,  B);
    Matrix diffM= sum(A, tempB);

    freeMatrix(&tempB);
    
    return diffM; //return diff matrix
}

// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    if (A == NULL || B == NULL){
        fprintf(stderr, "Matrix Error: calling product() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size){
        fprintf(stderr, "Matrix Error: calling product() while size(A) != size(B)\n");
        exit(EXIT_FAILURE);
    }
    double result= 0;
    Matrix BT= transpose(B);
    Matrix prod= newMatrix(A->size);
    for (int i= 1; i<= A->size; i++){
        for (int j= 1; j<= BT->size; j++){
            //if row_A and col_B both have non-zero value(s)
            if ( (A->entries[i] != NULL) && (BT->entries[j] != NULL) ){
                //if product matrix row is NULL, make a new list
                if (prod->entries[i] == NULL){ prod->entries[i]= newList();}
                result= vectorDot(A->entries[i], BT->entries[j]);
                if (result != 0){
                    Entry dotProductEntry= newEntry(j, result);
                    insertInOrder(prod->entries[i], dotProductEntry);
                    prod->nnz++;
                }
            }
        }
        //if row of product Matrix has no non-zero elements, free the list
        if(prod->entries[i] != NULL){
            if (length(prod->entries[i]) == 0){ freeList(&(prod->entries[i]));}
        }
    }
    freeMatrix(&BT);
    return prod;
}

// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    if (M == NULL){
        fprintf(stderr, "Matrix Error: calling printMatrix() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    for(int i=1; i<=M->size; i++){
        if(M->entries[i] != NULL){
            fprintf(out, "%d: ", i);
            for(moveFront(M->entries[i]); index(M->entries[i]) != -1; moveNext(M->entries[i])){
                Entry e= (Entry)get(M->entries[i]);
                fprintf(out, "(%d, %0.1f) ", e->col_index, e->value);
            }
            fprintf(out, "\n");
        }
    }

}