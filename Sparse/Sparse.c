//-----------------------------------------------------------------------------
// Sparse.c by Antonio Guizar Orozco
// CruzID: aguizaro
// PA4
// This program takes an input file defining a Matrix A and B, then performs matrix operations
// on the matrices.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

#define MAXLEN 100

int main(int argc, char * argv[]){
    int n, a, b, row, col;
    double val;
    Matrix A, B;
    FILE *in, *out;
    char linebuffer[MAXLEN]; //line buffer
    
    // check command line for correct number of arguments
    if( argc != 3 ){
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    // open files for reading and writing 
    in = fopen(argv[1], "r");
        if( in==NULL ){
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    out = fopen(argv[2], "w");
    if( out==NULL ){
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    char* read= fgets(linebuffer, MAXLEN, in); //read first line of input file
    if (read == NULL){
        fprintf(stderr, "Unable to read first line of %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }else{
        //store first line containing: n, number of a nnz, number of b nnz
        sscanf(linebuffer, "%d %d %d", &n, &a, &b);
        A= newMatrix(n);
        B= newMatrix(n);  
    }
    read= fgets(linebuffer, MAXLEN, in); //ignore empty line

    for (int i=1; i<=a; i++){ //for each nnz in a
        read= fgets(linebuffer, MAXLEN, in);
        if (read == NULL){
            fprintf(stderr, "Unable to read %d line of A from %s\n", i, argv[1]);
            exit(EXIT_FAILURE);
        }else{
            //store row, col, and value of nnz
            sscanf(linebuffer, "%d %d %lf", &row, &col, &val);
            //make new entry in Mattrix A
            changeEntry(A, row, col, val);
        }
    }
    
    read= fgets(linebuffer, MAXLEN, in); //ignore empty line
    for (int j=1; j<=b; j++){ //for each nnz in b
        read= fgets(linebuffer, MAXLEN, in);
        if (read == NULL){
            fprintf(stderr, "Unable to read %d line of B from %s\n", j,  argv[1]);
            exit(EXIT_FAILURE);
        }else{
            //store row, col, and value of nnz
            sscanf(linebuffer, "%d %d %lf", &row, &col, &val);
            //make new entry in Mattrix A
            changeEntry(B, row, col, val);
        }
    }

    //perform and print matrix operations

    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");
    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");
    //(1.5)*A
    fprintf(out, "(1.5)*A =\n");
    Matrix scalarA= scalarMult(1.5, A);
    printMatrix(out, scalarA);
    fprintf(out, "\n");
    //A+B
    fprintf(out, "A+B =\n");
    Matrix sumAB= sum(A,B);
    printMatrix(out, sumAB);
    fprintf(out, "\n");
    //A+A
    fprintf(out, "A+A =\n");
    Matrix sumAA= sum(A,A);
    printMatrix(out, sumAA);
    fprintf(out, "\n");
    //B-A
    fprintf(out, "B-A =\n");
    Matrix diffBA= diff(B,A);
    printMatrix(out, diffBA);
    fprintf(out, "\n");
    //A-A
    fprintf(out, "A-A =\n");
    Matrix diffAA= diff(A,A);
    printMatrix(out, diffAA);
    fprintf(out, "\n");
    //tranpose(A)
    fprintf(out, "Transpose(A) =\n");
    Matrix aT= transpose(A);
    printMatrix(out, aT);
    fprintf(out, "\n");
    //A*B
    fprintf(out, "A*B =\n");
    Matrix prodAB= product(A, B);
    printMatrix(out, prodAB);
    fprintf(out, "\n");
    //B*B
    fprintf(out, "B*B =\n");
    Matrix prodBB= product(B,B);
    printMatrix(out, prodBB);
    fprintf(out, "\n");

    //free Matrix
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&scalarA);
    freeMatrix(&sumAB);
    freeMatrix(&sumAA);
    freeMatrix(&diffBA);
    freeMatrix(&diffAA);
    freeMatrix(&aT);
    freeMatrix(&prodAB);
    freeMatrix(&prodBB);

    // close files 
    fclose(in);
    fclose(out);

   return(0);
}

