/*
Cole Schreiner
caschrei
pa1
FindPath.c
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
    int distance, source, destination;
    
    if (fscanf(fileIN, "%d", &graph_size) != 1)
    {
        fprintf(stderr, "Error reading first line of input file\n");
        return 1;
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
        addEdge(G, x, y);
    }
    // Break would exit here


    //-----------------------------------------------------------------------------
    // Print to output file
    printGraph(fileOUT, G);

    List path = newList();

    // Print shortest path from source to destination
    while (fscanf(fileIN, "%d %d", &source, &destination) == 2)
    {
        if (source == 0 && destination == 0)
        {
            break;
        }
        BFS(G, source);
        distance = getDist(G, destination);
        fprintf(fileOUT, "\nThe distance from %d to %d is ", source, destination);
        if (distance == INF)
        {
            fprintf(fileOUT, "infinity\n");
            fprintf(fileOUT, "No %d-%d path exists\n", source, destination);
        }
        else
        {
            fprintf(fileOUT, "%d\n", distance);
            fprintf(fileOUT, "A shortest %d-%d path is: ", source, destination);
            getPath(path, G, destination);
            printList(fileOUT, path);
        }
        clear(path);
    }

    //-----------------------------------------------------------------------------
    // Free memory
    freeList(&path);
    freeGraph(&G);
    
    fclose(fileIN);
    fclose(fileOUT);

    return 0;
}