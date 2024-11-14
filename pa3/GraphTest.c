/*
Cole Schreiner
caschrei
pa3
GraphTest.c
*/

#include <stdio.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"
#include <assert.h>

int main()
{
    // Test newGraph() and getOrder()
    Graph G = newGraph(5);
    assert(getOrder(G) == 5);

    // Test getSize()
    assert(getSize(G) == 0);

    // Test addArc() and addEdge()
    addArc(G, 1, 2);
    addArc(G, 1, 3);
    addArc(G, 2, 4);
    addArc(G, 3, 5);
    addEdge(G, 4, 5);
    assert(getSize(G) == 5);

    // Test DFS()
    List Test1 = newList();
    for (int i = 1; i <= getOrder(G); i++)
    {
        append(Test1, i);
    }
    DFS(G, Test1);

    // Test getParent()
    assert(getParent(G, 1) == NIL);
    assert(getParent(G, 2) == 1);
    assert(getParent(G, 3) == 1);
    assert(getParent(G, 4) == 2);
    assert(getParent(G, 5) == 4);

    // Test getDiscover() and getFinish()
    assert(getDiscover(G, 1) == 1);
    assert(getDiscover(G, 2) == 2);
    assert(getDiscover(G, 3) == 8);
    assert(getDiscover(G, 4) == 3);
    assert(getDiscover(G, 5) == 4);
    assert(getFinish(G, 1) == 10);
    assert(getFinish(G, 2) == 7);
    assert(getFinish(G, 3) == 9);
    assert(getFinish(G, 4) == 6);
    assert(getFinish(G, 5) == 5);

    // Test transpose() and copyGraph()
    Graph T = transpose(G);
    Graph C = copyGraph(G);
    assert(getOrder(T) == 5);
    assert(getOrder(C) == 5);
    assert(getSize(T) == 6);
    assert(getSize(C) == 6);

    // Test printGraph()
    FILE *out = fopen("output.txt", "w");
    printGraph(out, G);
    fclose(out);

    // Free memory
    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);

    printf("All tests passed!\n");

    return 0;
}