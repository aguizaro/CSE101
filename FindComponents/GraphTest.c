//-----------------------------------------------------------------------------
// GraphTest.c by Antonio Guizar Orozco
// CruzID: aguizaro
// PA3
// This program will test the Graph module.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include"Graph.h"
#include"List.h"

int main(){

    List L= newList();
    append(L, 1); append(L, 2); append(L, 3); append(L, 4); append(L, 5); append(L, 6);
    List L2= copyList(L);

    Graph G = newGraph(6);
    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 1, 3);
    addArc(G, 4, 5);
    addArc(G, 5, 6);

    printf("Directed Graph G:\n");
    printGraph(stdout, G);
    printf("\n");
    printf("Vertices: %d\n", getOrder(G));
    printf("Size: %d\n", getSize(G));


    DFS(G, L);

    printf("Stack:");
    printList(stdout, L);
    printf("\n");
    printf("len: %d\n\n", length(L));
    bool outOforder= false;
    moveFront(L);
    int greater= getFinish(G, get(L));
    for(moveNext(L); index(L) != -1; moveNext(L)){
        if (greater < getFinish(G, get(L))) outOforder= true;
    }
    (outOforder)? printf("Stack out of order\n") : printf("Stack in correct order\n");

    moveFront(L2);
    int lower= getDiscover(G, get(L2));
    for (moveNext(L2); index(L2) != -1; moveNext(L2)){
        if ( lower > getDiscover(G, get(L2)) ) outOforder= true;
    }
    (outOforder)? printf("Discover times not in order\n") : printf("Discover times in order\n");


    (getParent(G,1) != NIL)? printf("FALSE\n\n") : printf("TRUE\n\n");

    Graph copyG= copyGraph(G);
    printf("Copy of G:\n");
    printGraph(stdout, copyG);
    printf("\n");

    Graph Gt= transpose(G);
    printf("Transpose of G:\n");
    printGraph(stdout, Gt);
    printf("\n");

    printGraph(stdout, Gt);
    printf("\n");

    addEdge(copyG, 1, 6);
    addArc(G, 1, 6);
    addArc(G, 6, 1);

    printf("G:\n");
    printGraph(stdout, G);
    printf("\n");
    printf("copy G:\n");
    printGraph(stdout, copyG);

    freeList(&L);
    freeList(&L2);
    freeGraph(&G);
    freeGraph(&copyG);
    freeGraph(&Gt);
    return 0;
}

/* CORRECT OUTPUT:
Directed Graph G:
1: 2 3
2: 3
3: 
4: 5
5: 6
6: 

Vertices: 6
Size: 5
Stack: 4 5 6 1 2 3
len: 6

Stack in correct order
Discover times in order
TRUE

Copy of G:
1: 2 3
2: 3
3: 
4: 5
5: 6
6: 

Transpose of G:
1: 
2: 1
3: 1 2
4: 
5: 4
6: 5

1: 
2: 1
3: 1 2
4: 
5: 4
6: 5

G:
1: 2 3 6
2: 3
3: 
4: 5
5: 6
6: 1

copy G:
1: 2 3 6
2: 3
3: 
4: 5
5: 6
6: 1
*/