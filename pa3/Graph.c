/*
Cole Schreiner
caschrei
pa3
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
    // int time;       // Current time
    int *color;    // Array for DFS coloring
    int *parent;   // Array for storing parent vertices
    int *discover; // Array for storing discover times
    int *finish;   // Array for storing finish times
} GraphObj;

// Constructors-Destructors
Graph newGraph(int n)
{
    Graph G = malloc(sizeof(struct GraphObj));
    G->order = n;
    G->size = 0;
    // G->time = UNDEF;
    G->adjLists = calloc(n, sizeof(List)); // Allocate array of lists
    // Allocate memory for DFS arrays (will be used later in DFS())
    G->color = calloc(n, sizeof(int));
    G->parent = calloc(n, sizeof(int));
    G->discover = calloc(n, sizeof(int));
    G->finish = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) // Will need to compare everything to [u - 1] and [s - 1]
    {
        G->adjLists[i] = newList(); // Initialize each list
        G->color[i] = WHITE;       // Initialize DFS arrays
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    return G;
}

void freeGraph(Graph* pG)
{
    if (pG != NULL && *pG != NULL)
    {
        for (int i = 0; i < (*pG)->order; i++)
        {
            freeList(&(*pG)->adjLists[i]); // Free each list
        }
        free((*pG)->adjLists); // Free array of lists
        free((*pG)->color);   // Free DFS arrays
        free((*pG)->parent);
        free((*pG)->discover);
        free((*pG)->finish);
        free(*pG); // Free graph object
        *pG = NULL;
    }
}


// Access functions
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

int getParent(Graph G, int u) /* Pre: 1<=u<=n=getOrder(G) */
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
    return G->parent[u - 1];
}

int getDiscover(Graph G, int u) /* Pre: 1<=u<=n=getOrder(G) */
{
    if (G == NULL)
    {
        printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
        return NIL;
    }
    if (u < 1 || u > G->order)
    {
        printf("Graph Error: calling getDiscover() on invalid vertex\n");
        return NIL;
    }
    return G->discover[u - 1];
}

int getFinish(Graph G, int u) /* Pre: 1<=u<=n=getOrder(G) */
{
    if (G == NULL)
    {
        printf("Graph Error: calling getFinish() on NULL Graph reference\n");
        return NIL;
    }
    if (u < 1 || u > G->order)
    {
        printf("Graph Error: calling getFinish() on invalid vertex\n");
        return NIL;
    }
    return G->finish[u - 1];
}


// Manipulation procedures
void addArc(Graph G, int u, int v) /* Pre: 1<=u<=n, 1<=v<=n */
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
    moveFront(G->adjLists[u - 1]); // Move to front of adjacency list for u
    while (index(G->adjLists[u - 1]) >= 0 && get(G->adjLists[u - 1]) < v)
    {
        moveNext(G->adjLists[u - 1]); // Move to next vertex in adjacency list
    }
    if (index(G->adjLists[u - 1]) >= 0 && get(G->adjLists[u - 1]) == v)
    {
        // u, v already exists
        return;
    }
    if (index(G->adjLists[u - 1]) >= 0)
    {
        insertBefore(G->adjLists[u - 1], v); // Insert v before current vertex
    }
    else
    {
        append(G->adjLists[u - 1], v); // Append v to end of adjacency list
    }
    G->size++; // Increment edge count
}

void addEdge(Graph G, int u, int v) /* Pre: 1<=u<=n, 1<=v<=n */
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

void Visit(Graph G, List S, int x, int *time)
{
    /* 
    pseudo code
    Visit(x)
   d[x] = (++time)          // discover x
   color[x] = gray            
   for all y in adj[x]
      if color[y] == white 
         p[y] = x
         Visit(y)
   color[x] = black 
   f[x] = (++time)          // finish x
     */
    if (G == NULL || S == NULL || time == NULL)
    {
        printf("Graph Error: calling Visit() on NULL Graph reference\n");
        return;
    }
    if (x < 1 || x > G->order)
    {
        printf("Graph Error: calling Visit() with invalid vertex\n");
        return;
    }
    G->color[x - 1] = GRAY; // Set x to gray
    G->discover[x - 1] = ++(*time); // Set discover time for x
    moveFront(G->adjLists[x - 1]); // Move to front of adjacency list for x
    while (index(G->adjLists[x - 1]) >= 0)
    {
        int y = get(G->adjLists[x - 1]); // Get vertex y from adjacency list
        if (G->color[y - 1] == WHITE)
        {
            G->parent[y - 1] = x; // Set y's parent to x
            Visit(G, S, y, time);
        }
        moveNext(G->adjLists[x - 1]); // Move to next vertex in adjacency list
    }
    G->color[x - 1] = BLACK;
    G->finish[x - 1] = ++(*time);
    prepend(S, x);
}

void DFS(Graph G, List S) /* Pre: length(S)==getOrder(G) */
{
/* 
    pseudo code
       for all x in V(G)
      color[x] = white 
      p[x] = nil 
   time = 0
   for all x in V(G)  // main loop of DFS
      if color[x] == white 
         Visit(x)
*/
    if (G == NULL)
    {
        printf("Graph Error: calling DFS() on NULL Graph reference\n");
        return;
    }
    if (length(S) != G->order)
    {
        printf("Graph Error: calling DFS() with invalid List length\n");
        return;
    }

    for (int i = 0; i < G->order; i++)
    {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    int time = 0;
    moveFront(S);
    while (index(S) >= 0)
    {
        int x = get(S);
        if (G->color[x - 1] == WHITE)
        {
            Visit(G, S, x, &time);
        }
        moveNext(S);
    }
    for (int i = 0; i < G->order; i++)
    {
        deleteBack(S);
    }
}


// Other Functions
Graph transpose(Graph G)
{
    if (G == NULL)
    {
        printf("Graph Error: calling transpose() on NULL Graph reference\n");
        return NULL;
    }

    Graph T = newGraph(G->order); // Create new graph object
    for (int i = 0; i < G->order; i++)
    {
        moveFront(G->adjLists[i]); // Move to front of adjacency list for vertex i
        while (index(G->adjLists[i]) >= 0)
        {
            addArc(T, get(G->adjLists[i]), i + 1); // Add arc from vertex i to current vertex
            moveNext(G->adjLists[i]);              // Move to next vertex in adjacency list
        }
    }
    return T;
}

Graph copyGraph(Graph G)
{
    if (G == NULL)
    {
        printf("Graph Error: calling copyGraph() on NULL Graph reference\n");
        return NULL;
    }

    Graph C = newGraph(G->order); // Create new graph object
    for (int i = 0; i < G->order; i++)
    {
        moveFront(G->adjLists[i]); // Move to front of adjacency list for vertex i
        while (index(G->adjLists[i]) >= 0)
        {
            addArc(C, i + 1, get(G->adjLists[i])); // Add arc from vertex i to current vertex
            moveNext(G->adjLists[i]);              // Move to next vertex in adjacency list
        }
    }
    return C;
}

void printGraph(FILE* out , Graph G)
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

