//-----------------------------------------------------------------------------
// Graph.c by Antonio Guizar Orozco
// CruzID: aguizaro
// PA2
// This is the implementation file for the Graph module.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

#define INF -100
#define NIL 0
#define MAX_VERT 301

//private GraphObj type
typedef struct GraphObj{
    List adj[MAX_VERT]; //ith element is an adjacency list for vertex i
    char color[MAX_VERT]; //ith element is the color of of vertex
    int parent[MAX_VERT]; // ith element is the parent of vertex i
    int distance[MAX_VERT]; // ith element is distance from (most recent) source to vertex i
    int order; //number of vertices in the graph
    int size; // number of edges in the graph
    int source; //label of vertex most recently used as a source for BFS;
} GraphObj;


/****************************** Constructors-Destructors ******************************/

//returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges
Graph newGraph(int n){
    if (n < 1){
        fprintf(stderr, "Graph Error: calling newGraph() with non-positive int argument.\n");
        exit(EXIT_FAILURE);
    }
    Graph G;
    G= malloc(sizeof(GraphObj));
    assert(G!=NULL);
    for(int i=1; i<=n; i++){
        G->adj[i]= newList();
        G->color[i]= 'w'; //set color of vertices to white
        G->parent[i]= NIL;
        G->distance[i]= INF;
    }
    G->order= n; //n vertices
    G->size= 0; //0 edges
    G->source= NIL;
    return G;
}

