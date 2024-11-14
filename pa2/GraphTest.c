/*
Cole Schreiner
caschrei
pa2
GraphTest.c
*/

#include <stdio.h>
#include <stdbool.h>
#include "Graph.h"

int main()
{
    // Test newGraph() and getOrder()
    Graph G = newGraph(5);
    printf("Order of G: %d\n", getOrder(G)); // Expected output: 5

    // Test getSize()
    printf("Size of G: %d\n", getSize(G)); // Expected output: 0

    // Test addEdge() and getSize()
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    printf("Size of G: %d\n", getSize(G)); // Expected output: 4

    // Test addArc() and getSize()
    addArc(G, 5, 1);
    addArc(G, 4, 3);
    printf("Size of G: %d\n", getSize(G)); // Expected output: 6

    // Test getSource()
    printf("Source of G: %d\n", getSource(G)); // Expected output: -1

    // Test BFS(), getSource(), getParent(), getDist(), and getPath()
    BFS(G, 1);
    printf("Source of G: %d\n", getSource(G)); // Expected output: 1
    printf("Parent of vertex 2: %d\n", getParent(G, 2)); // Expected output: 1
    printf("Distance of vertex 3: %d\n", getDist(G, 3)); // Expected output: 2

    List path = newList();
    getPath(path, G, 5);
    printf("Path from vertex 1 to 5: ");
    printList(stdout, path); // Expected output: 1 2 3 4 5
    printf("\n");

    freeList(&path);
    freeGraph(&G);

    return 0;
}