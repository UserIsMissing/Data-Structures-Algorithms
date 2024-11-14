/*
Cole Schreiner
caschrei
pa2
Graph.h
*/

#ifndef GRAPH_H
#define GRAPH_H

#include "List.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NIL -1
#define INF -2

typedef struct GraphObj *Graph;

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n);
void freeGraph(Graph* pG);

// Access functions -----------------------------------------------------------
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

// Manipulation procedues -----------------------------------------------------
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

// Other operations -----------------------------------------------------------
void printGraph(FILE* out, Graph G);

#endif // GRAPH_H