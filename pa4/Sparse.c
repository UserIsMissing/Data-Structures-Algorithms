/*
Cole Schreiner
caschrei
pa4
Sparse.c
*/

#include "Matrix.h"
#include "List.h"
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
    // Start reading file
    int x, a, b;
    int value = fscanf(fileIN, "%d %d %d", &x, &a, &b);
    if (value == EOF)
    {
        fclose(fileIN);
        fclose(fileOUT);
        return 1;
    }

    Matrix MatrixA = newMatrix(x);
    Matrix MatrixB = newMatrix(x);
    for (int i = 0; i < a; i++)
    {
        int row, col;
        double data;
        fscanf(fileIN, "%d %d %lf", &row, &col, &data);
        changeEntry(MatrixA, row, col, data);
    }

    for (int i = 0; i < b; i++)
    {
        int row, col;
        double data;
        fscanf(fileIN, "%d %d %lf", &row, &col, &data);
        changeEntry(MatrixB, row, col, data);
    }

    //-----------------------------------------------------------------------------
    // Output format
    fprintf(fileOUT, "A has %d non-zero entries:\n", NNZ(MatrixA));
    printMatrix(fileOUT, MatrixA);

    fprintf(fileOUT, "B has %d non-zero entries:\n", NNZ(MatrixB));
    printMatrix(fileOUT, MatrixB);
    // Matrix operations
    Matrix ScalarMultiply = scalarMult(1.5, MatrixA);
    fprintf(fileOUT, "(1.5)*A =\n");
    printMatrix(fileOUT, ScalarMultiply);

    Matrix SumAB = sum(MatrixA, MatrixB);
    fprintf(fileOUT, "A+B =\n");
    printMatrix(fileOUT, SumAB);

    Matrix SumAA = sum(MatrixA, MatrixA);
    fprintf(fileOUT, "A+A =\n");
    printMatrix(fileOUT, SumAA);

    Matrix Diff = diff(MatrixB, MatrixA);
    fprintf(fileOUT, "B-A =\n");
    printMatrix(fileOUT, Diff);

    fprintf(fileOUT, "A-A =\n\n");

    Matrix TransposeA = transpose(MatrixA);
    fprintf(fileOUT, "Transpose(A) =\n");
    printMatrix(fileOUT, TransposeA);

    Matrix ProductAB = product(MatrixA, MatrixB);
    fprintf(fileOUT, "A*B =\n");
    printMatrix(fileOUT, ProductAB);

    Matrix ProductBB = product(MatrixB, MatrixB);
    fprintf(fileOUT, "B*B =\n");
    printMatrix(fileOUT, ProductBB);

    //-----------------------------------------------------------------------------
    // Close files
    fclose(fileIN);
    fclose(fileOUT);
    // Free memory
    freeMatrix(&MatrixA);
    freeMatrix(&MatrixB);
    freeMatrix(&ScalarMultiply);
    freeMatrix(&SumAB);
    freeMatrix(&SumAA);
    freeMatrix(&Diff);
    freeMatrix(&TransposeA);
    freeMatrix(&ProductAB);
    freeMatrix(&ProductBB);
    return 0;
}