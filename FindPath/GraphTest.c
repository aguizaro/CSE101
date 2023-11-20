//-----------------------------------------------------------------------------
// GraphTest.c by Antonio Guizar Orozco
// CruzID: aguizaro
// PA2
// This program will test the Graph module.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include"Graph.h"
#include"List.h"

int main(){

    Graph G = NULL;
    Graph H= NULL;
    List L= newList();

    // Build graph G 
    G = newGraph(12);
    addEdge(G, 1,3);
    addEdge(G, 1,2);
    addEdge(G, 2,4);
    addEdge(G, 2,5);
    addEdge(G, 5,6);
    addEdge(G, 6,7);
    addEdge(G, 7,8);
    addEdge(G, 6,9);
    addEdge(G, 7,10);
    addEdge(G, 8,11);
    addEdge(G, 3, 12);

    printf("Undirected Graph:\n");
    printGraph(stdout, G);
    printf("\n");
    
    BFS(G, 2);

    getPath(L, G, 12);
    printf("Distance from source: %d to destination: %d = %d\n", getSource(G), 12, getDist(G, 12));
    printf("A %d-%d path is: ", getSource(G), 12);
    printList(stdout, L);
    clear(L);
    printf("\n");

    getPath(L, G, 9);
    printf("Distance from source: %d to destination: %d = %d\n", getSource(G), 9, getDist(G, 9));
    printf("A %d-%d path is: ", getSource(G), 9);
    printList(stdout, L);
    clear(L);
    printf("\n");

    printf("Order: %d\n", getOrder(G));
    printf("Size: %d\n", getSize(G));
    printf("Source: %d\n", getSource(G));

    printf("\n");

    //Build Graph H
    H= newGraph(5);
    addArc(H, 1, 2);
    addArc(H, 2, 3);
    addArc(H, 3, 4);
    addArc(H, 1, 3);

    printf("Directed Graph:\n");
    printGraph(stdout, H);
    printf("\n");

    BFS(H, 1);

    getPath(L, H, 4);
    printf("Distance from source: %d to destination: %d = %d\n", getSource(G), 4, getDist(H, 4));
    printf("A %d-%d path is: ", getSource(H), 4);
    printList(stdout, L);
    clear(L);
    printf("\n");

    getPath(L, H, 5);
    printf("Distance from source: %d to destination: %d = %s\n", getSource(G), 5, "infinity");
    printf("No %d-%d path exists", getSource(H), 5);
    clear(L);
    printf("\n");

    printf("Order: %d\n", getOrder(H));
    printf("Size: %d\n", getSize(H));
    printf("Source: %d\n", getSource(H));
    printf("\n");

    printf("%s\n", (getParent(G, 12) == 3)? "true": "false");
    printf("%s\n", (getParent(G, 6) == 5)? "true": "false");
    printf("%s\n", (getParent(G, 4) == 2)? "true": "false");
    printf("%s\n", (getParent(G, 12) == 3)? "true": "false");
    printf("%s\n", (getParent(H, 4) == 3)? "true": "false");
    printf("%s\n", (getParent(H, 3) == 1)? "true": "false");
    printf("\n");

    makeNull(G);
    printf("NULL Graph with 12 Vertices: \n");
    printGraph(stdout, G);
    printf("\n");

    addArc(H, 4, 5);
    addArc(H, 1, 5);

    printf("Undirected Graph: \n");
    printGraph(stdout, H);
    printf("\n");

    BFS(H, 1);

    getPath(L, H, 5);
    printf("Distance from source: %d to destination: %d = %d\n", getSource(H), 5, getDist(H, 5));
    printf("A %d-%d path is: ", getSource(H), 5);
    printList(stdout, L);
    clear(L);
    printf("\n");

    freeGraph(&G);
    freeGraph(&H);
    freeList(&L);
    return 0;
}

/* CORRECT OUTPUT:
Undirected Graph:
1: 2 3
2: 1 4 5
3: 1 12
4: 2
5: 2 6
6: 5 7 9
7: 6 8 10
8: 7 11
9: 6
10: 7
11: 8
12: 3

Distance from source: 2 to destination: 12 = 3
A 2-12 path is:  2 1 3 12
Distance from source: 2 to destination: 9 = 3
A 2-9 path is:  2 5 6 9
Order: 12
Size: 11
Source: 2

Directed Graph:
1: 2 3
2: 3
3: 4
4: 
5: 

Distance from source: 2 to destination: 4 = 2
A 1-4 path is:  1 3 4
Distance from source: 2 to destination: 5 = infinity
No 1-5 path exists
Order: 5
Size: 4
Source: 1

true
true
true
true
true
true

NULL Graph with 12 Vertices: 
1: 
2: 
3: 
4: 
5: 
6: 
7: 
8: 
9: 
10: 
11: 
12: 

Undirected Graph: 
1: 2 3 5
2: 3
3: 4
4: 5
5: 

Distance from source: 1 to destination: 5 = 1
A 1-5 path is:  1 5 
*/