/*
Cole Schreiner
caschrei
pa3
FindComponents.c
*/


#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 300
//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    //-----------------------------------------------------------------------------
    // Check command line arguments
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //-----------------------------------------------------------------------------
    // Open files for reading and writing
    FILE *fileIN = fopen(argv[1], "r");
    if (fileIN == NULL)
    {
        fprintf(stderr, "Unable to open file %s for reading", argv[1]);
        exit(EXIT_FAILURE);
    }
    FILE *fileOUT = fopen(argv[2], "w"); // Open the output file in write mode
    if (fileOUT == NULL)
    {
        fprintf(stderr, "Error opening output file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    //-----------------------------------------------------------------------------
    // Start getting lines
    char Vert[MAX_LENGTH]; // Vertex lines
    int graph_size = 0; // Number of vertices
    int x, y;
    if (fscanf(fileIN, "%d", &graph_size) != 1)
    {
        fprintf(stderr, "Error reading first line of input file\n");
        return 1;
    }
    
    List S = newList();
    for (int i = 1; i <= graph_size; i++)
    {
        append(S, i);
    }

    Graph G = newGraph(graph_size);
    fgets(Vert, MAX_LENGTH, fileIN); // Get first line (number of vertices

    
    // Read lines from input file and store in array intil "0 0"
    while (fgets(Vert, MAX_LENGTH, fileIN) != NULL)
    {
        if (strcmp(Vert, "0 0\n") == 0)
        {
            break;
        }
        sscanf(Vert, "%d %d", &x, &y);
        addArc(G, x, y);
    }
    // Break would exit here

    //-----------------------------------------------------------------------------
    // Print to output file
    fprintf(fileOUT, "Adjacency list representation of G:\n");
    printGraph(fileOUT, G);
    DFS(G, S);
    Graph T = transpose(G);
    DFS(T, S);

    int count = 0;
    for (moveFront(S); index(S) >= 0; moveNext(S))
    {
        if (getParent(T, get(S)) == NIL)
        {
            count++;
        }
    }

    // Find the strongly connected components
    List* components = malloc(count * sizeof(List));
    for (int i = 0; i < count; i++)
    {
        components[i] = newList();
    }

    int i = count;
    for (moveFront(S); index(S) >= 0; moveNext(S))
    {
        if (getParent(T, get(S)) == NIL)
        {
            i--;
        }
        if (i == count)
        {
            break;
        }
        append(components[i], get(S));
    }

    // Print the strongly connected components
    fprintf(fileOUT, "\nG contains %d strongly connected components:\n", count);
    for (int i = 1; i <= count; i++)
    {
        fprintf(fileOUT, "Component %d: ", i);
        printList(fileOUT, components[i-1]);
    }

    //-----------------------------------------------------------------------------
    // Free memory
    freeList(components);
    freeGraph(&G);
    freeGraph(&T);
    freeList(&S);
    
    fclose(fileIN);
    fclose(fileOUT);

    return 0;
}