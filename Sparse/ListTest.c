//-----------------------------------------------------------------------------
// ListTest.c by Antonio Guizar Orozco
// CruzID: aguizaro
// Test client for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = newList();
   char* arr[] = {"one", "two","three", "four", "five", "six", "seven", "eight", "nine", "ten"}; 
   int arr2[10];
   for(int i=0 ; i<10; i++){
      arr2[i]= (i+1)*5;
   }

   // initialize Lists A and B
   for(int i=0; i<10; i++){
      append(A, &arr[i]);
      prepend(B, &arr[i]);
   }

   // print both lists of strings in forward direction
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%s ", *(char**)get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%s ", *(char**)get(B));
   }
   printf("\n");

   //check if lists are reverse of each other
   moveBack(A); moveFront(B);
   while(index(A) != -1 && index(B) != -1){
      if ( *(char**)get(A) != *(char**)get(B) ){
         printf("NOT REVERSED!\n");
         exit(1);
      }
      movePrev(A); moveNext(B);
   }
   printf("REVERSED!\n");
   clear(B);

   moveFront(A);
   int j= 0;
   while(index(A) != -1){
      set(A, &arr2[j]);      
      j++;
      moveNext(A);
   }

   for(moveFront(A);index(A) != -1;moveNext(A)){
      printf("%d ", *(int*)get(A) );
   }
   printf("\n");

   deleteFront(A);
   deleteBack(A);
   deleteBack(A);

   moveFront(A); moveNext(A);
   delete(A);

   moveBack(A); movePrev(A);
   delete(A);

   append(C, &arr2[1]);
   append(C, &arr2[3]);

   moveFront(A); moveNext(A); moveNext(A);
   delete(A);

   moveBack(A); movePrev(A);
   delete(A);

   deleteBack(A);

   for(moveFront(A);index(A) != -1;moveNext(A)){
      printf("%d ", *(int*)get(A) );
   }
   printf("\n");
   for(moveFront(C);index(C) != -1;moveNext(C)){
      printf("%d ", *(int*)get(C) );
   }
   printf("\n");

   moveFront(A);
   insertAfter(A, &arr2[2]);

   moveBack(C);
   insertBefore(C, &arr2[2]);

   if ( *(int*)front(A) != *(int*)front(C)){
      printf("%d, %d\n", *(int*)front(A), *(int*)front(C) );
      exit(2);
   }
   if ( *(int*)back(A) != *(int*)back(C)){
      printf("%d, %d\n", *(int*)back(A), *(int*)back(C) );
      exit(3);
   }
   if (length(A) != length(C)){
      printf("NOT EQUAL\n");
      exit(4);
   }
   printf("EQUAL\n");
   clear(A);
   printf("%d %d\n", length(B), length(A));
   
   freeList(&A);
   freeList(&B);
   freeList(&C);

   return(0);
}

/*
Output of this program:
one two three four five six seven eight nine ten 
one two three four five six seven eight nine ten 
REVERSED!
5 10 15 20 25 30 35 40 45 50 
10 20 
10 20 
EQUAL
-bash-4.2$ make ListTest
gcc -std=c17 -Wall -c -g ListTest.c
gcc -std=c17 -Wall -o ListTest ListTest.o List.o
-bash-4.2$ ListTest
one two three four five six seven eight nine ten 
one two three four five six seven eight nine ten 
REVERSED!
5 10 15 20 25 30 35 40 45 50 
10 20 
10 20 
EQUAL
0 0
*/
