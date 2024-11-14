/*
Cole Schreiner
caschrei
pa4
MatrixTest.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Matrix.h"

// Test client for the Matrix ADT

int main(int argc, char *argv[])
{
    int n = 100;
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    changeEntry(A, 1, 1, 1.0);
    changeEntry(B, 1, 1, 1.0);
    // Test equals()
    assert(equals(A, B));

    // Test changeEntry()
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            changeEntry(A, i, j, 1.0);
            changeEntry(B, i, j, 2.0);
        }
    }

    // Test NNZ()
    assert(NNZ(A) == n * n);
    assert(NNZ(B) == n * n);

    // Test makeZero()
    makeZero(A);
    assert(NNZ(A) == 0);

    // Test copy()
    Matrix C = copy(B);
    assert(equals(B, C));

    // Test transpose()
    Matrix D = transpose(B);
    assert(equals(B, D));

    // Test scalarMult()
    Matrix E = scalarMult(2.0, A);
    assert(NNZ(E) == 0);

    // Test sum()
    Matrix F = sum(B, C);
    assert(NNZ(F) == n * n);

    // Test diff()
    Matrix G = diff(B, C);
    assert(NNZ(G) == 0);

    // Test product()
    Matrix H = product(B, C);
    assert(NNZ(H) == n * n);

    // Test freeMatrix()
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);

    printf("All tests passed!\n");
}