//frees all heap memory associated with the Graph *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG){
    if (*pG == NULL){
        fprintf(stderr, "Graph Error: calling freeGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    //free each list from the adjacency list
    for (int i=1; i<=(*pG)->order; i++){ freeList(&((*pG)->adj[i]));}
    free(*pG);
    *pG= NULL;
}


/****************************** Access functions ******************************/

//returns order of G
int getOrder(Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}
//returns size of G
int getSize(Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size;

}
//returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called
int getSource(Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getSource() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->source;

}
//will return the parent of vertex u in the BFS tree created by BFS(), or NIL if BFS() has not yet been called
//precondition 1 ≤ u ≤ getOrder(𝐺)
int getParent(Graph G, int u){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1){
        fprintf(stderr, "Graph Error: calling getParent() on u < 1\n");
        exit(EXIT_FAILURE);
    }
    if(u > G->order){
        fprintf(stderr, "Graph Error: calling getParent() on u > getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}
//returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called
////precondition 1 ≤ u ≤ getOrder(𝐺)
int getDist(Graph G, int u){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getDist() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1){
        fprintf(stderr, "Graph Error: calling getDist() on u < 1\n");
        exit(EXIT_FAILURE);
    }
    if(u > G->order){
        fprintf(stderr, "Graph Error: calling getDist() on u > getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    return G->distance[u];
}
//appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists
//precondition: getSource(G)!=NIL, so BFS() must be called before getPath() is called
////precondition: 1 ≤ u ≤ getOrder(𝐺)
void getPath(List L, Graph G, int u){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getPath() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (G->source == NIL){
        fprintf(stderr, "Graph Error: calling getPath() while getSource(G) == NIL\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1){
        fprintf(stderr, "Graph Error: calling getPath() on u < 1\n");
        exit(EXIT_FAILURE);
    }
    if(u > G->order){
        fprintf(stderr, "Graph Error: calling getPath() on u > getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    //recursively find shortest path
    if (u == G->source){
        append(L, G->source);
    }else if (G->parent[u] == NIL){
        append(L, NIL);
    }else{
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}


/********************************* Helper Functions ***************************/

//inserts u to the adjacency list L in the correct vertex label order
static void insertInOrder(List L, int u){
    bool alreadyInserted= false;
    //if adjacency list of u is empty, append new element
    if (length(L) == 0){
        append(L, u);
    }else{ //otherwise insert the new element in correct vertex label order
        //iterate through adj list and insert vertex
        moveFront(L);
        while(index(L) != -1){
            if (get(L) < u){
                moveNext(L);
            }else if (get(L) > u){
                insertBefore(L, u);
                alreadyInserted= true;
                moveBack(L);
                moveNext(L); //make cursor undefined/ break out of loop
            }else{// otherwise, the vertex is already in the list
                alreadyInserted= true;
                moveBack(L);
                moveNext(L);//make cursor undefined/ break out of loop
            }
        }
        //if vertex to be inserted goes at the end of the list, append to back of list
        if (!alreadyInserted) append(L, u);
    }
}


/****************************** Manipulation procedures******************************/

//deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling makeNull() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i=1; i<=G->order; i++){
        //free each list from the adjacency list
        freeList(&(G->adj[i]));
        G->adj[i]= newList();
        G->color[i]= 'w'; //set color of vertices to white
        G->parent[i]= NIL;
        G->distance[i]= INF;
    }
    G->size= 0; //0 edges
    G->source= NIL;

}
//inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u.
//precondition: two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1){
        fprintf(stderr, "Graph Error: calling addEdge() on u < 1\n");
        exit(EXIT_FAILURE);
    }
    if(u > G->order){
        fprintf(stderr, "Graph Error: calling addEdge() on u > getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    if (v < 1){
        fprintf(stderr, "Graph Error: calling addEdge() on v < 1\n");
        exit(EXIT_FAILURE);
    }
    if(v > G->order){
        fprintf(stderr, "Graph Error: calling addEdge() on v > getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    //adds v to the adjcency list of u in the correct vetex label order
    insertInOrder(G->adj[u], v);
    //adds u to the adjcency list of v in the correct vetex label order
    insertInOrder(G->adj[v], u);
    G->size++; //count of edges increases by 1
}
//inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v)
//precondition: two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1){
        fprintf(stderr, "Graph Error: calling addArc() on u < 1\n");
        exit(EXIT_FAILURE);
    }
    if(u > G->order){
        fprintf(stderr, "Graph Error: calling addArc() on u > getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    if (v < 1){
        fprintf(stderr, "Graph Error: calling addArc() on v < 1\n");
        exit(EXIT_FAILURE);
    }
    if(v > G->order){
        fprintf(stderr, "Graph Error: calling addArc() on v > getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    //adds v to the adjcency list of u in the correct vetex label order
    insertInOrder(G->adj[u], v);
    G->size++;//count of edges increases by 1

}
//runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling BFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (s < 1){
        fprintf(stderr, "Graph Error: calling BFS() on souce < 1\n");
        exit(EXIT_FAILURE);
    }
    if(s > G->order){
        fprintf(stderr, "Graph Error: calling BFS() on source > getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    int x, y;
    for(int i= 1; i<=G->order; i++){
        G->color[i]= 'w';
        G->distance[i]= INF;
        G->parent[i]= NIL;
    }
    G->source= s;
    G->color[s]= 'g';
    G->distance[s]= 0;
    G->parent[s]= NIL;
    List L= newList();
    append(L, s); //make a new list and append the source vertex to it
    while(length(L) > 0){ //while the list is not empty
        x= front(L); //set x to be the source vertex
        deleteFront(L); //dequeue the source vertex from the list
        //iterate through adjacency list of x
        for (moveFront(G->adj[x]); index(G->adj[x])!= -1; moveNext(G->adj[x])){
            y= get(G->adj[x]); //set y to the next vertex in the adjacency list of x
            if (G->color[y] == 'w'){ //if y is undiscovered
                G->color[y]= 'g'; //discover y
                G->distance[y]= G->distance[x] + 1; //set distance of y = distance of x +1
                G->parent[y]= x; //set parent of y to be x
                append(L, y); //enqueue y to the list
            }
        }
        G->color[x]= 'b'; //finish x
    }
    freeList(&L);
    L=NULL;

}

/****************************** Other operations ******************************/

//prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling printGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    for(int i= 1; i<=G->order; i++){
        fprintf(out, "%d:", i);
        if (length(G->adj[i]) != 0){
            printList(out, G->adj[i]);
        }else{ //print space to match model outfile if no adj list
            fprintf(out, " ");
        }
        fprintf(out, "\n");
    }
}



