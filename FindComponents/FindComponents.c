//-----------------------------------------------------------------------------
// FindPath.c by Antonio Guizar Orozco
// CruzID: aguizaro
// PA3
// This program takes an input file defining a Graph, and use Depth First Search
// to find the strongly connected components and outputs results to an output file.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

#define MAXLEN 100

int main(int argc, char * argv[]){
    int vertices;
    FILE *in, *out;
    char linebuffer[MAXLEN]; //line buffer
    Graph G= NULL, transposeG= NULL;
    List L= newList();

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

    char* read= fgets(linebuffer, MAXLEN, in);
    if (read == NULL){
        fprintf(stderr, "Unable to read first line of %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }else{
        //make a Graph with given number of vertices
        sscanf(linebuffer, "%d", &vertices);
        G= newGraph(vertices);
    }
    //Add vertices to list by increasing vertex label order
    for (int i= 1; i<= vertices; i++) append(L, i);
    // read each subsequent line from input file until 0 0 found
    while( fgets(linebuffer, MAXLEN, in) != NULL)  {
        int u, v;
        sscanf(linebuffer, "%d %d", &u, &v);
        //stop reading from input file if 0 0 is reached
        if (u == 0 && v == 0){ break;}
        if (u == 0 || v == 0){
            fprintf(stderr, "%s contains non-positive integer\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        addArc(G, u, v);
    }
    //print adjacency list of G
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    DFS(G, L); //run DFS on G
    transposeG= transpose(G); //make transpose graph
    //run DFS on transpose of G using list of vertices
    //ordered by decreasing finish times from the first call.
    DFS(transposeG, L); 
    
    List comp= newList(); //list of parents of each vertex
    bool again= true; //used to indicate another loop execution
    int num_comp= 0, num_sets= 0, num_elements= 0; //number of connected componnets & number of elements in a set 
    //find number of sets of strongly connected components
    for(moveFront(L); index(L) != -1; moveNext(L)){ if (getParent(transposeG, get(L)) == NIL){ num_comp++;}}
    //print number of sets of strongly connected components
    fprintf(out, "G contains %d strongly connected components:\n", num_comp);

    //find strongly connected components
    moveBack(L);
    while (again){
        if (getParent(transposeG, get(L)) == NIL ){ //if vertex is root of a tree in DFS tree
            num_sets++;
            append(comp, get(L));
            num_elements++;
            moveNext(L);
            while (index(L) != -1){
                //append vertex to list of components until a new tree on DFS tree
                append(comp, get(L));
                num_elements++;
                moveNext(L);
            }
            //print out each set of connected components
            fprintf(out, "Component %d: ", num_sets);
            printList(out, comp);
            fprintf(out, "\n");
            //clear list of components
            clear(comp);
             //delete components from list
            for (int i= 0; i<num_elements; i++) deleteBack(L);
            //clear counters
            num_elements= 0;
            if (length(L) > 0) moveBack(L); else again= false; //break out of loop if collected all elements 
        }else{
            movePrev(L);
        }
        if (index(L) == -1) again= false;
    }



    //free Graph & List
    freeGraph(&G);
    freeGraph(&transposeG);
    freeList(&L);
    freeList(&comp);
    // close files 
    fclose(in);
    fclose(out);

   return(0);
}
