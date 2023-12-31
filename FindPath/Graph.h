//-----------------------------------------------------------------------------
// Graph.h by Antonio Guizar Orozco
// CruzID: aguizaro
// PA2
// This is the header file for the Graph module.
//-----------------------------------------------------------------------------
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include<stdio.h>
#include"List.h"

#define INF -100
#define NIL 0

/****************************** Exported Type ******************************/
typedef struct GraphObj* Graph;

/****************************** Constructors-Destructors ******************************/

//returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges
Graph newGraph(int n);
//frees all heap memory associated with the Graph *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG);

/****************************** Access functions ******************************/

//returns order of G
int getOrder(Graph G);
//returns size of G
int getSize(Graph G);
//returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called
int getSource(Graph G);
//will return the parent of vertex u in the BFS tree created by BFS(), or NIL if BFS() has not yet been called
//precondition 1 ≤ u ≤ getOrder(𝐺)
int getParent(Graph G, int u);
//returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called
////precondition 1 ≤ u ≤ getOrder(𝐺)
int getDist(Graph G, int u);
//appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists
//precondition: getSource(G)!=NIL, so BFS() must be called before getPath() is called
////precondition: 1 ≤ u ≤ getOrder(𝐺)
void getPath(List L, Graph G, int u);

/****************************** Manipulation procedures******************************/

//deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G);
//inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u.
//precondition: two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v);
//inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v)
//precondition: two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v);
//runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s);

/****************************** Other operations ******************************/

//prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);


#endif