//-----------------------------------------------------------------------------
// Lex.c by Antonio Guizar Orozco
// CruzID: aguizaro
// PA1
// This program will take an input file and use the List ADT in order to output
// the lines sorted in lexicographical order to the output file specified.
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){
    int line_count= 0;
    FILE *in, *out;
    char linebuffer[MAX_LEN]; // line buffer
    char** lines= NULL; //string array of lines
    List L= newList(); //List object
    append(L,0);

    // check command line for correct number of arguments
    if( argc != 3 ){
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    // open files for reading and writing 
    in = fopen(argv[1], "r");
        if( in==NULL ){
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    out = fopen(argv[2], "w");
    if( out==NULL ){
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // read each line of input file
    while( fgets(linebuffer, MAX_LEN, in) != NULL)  {
        line_count++;
        char** temp = realloc(lines, line_count * sizeof(char *)); // Reallocate memory for array of lines
        if (temp == NULL){
            fprintf(stderr, "Error: Could not allocate memory.\n");
            exit(EXIT_FAILURE);
        }
        lines= temp; //assign new memory to array pointer;
        lines[line_count-1] = malloc((strlen(linebuffer)+1) * sizeof(char)); // Allocate memory for new line
        if (lines[line_count-1] == NULL){
            fprintf(stderr, "Error: Could not allocate memory.\n");
            exit(EXIT_FAILURE);
        }
        strcpy(lines[line_count-1], linebuffer); // Copy line to array
    }

   //indirectly sort lines into list using insertion sort algorithm from CLRS 2.1
    bool already_inserted= false;
    for (int i= 1; i < line_count; i++){
        already_inserted= false;
        moveBack(L);
        int j= i-1;
        char* key= lines[i];
        while (j >= 0){
            //if line at j should come after line at i
            if(strcmp(lines[j],key) > 0){
                if (index(L) == 0){ //if cursor is at front of list
                    insertBefore(L, i);
                    already_inserted= true;
                }else{
                    movePrev(L); // move cursor toward front by 1
                }
            }
            j--;
        }
        //insert index of sorted line if cursor is defined
        if (!already_inserted){ insertAfter(L,i);}
    }
    //iterate through the List
    moveFront(L);
    while(index(L) != -1){
        //print array in lex order using elements from L as indices
        fprintf(out, "%s", lines[get(L)]);
        moveNext(L);
    }
    //free list
    freeList(&L); 
    // Free memory allocated for array of lines
    for(int i=0; i<line_count; i++){ free(lines[i]);}
    free(lines);
    lines= NULL;
    
    // close files 
    fclose(in);
    fclose(out);

   return(0);
}