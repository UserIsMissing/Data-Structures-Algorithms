/*
Cole Schreiner
caschrei
pa2
Graph.c
*/

#include "List.h"

#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Graph.h"

// structs --------------------------------------------------------------------
// private GraphObj type
typedef struct GraphObj
{
    List *adjLists; // Array of adjacency lists
    int order;      // Number of vertices
    int size;       // Number of edges
    int source;     // Most recently used source vertex
    int *colors;    // Array for BFS coloring
    int *parents;   // Array for storing parent vertices
    int *distances; // Array for storing distances from source
} GraphObj;

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n)
{
    Graph G = malloc(sizeof(struct GraphObj));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    G->adjLists = calloc(n, sizeof(List)); // Allocate array of lists
    // Allocate memory for BFS arrays (will be used later in BFS())
    G->colors = calloc(n, sizeof(int));
    G->parents = calloc(n, sizeof(int));
    G->distances = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) // Will need to compare everything to [u - 1] and [s - 1]
    {
        G->adjLists[i] = newList(); // Initialize each list
        G->colors[i] = WHITE;       // Initialize BFS arrays
        G->parents[i] = NIL;
        G->distances[i] = INF;
    }
    return G;
}

void freeGraph(Graph *pG)
{
    if (pG != NULL && *pG != NULL)
    {
        for (int i = 0; i < (*pG)->order; i++)
        {
            freeList(&(*pG)->adjLists[i]); // Free each list
        }
        free((*pG)->adjLists); // Free array of lists
        free((*pG)->colors);   // Free BFS arrays
        free((*pG)->parents);
        free((*pG)->distances);
        free(*pG); // Free graph object
        *pG = NULL;
    }
}

// Access functions -----------------------------------------------------------
// precondition 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getOrder(Graph G)
{
    if (G == NULL)
    {
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        return NIL;
    }
    return G->order;
}

int getSize(Graph G)
{
    if (G == NULL)
    {
        printf("Graph Error: calling getSize() on NULL Graph reference\n");
        return NIL;
    }
    return G->size;
}

int getSource(Graph G)
{
    if (G == NULL)
    {
        printf("Graph Error: calling getSource() on NULL Graph reference\n");
        return NIL;
    }
    return G->source;
}

int getParent(Graph G, int u)
{
    if (G == NULL)
    {
        printf("Graph Error: calling getParent() on NULL Graph reference\n");
        return NIL;
    }
    if (u < 1 || u > G->order)
    {
        printf("Graph Error: calling getParent() on invalid vertex\n");
        return NIL;
    }
    return G->parents[u - 1];
}

// precondition 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getDist(Graph G, int u)
{
    if (G == NULL)
    {
        printf("Graph Error: calling getDist() on NULL Graph reference\n");
        return NIL;
    }
    if (u < 1 || u > G->order)
    {
        printf("Graph Error: calling getDist() on invalid vertex\n");
        return NIL;
    }
    if (getSource(G) == NIL)
    {
        return INF;
    }
    return G->distances[u - 1];
}

// precondition 1 ≤ 𝑢 ≤ getOrder(𝐺)
void getPath(List L, Graph G, int u)
{
    if (G == NULL)
    {
        printf("Graph Error: calling getPath() on NULL Graph reference\n");
        return;
    }
    if (u < 1 || u > G->order)
    {
        printf("Graph Error: calling getPath() on invalid vertex\n");
        return;
    }
    if (getSource(G) == NIL)
    {
        printf("Graph Error: calling getPath() before BFS()\n");
        return;
    }

    if (u == getSource(G))
    {
        append(L, u);
    }
    else if (getParent(G, u) == NIL)
    {
        append(L, NIL);
    }
    else
    {
        getPath(L, G, getParent(G, u));
        append(L, u);
    }
}

// Manipulation procedues -----------------------------------------------------
void makeNull(Graph G)
{
    if (G == NULL)
    {
        printf("Error: makeNull called on NULL Graph pointer\n");
        return;
    }

    for (int i = 0; i < G->order; i++)
    {
        clear(G->adjLists[i]); // Clear each adjacency list
    }
    G->size = 0;
}

