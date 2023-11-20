//-----------------------------------------------------------------------------
// Graph.h by Antonio Guizar Orozco
// CruzID: aguizaro
// PA3
// This is the header file for the Graph module.
//-----------------------------------------------------------------------------
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include<stdio.h>
#include"List.h"

#define UNDEF -100
#define NIL 0

/****************************** Exported Type ******************************/
typedef struct GraphObj* Graph;

/****************************** Constructors-Destructors ******************************/

//returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges
Graph newGraph(int n);
// returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G);
// returns a reference to a new graph that is a copy of G.
Graph copyGraph(Graph G);
//frees all heap memory associated with the Graph *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG);


/****************************** Access functions ******************************/

//returns order of G
int getOrder(Graph G);
//returns size of G
int getSize(Graph G);
//will return the parent of vertex u in the DFS tree created by DFS(), or NIL if DFS() has not yet been called
//precondition 1 ≤ u ≤ getOrder(𝐺)
int getParent(Graph G, int u);
//will return the discovery time of the vertex u, or UNDEF if DFS() has not been called
// Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u);
//will return the finish time of the vertex u, or UNDEF if DFS() has not been called
// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u);

/****************************** Manipulation procedures******************************/

//inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u.
//precondition: 1<=u<=n, 1<=v<=n
void addEdge(Graph G, int u, int v);
//inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v)
//precondition: 1<=u<=n, 1<=v<=n 
void addArc(Graph G, int u, int v);
//Function DFS() will perform the depth first search algorithm on G. List S defines the order in which vertices are to be
// processed in the main loop of DFS. Once DFS is complete, it will store the vertices by decreasing finish times (hence 𝑆 is
// considered to be a stack).
// Pre: length(𝑆) == getOrder(G) and S contains some permutation of the integers {1, 2, … , 𝑛} where 𝑛 = getOrder(𝐺) (only 1st pre checked)
void DFS(Graph G, List S);

/****************************** Other operations ******************************/

//prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);


#endif