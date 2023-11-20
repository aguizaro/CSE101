//-----------------------------------------------------------------------------
// ListTest.c by Antonio Guizar Orozco
// CruzID: aguizaro
// PA1
// This program will test each operation of the List module.
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = NULL;
   List D= newList();
   int i;

   for(i=1; i<=20; i++){
      append(A,i);
      append(D,i);
      prepend(B,i);
   }

   printf("A: ");
   printList(stdout,A); 
   printf("\n");
   printf("B: ");
   printList(stdout,B); 
   printf("\n");

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
   }
   printf("\n");

   C = copyList(A);
   moveFront(D);
   moveNext(D);
   moveNext(D);
   moveNext(D);
   set(D,99);

   printf("%s\n", equals(A,B)?"true":"false"); //false
   printf("%s\n", equals(B,C)?"true":"false"); //false
   printf("%s\n", equals(C,A)?"true":"false"); //true
   printf("%s\n", equals(D,A)?"true":"false"); //false

   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   insertBefore(A, -1);            // at index 6
   for(i=0; i<9; i++) moveNext(A); // at index 15
   insertAfter(A, -2);
   for(i=0; i<5; i++) movePrev(A); // at index 10

   delete(A);
   printf("A: ");
   printList(stdout,A);
   printf("\n");

   clear(A);
   printf("len A: %d\n", length(A));

   clear(B);
   printf("%s\n", equals(A,B)?"true":"false"); //true

   printf("C: ");
   printList(stdout,C); 
   printf("\n");

   deleteFront(C);
   deleteBack(C);
   printf("C: ");
   printList(stdout,C); 
   printf("\n");
   printf("len C: %d\n", length(C));

   moveFront(C);
   delete(C);
   moveBack(C);
   delete(C);
   printf("C: ");
   printList(stdout,C); 
   printf("\n");
   printf("len C: %d\n", length(C));

   clear(C);
   prepend(C, 19);
   moveBack(C);
   printf("Front element: %d\nBack Element: %d\nCursor Element: %d\n", front(C), back(C), get(C));

   delete(C);
   printList(stdout, C);
   printf("\n");

   printf("len C: %d\n", length(C));

   movePrev(D);
   set(D, -1200);
   printf("D: ");
   printList(stdout, D);
   printf("\n");

   freeList(&A);
   freeList(&B);
   freeList(&C);
   freeList(&D);

   return(0);
}

/*
Output of this program:
A: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
B: 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
false
false
true
false
A: 1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
len A: 0
true
C: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
C: 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
len C: 18
C: 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
len C: 16
Front Element: 19
Back Element: 19:
Cursor Element: 19

len C: 0
D: 1 2 -1200 99 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
*/