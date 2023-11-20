//-----------------------------------------------------------------------------
// Graph.c by Antonio Guizar Orozco
// CruzID: aguizaro
// PA3
// This is the implementation file for the Graph module.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"List.h"
#include"Graph.h"

#define MAX_VERT 1001

//private GraphObj type
typedef struct GraphObj{
    List adj[MAX_VERT]; //ith element is an adjacency list for vertex i
    char color[MAX_VERT]; //ith element is the color of of vertex
    int parent[MAX_VERT]; // ith element is the parent of vertex i
    int discover[MAX_VERT]; // ith element is discover time of vertex i
    int finish[MAX_VERT]; //ith element is the finish time of ith vertex
    int order; //number of vertices in the graph
    int size; // number of edges in the graph
} GraphObj;

/********************************* Helper Functions ***************************/

//inserts u to the adjacency list L in the correct vertex label order
//duplicate values will not be inserted into list
//returns a true on successful insertion, returns false otherwise
static bool insertInOrder(List L, int u){
    //if adjacency list of u is empty, append new element
    if (length(L) == 0){
        append(L, u);
        return true; //return successful insertion
    }else{ //otherwise insert the new element in correct vertex label order
        //iterate through adj list and insert vertex
        moveFront(L);
        while(index(L) != -1){
            if (get(L) < u){
                moveNext(L);
            }else if (get(L) > u){
                insertBefore(L, u);
                moveBack(L);
                moveNext(L); //make cursor undefined/ break out of loop
                return true; //return successful insertion
            }else{// otherwise, the vertex is already in the list
                moveBack(L);
                moveNext(L);//make cursor undefined/ break out of loop
                return false; //return failed insertion
            }
        }
        //if vertex to be inserted goes at the end of the list, append to back of list
        append(L, u);
        return true; //return successful insertion
    }
}
//visit vertex u in graph G, also takes time parameter and stack parameter
static void visit(Graph G, int u, int* t, List* stack){
    List adj_u= G->adj[u];
    int y;
    G->discover[u]= ++(*t);
    G->color[u]= 'g';
    if (length(adj_u) > 0) {moveFront(adj_u);} // if adjacency list is empty, do not iterate
    //iterate through each vertex in the adjacency list of vertex u
    while (index(adj_u) != -1){
        y= get(adj_u); //set y to be the next vertex in the adjacency list of u
        if (G->color[y] == 'w'){ //if y is undiscovered
            G->parent[y]= u; // set y's parent to u
            visit(G, y, t, stack); // visit y
        }
        moveNext(adj_u);
    }
    G->color[u]= 'b';
    G->finish[u]= ++(*t);
    prepend(*stack, u); //push vertex to stack after its finished
}

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
        G->discover[i]= UNDEF;
        G->finish[i]= UNDEF;
    }
    G->order= n; //n vertices
    G->size= 0; //0 edges
    return G;
}
// returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling transpose() with NULL Graph argument.\n");
        exit(EXIT_FAILURE);
    }
    Graph transposeG= newGraph(G->order);
    for (int i= 1; i<= G->order; i++){
        if (length(G->adj[i]) > 0){ moveFront(G->adj[i]);} //only enter while loop if adj list not empty
        while((index(G->adj[i]) != -1)){
            insertInOrder(transposeG->adj[get(G->adj[i])], i); //insert new reverse edge
            moveNext(G->adj[i]);
        }
    }
    return transposeG;
}
// returns a reference to a new graph that is a copy of G.
Graph copyGraph(Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling copyGraph() with NULL Graph argument.\n");
        exit(EXIT_FAILURE);
    }
    Graph newG= malloc(sizeof(GraphObj));
    assert(newG!=NULL);
    for (int i= 1; i<= G->order; i++){
        newG->adj[i]= copyList(G->adj[i]);
        newG->color[i]= 'w';
        newG->parent[i]= NIL;
        newG->discover[i]= UNDEF;
        newG->finish[i]= UNDEF;
    }
    newG->order= G->order; //n vertices
    newG->size= G->size; //G->size edges
    return newG;
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
//will return the discovery time of the vertex u, or UNDEF if DFS() has not been called
// Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getDiscover() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1){
        fprintf(stderr, "Graph Error: calling getDiscover() on u < 1\n");
        exit(EXIT_FAILURE);
    }
    if(u > G->order){
        fprintf(stderr, "Graph Error: calling getDiscover() on u > getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}
//will return the finish time of the vertex u, or UNDEF if DFS() has not been called
// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getFinish() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1){
        fprintf(stderr, "Graph Error: calling getFinish() on u < 1\n");
        exit(EXIT_FAILURE);
    }
    if(u > G->order){
        fprintf(stderr, "Graph Error: calling getFinish() on u > getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
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
        G->discover[i]= UNDEF;
        G->finish[i]= UNDEF;
    }
    G->size= 0; //0 edges

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
    bool success= insertInOrder(G->adj[u], v);
    if (success) G->size++;//count of edges increases by 1 if successfully iserted new vertex label

}
//Function DFS() will perform the depth first search algorithm on G. List S defines the order in which vertices are to be
// processed in the main loop of DFS. Once DFS is complete, it will store the vertices by decreasing finish times (hence 𝑆 is
// considered to be a stack).
// Pre: length(𝑆) == getOrder(G) and S contains some permutation of the integers {1, 2, … , 𝑛} where 𝑛 = getOrder(𝐺) (only 1st pre checked)
void DFS(Graph G, List S){
    int time, element;
    List stack= newList();
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling DFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(S) != G->order){
        fprintf(stderr, "Graph Error: calling DFS() on length(S) != getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    for (int i= 1; i<= G->order; i++){
        G->color[i]= 'w';
        G->parent[i]= NIL;
    }
    time= 0;
    if (length(S) > 0) { moveFront(S);} //if list is empty, do not iterate
    while(index(S) != -1){ //main DFS loop
        element= get(S);
        if (G->color[element] == 'w'){
            visit(G, element, &time, &stack);
        }
        moveNext(S);
    }
    //clear list and make S = stack of vertices ordered by decreasing finish times
    clear(S);
    for (moveFront(stack); index(stack) != -1; moveNext(stack)){ append(S, get(stack));}
    freeList(&stack);
}

/****************************** Other operations ******************************/

//prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling printGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    for(int i= 1; i<=G->order; i++){
        fprintf(out, "%d: ", i);
        if (length(G->adj[i]) != 0){
            printList(out, G->adj[i]);
        }
        fprintf(out, "\n");
    }
}



