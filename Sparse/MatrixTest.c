//-----------------------------------------------------------------------------
// MatrixTest.c by Antonio Guizar Orozco
// CruzID: aguizaro
// Test client for Matrix ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Matrix.h"

int main(int argc, char* argv[]){

    Matrix M= newMatrix(3);
    makeZero(M);
    changeEntry(M, 1, 1, 6); changeEntry(M, 1, 1, 6);
    changeEntry(M, 1, 2, 5); changeEntry(M, 1, 2, 0);
    changeEntry(M, 3, 3, 9);

    printf("M is a %dx%d matrix\n", size(M),size(M));
    printf("M has %d non-zero entries\n", NNZ(M));

    Matrix M2= copy(M);

    printf("M2 is a %dx%d matrix\n", size(M2),size(M2));
    printf("M2 has %d non-zero entries\n", NNZ(M2));

    Matrix M3= transpose(M);
    Matrix M4= transpose(M2);
    Matrix M5= transpose(M3);

    (equals(M, M2))? printf("EQUAL\n"): printf("NOT EQUAL\n");
    (equals(M3, M4))? printf("EQUAL\n"): printf("NOT EQUAL\n");
    (equals(M, M5))? printf("EQUAL\n"): printf("NOT EQUAL\n");

    Matrix scalarM2= scalarMult(0.5, M2);
    changeEntry(M2, 1,1,3);
    changeEntry(M2, 3, 3, 4.5);

    (equals(M2, scalarM2))? printf("EQUAL\n"): printf("NOT EQUAL\n");

    changeEntry(M, 1, 3, 10);

    Matrix sum1= sum(M, M3);
    Matrix sum2= newMatrix(size(M2));
    changeEntry(sum2, 1,1,12); changeEntry(sum2, 1,3,10); changeEntry(sum2, 3, 3, 18);

    (equals(sum1, sum2))? printf("EQUAL\n"): printf("NOT EQUAL\n");

    Matrix A= newMatrix(4);
    Matrix B= newMatrix(4);

    changeEntry(A, 1,1,1); changeEntry(A, 1,4,2);
    changeEntry(A, 4,1,7); changeEntry(A, 4,4,8);

    changeEntry(B, 2,1,3); changeEntry(B, 2,4,4);
    changeEntry(B, 3,1,5); changeEntry(B, 3,4,6);

    Matrix C= sum(A,B);
    Matrix copyC= copy(C);

    printMatrix(stdout, C);

    Matrix D= diff(C,copyC);
    printf("D has %d nnz\n", NNZ(D));
    makeZero(A);
    printf("A has %d nnz\n", NNZ(A));
    Matrix prod= product(A,B);
    printf("prod has %d nnz\n", NNZ(prod));
   
    printMatrix(stdout, prod);

    freeMatrix(&M);
    freeMatrix(&M2);
    freeMatrix(&M3);
    freeMatrix(&M4);
    freeMatrix(&M5);
    freeMatrix(&scalarM2);
    freeMatrix(&sum1);
    freeMatrix(&sum2);
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&copyC);
    freeMatrix(&D);
    freeMatrix(&prod);
    
    return 0;
}