void addEdge(Graph G, int u, int v)
{
    if (G == NULL || u < 1 || u > G->order || v < 1 || v > G->order)
    {
        printf("Error: addEdge called with invalid arguments\n");
        return;
    }
    if (u == v)
    {
        printf("Error: addEdge called with identical arguments\n");
        return;
    }
    
    // Insert edges in sorted order
    moveFront(G->adjLists[u - 1]); // Move to front of adjacency list for u
    while (index(G->adjLists[u - 1]) >= 0 && get(G->adjLists[u - 1]) < v)
    {
        moveNext(G->adjLists[u - 1]); // Move to next vertex in adjacency list
    }
    if (index(G->adjLists[u - 1]) >= 0)
    {
        insertBefore(G->adjLists[u - 1], v); // Insert v before current vertex
    }
    else
    {
        append(G->adjLists[u - 1], v); // Append v to end of adjacency list
    }

    moveFront(G->adjLists[v - 1]); // Move to front of adjacency list for v
    while (index(G->adjLists[v - 1]) >= 0 && get(G->adjLists[v - 1]) < u)
    {
        moveNext(G->adjLists[v - 1]); // Move to next vertex in adjacency list
    }
    if (index(G->adjLists[v - 1]) >= 0)
    {
        insertBefore(G->adjLists[v - 1], u); // Insert u before current vertex
    }
    else
    {
        append(G->adjLists[v - 1], u); // Append u to end of adjacency list
    }

    G->size++;                     // Increment edge count
}

void addArc(Graph G, int u, int v)
{
    if (G == NULL)
    {
        printf("Graph Error: calling addArc() on NULL Graph reference\n");
        return;
    }
    if (u < 1 || u > G->order || v < 1 || v > G->order)
    {
        printf("Error: addArc called with invalid arguments\n");
        return;
    }
    G->size++;                     // Increment edge count
    append(G->adjLists[u - 1], v); // Add v to u's adjacency list (directed edge)
}

void BFS(Graph G, int s)
{
    if (G == NULL)
    {
        printf("Graph Error: calling BFS() on NULL Graph reference\n");
        return;
    }
    if (s < 1 || s > G->order)
    {
        printf("Graph Error: calling BFS() on invalid source vertex\n");
        return;
    }

    G->source = s; // Set source vertex
    for (int i = 0; i < G->order; i++)
    {
        G->colors[i] = WHITE; // Initialize BFS arrays
        G->parents[i] = NIL;
        G->distances[i] = INF;
    }

    G->colors[s - 1] = GRAY; // Set source vertex to gray
    G->distances[s - 1] = 0; // Set source vertex distance to 0
    G->parents[s - 1] = NIL; // Set source vertex parent to NIL

    List queue = newList(); // Create queue
    append(queue, s);       // Enqueue source vertex

    while (length(queue) > 0) // While queue is not empty
    {
        int u = front(queue); // Dequeue vertex u
        deleteFront(queue);
        moveFront(G->adjLists[u - 1]); // Move to front of adjacency list for u
        while (index(G->adjLists[u - 1]) >= 0)
        {
            int v = get(G->adjLists[u - 1]); // Get vertex v from adjacency list
            if (G->colors[v - 1] == WHITE)   // If v is white
            {
                G->colors[v - 1] = GRAY; // Set v to gray
                G->distances[v - 1] = G->distances[u - 1] + 1;
                G->parents[v - 1] = u; // Set v's parent to u
                append(queue, v);      // Enqueue v
            }
            moveNext(G->adjLists[u - 1]); // Move to next vertex in adjacency list
        }
        G->colors[u - 1] = BLACK; // Set u to black
    }
    freeList(&queue); // Free queue
}

// Other operations -----------------------------------------------------------
void printGraph(FILE *out, Graph G)
{
    if (G == NULL)
    {
        printf("Error: printGraph called with NULL Graph pointer\n");
        return;
    }

    for (int i = 1; i <= G->order; i++)
    {
        fprintf(out, "%d: ", i);
        printList(out, G->adjLists[i - 1]);
        // fprintf(out, "\n");
    }
}