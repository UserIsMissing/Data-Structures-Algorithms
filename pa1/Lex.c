/*
Cole Schreiner
caschrei
pa1
Lex.c
*/

/*
Our goal in this project is to build an Integer List ADT in C and use it to indirectly alphabetize the lines in a file.
This ADT module will also be used (with some modifications) in future programming assignments, so you should
test it thoroughly, even though not all of its features will be used here. Begin by reading the handout ADT.pdf
posted on the class webpage for a thorough explanation of the programming practices and conventions required
for implementing ADTs in C in this class.
Program Operation
The main program for this project will be called Lex.c. Your List ADT module will be contained in files called
List.h and List.c, and will export its services to the client module Lex.c. The required List operations are specified
in detail below. Lex.c will take two command line arguments giving the names of an input file and an output file,
respectively.
Lex <input file> <output file>
The input can be any text file. The output file will contain the same lines as the input, but arranged in
lexicographic (i.e. alphabetical) order. For example:
Input file: Output file:
one five
two four
three one
four three
five two
Lex.c will follow the sketch given below.
1. Check that there are two command line arguments (other than the program name Lex). Quit with a usage
message to stderr if more than or less than two command line arguments are given.
2. Count the number of lines n in the input file. Create a string array of length n and read in the lines of the
file as strings, placing them into the array. (Allocate this array from heap memory using functions
calloc() or malloc() defined in the header file stdlib.h. Do not use a variable length array. See
the comments here for more on this topic.)
3. Create a List whose elements are the indices of the above string array. These indices should be arranged
in an order that indirectly sorts the array. Using the above input file as an example we would have.
Indices: 0 1 2 3 4
Array: one two three four five
List: 4 3 0 2 1
To build the integer List in the correct order, begin with an initially empty List, then insert the indices of
the array one by one into the appropriate positions of the List. Use the Insertion Sort algorithm (section
2.1 of the text CLRS) as a guide to your thinking on how to accomplish this. (Please read the preceding
two sentences several times so that you understand what is required. You are not being asked to sort the
input array using Insertion Sort.) You may use only the List ADT operations defined below to manipulate the List. Note that the C standard library string.h provides a function called strcmp() that determines
the lexicographic ordering of two Strings. If s1 and s2 are strings then:
strcmp(s1, s2)<0 is true if and only if s1 comes before s2
strcmp(s1, s2)>0 is true if and only if s1 comes after s2
strcmp(s1, s2)==0 is true if and only if s1 is identical to s2
4. Use the List constructed in (3) to print the array in alphabetical order to the output file. Note that at no
time is the array ever sorted. Instead you are indirectly sorting the array by building a List of indices in a
certain order.
See the example FileIO.c to learn about file input-output operations in C if you are not already familiar with them.
I will place a number of matched pairs of input-output files in the examples section, along with a python script
that creates random input files, along with their matched output files. You may use these tools to test your
program once it is up and running.
 */

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 300
//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    //-----------------------------------------------------------------------------
    // 1. Check command line arguments
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1); // exit(1)
    }

    //-----------------------------------------------------------------------------
    // 2. Count number of lines in input file and read into an array
    FILE *fileIN = fopen(argv[1], "r");
    if (fileIN == NULL)
    {
        fprintf(stderr, "Unable to open file %s for reading", argv[1]);
        exit(1);
    }

    int line_count = 0;
    char c;
    while ((c = fgetc(fileIN)) != EOF)
    {
        if (c == '\n')
        {
            line_count++;
        }
    }

    rewind(fileIN);

    char **lines = (char **)malloc(line_count * sizeof(char *));
    for (int i = 0; i < line_count; i++)
    {
        lines[i] = (char *)malloc(MAX_LENGTH * sizeof(char));
        fgets(lines[i], MAX_LENGTH, fileIN);
    }

    //-----------------------------------------------------------------------------
    // 3. Create List of indices
    List indexList = newList();
    for (int i = 0; i < line_count; i++)
    {
        moveFront(indexList);
        while (index(indexList) != -1 && strcmp(lines[get(indexList)], lines[i]) < 0)
        {
            moveNext(indexList);
        }
        if (length(indexList) == 0)
        {
            append(indexList, i);   // append to empty list for 1st element
        }
        else if (index(indexList) == -1)
        {
            append(indexList, i);
        }
        else
        {
            insertBefore(indexList, i);
        }
        // insertBefore(indexList, i);
    }

    //-----------------------------------------------------------------------------
    // 4. Print to output file
    FILE *fileOUT = fopen(argv[2], "w"); // Open the output file in write mode
    if (fileOUT == NULL)
    {
        fprintf(stderr, "Error opening output file %s\n", argv[2]);
        exit(1);
    }

    moveFront(indexList);
    while (index(indexList) != -1)
    {
        fprintf(fileOUT, "%s", lines[get(indexList)]);
        moveNext(indexList);
    }

    //-----------------------------------------------------------------------------
    // Free memory
    for (int i = 0; i < line_count; i++)
    {
        free(lines[i]);
    }
    free(lines);
    freeList(&indexList);
    fclose(fileIN);
    fclose(fileOUT);

    return 0;
}