//-----------------------------------------------------------------------------
// FindPath.c by Antonio Guizar Orozco
// CruzID: aguizaro
// PA2
// This program takes an input file defining a Graph, and source-destination
// ordered pairs, then writes to a given output file the adjacency list
// representation of the Graph as well as the shortest path from each source
// vertex to destination vertex.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

#define INF -100
#define MAXLEN 100

int main(int argc, char * argv[]){
    int vertices, dist;
    FILE *in, *out;
    char linebuffer[MAXLEN]; //line buffer
    Graph G= NULL;
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
        addEdge(G, u, v);
    }
    //print adjacency list of G
    printGraph(out, G);

    // read each line from input file until 0 0 found
    while( fgets(linebuffer, MAXLEN, in) != NULL)  {
        int u, v;
        sscanf(linebuffer, "%d %d", &u, &v);
        //stop reading from input file if 0 0 is reached
        if (u == 0 && v == 0){ break;}
        if (u == 0 || v == 0){
            fprintf(stderr, "%s contains non-positive integer\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        //run BFS on given source vertex
        BFS(G, u);
        //find shortest path from source to destination
        dist= getDist(G, v);
        getPath(L, G, v);
        //print distance and shortest path from source to destination
        if (dist != INF){
            fprintf(out, "\n"); 
            fprintf(out, "The distance from %d to %d is %d\n", u, v, dist);
            fprintf(out, "A shortest %d-%d path is:", u, v);
            printList(out, L);
            fprintf(out, "\n");
        }else{
            fprintf(out, "\n"); 
            fprintf(out, "The distance from %d to %d is infinity\n", u, v);
            fprintf(out, "No %d-%d path exists\n", u, v);
        }
        //clear list
        clear(L);
    }

    //free Graph & List
    freeGraph(&G);
    G = NULL;
    freeList(&L);
    L = NULL;
    // close files 
    fclose(in);
    fclose(out);

   return(0);
}
