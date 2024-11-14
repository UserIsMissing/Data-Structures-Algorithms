/*
Cole Schreiner
caschrei
pa4
Matrix.c
*/

#include "List.h"

#include <limits.h>
#include <stdio.h>
// #include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Matrix.h"

typedef struct EntryObj *Entry;

// Structs --------------------------------------------------------------------
typedef struct EntryObj
{
    int column;
    double index;
} EntryObj;

typedef struct MatrixObj
{
    List *row;
    int size;
    int NNZ;
    // int equals;
} MatrixObj;

// Constructors-Destructors ---------------------------------------------------
Entry newEntry(int column, double index)
{
    Entry E = malloc(sizeof(struct EntryObj));
    E->column = column;
    E->index = index;
    return E;
}

void freeEntry(Entry *pE)
{
    if (pE != NULL && *pE != NULL)
    {
        free(*pE);
        *pE = NULL;
        pE = NULL;
    }
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n)
{
    if (n < 1)
    {
        printf("Matrix Error: calling newMatrix() on invalid size\n");
        return NULL;
    }

    Matrix M = malloc(sizeof(struct MatrixObj));
    M->size = n;
    M->NNZ = 0;
    // M->equals = 0;
    M->row = calloc(n + 1, sizeof(List));
    for (int i = 0; i < n; i++)
    {
        M->row[i] = newList();
    }
    return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix *pM)
{
    if (pM != NULL && *pM != NULL)
    {
        for (int i = 0; i < (*pM)->size; i++)
        {
            List temp = (*pM)->row[i];
            for (moveFront(temp); index(temp) >= 0; moveNext(temp))
            {
                Entry e = (Entry)get(temp);
                freeEntry(&e);
            }
            freeList(&(*pM)->row[i]);
        }
        free((*pM)->row);
        free(*pM);
        *pM = NULL;
        pM = NULL;
    }
}

// Access functions -----------------------------------------------------------
// size()
// Return the size of square Matrix M.
int size(Matrix M)
{
    if (M == NULL)
    {
        printf("Matrix Error: calling size() on NULL Matrix reference\n");
        exit(1);
    }
    return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M)
{
    if (M == NULL)
    {
        printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
        exit(1);
    }
    return M->NNZ;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B)
{
    if (A == NULL || B == NULL)
    {
        printf("Matrix Error: calling equals() on NULL Matrix reference\n");
        exit(1);
    }
    if (A->size != B->size)
    {
        return 0;
    }
    if (A->NNZ != B->NNZ)
    {
        return 0;
    }
    for (int i = 0; i < A->size; i++)
    {
        if (length(A->row[i]) != length(B->row[i]))
        {
            return 0;
        }
        moveFront(A->row[i]);
        moveFront(B->row[i]);
        while (index(A->row[i]) >= 0)
        {
            Entry eA = (Entry)get(A->row[i]);
            Entry eB = (Entry)get(B->row[i]);
            if (eA->column != eB->column || eA->index != eB->index)
            {
                return 0;
            }
            moveNext(A->row[i]);
            moveNext(B->row[i]);
        }
    }
    return 1;
}

// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M)
{
    if (M == NULL)
    {
        printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
        return;
    }
    for (int i = 0; i < M->size; i++)
    {
        clear(M->row[i]);
    }
    M->NNZ = 0;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x)
{
    if (M == NULL)
    {
        printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        return;
    }
    if (i < 1 || i > M->size)
    {
        printf("Matrix Error: calling changeEntry() on invalid row\n");
        return;
    }
    if (j < 1 || j > M->size)
    {
        printf("Matrix Error: calling changeEntry() on invalid column\n");
        return;
    }
    if (M->size == 0)
    {
        printf("Matrix Error: calling changeEntry() on empty Matrix\n");
        return;
    }

    moveFront(M->row[i - 1]);
    while (index(M->row[i - 1]) >= 0)
    {
        Entry e = (Entry)get(M->row[i - 1]);
        if (e->column == j) // if the column already exists
        {
            if (x == 0)
            {
                delete (M->row[i - 1]);
                M->NNZ--;
            }
            else
            {
                e->index = x;
            }
            return;
        }
        moveNext(M->row[i - 1]);
    }
    if (x != 0) // if the column does not exist
    {
        moveFront(M->row[i - 1]);
        while (index(M->row[i - 1]) >= 0)
        {
            Entry e = (Entry)get(M->row[i - 1]);
            if (e->column < j)
            {
                moveNext(M->row[i - 1]);
            }
            else
            {
                insertBefore(M->row[i - 1], newEntry(j, x));
                M->NNZ++;
                return;
            }
        }
        append(M->row[i - 1], newEntry(j, x));
        M->NNZ++;
    }
    return;
}

// Matrix Arithmetic operations ------------------------------------------------
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A)
{
    if (A == NULL)
    {
        printf("Matrix Error: calling copy() on NULL Matrix reference\n");
        return NULL;
    }
    Matrix Copy = newMatrix(A->size);
    for (int i = 0; i < A->size; i++)
    {
        moveFront(A->row[i]);
        while (index(A->row[i]) >= 0)
        {
            Entry e = (Entry)get(A->row[i]);
            append(Copy->row[i], newEntry(e->column, e->index));
            moveNext(A->row[i]);
        }
    }
    Copy->NNZ = A->NNZ;
    return Copy;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A)
{
    if (A == NULL)
    {
        printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
        return NULL;
    }
    Matrix Transpose = newMatrix(A->size);
    for (int i = 0; i < A->size; i++)
    {
        moveFront(A->row[i]);
        while (index(A->row[i]) >= 0)
        {
            Entry e = (Entry)get(A->row[i]);
            append(Transpose->row[e->column - 1], newEntry(i + 1, e->index));
            moveNext(A->row[i]);
        }
    }
    Transpose->NNZ = A->NNZ;
    return Transpose;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A)
{
    if (A == NULL)
    {
        printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
        return NULL;
    }
    Matrix Scalar = newMatrix(A->size);
    for (int i = 0; i < A->size; i++)
    {
        moveFront(A->row[i]);
        while (index(A->row[i]) >= 0)
        {
            Entry e = (Entry)get(A->row[i]);
            append(Scalar->row[i], newEntry(e->column, e->index * x));
            moveNext(A->row[i]);
        }
    }
    Scalar->NNZ = A->NNZ;
    return Scalar;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B)
{
    if (A == NULL || B == NULL)
    {
        printf("Matrix Error: calling sum() on NULL Matrix reference\n");
        return NULL;
    }
    if (A->size != B->size)
    {
        printf("Matrix Error: calling sum() on different size matrices\n");
        return NULL;
    }
    Matrix Sum = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++)
    {
        for (int j = 1; j <= A->size; j++)
        {
            double a = 0;
            double b = 0;
            moveFront(A->row[i - 1]);
            moveFront(B->row[i - 1]);
            while (index(A->row[i - 1]) >= 0)
            {
                Entry e = (Entry)get(A->row[i - 1]);
                if (e->column == j)
                {
                    a = e->index;
                    break;
                }
                moveNext(A->row[i - 1]);
            }
            while (index(B->row[i - 1]) >= 0)
            {
                Entry temp = (Entry)get(B->row[i - 1]);
                if (temp->column == j)
                {
                    b = temp->index;
                    break;
                }
                moveNext(B->row[i - 1]);
            }
            if (a + b != 0)
            {
                append(Sum->row[i - 1], newEntry(j, a + b));
                Sum->NNZ++;
            }
        }
    }
    return Sum;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B)
{
    if (A == NULL || B == NULL)
    {
        printf("Matrix Error: calling diff() on NULL Matrix reference\n");
        return NULL;
    }
    if (A->size != B->size)
    {
        printf("Matrix Error: calling diff() on different size matrices\n");
        return NULL;
    }
    Matrix Diff = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++)
    {
        for (int j = 1; j <= A->size; j++)
        {
            double a = 0;
            double b = 0;
            moveFront(A->row[i - 1]);
            moveFront(B->row[i - 1]);
            while (index(A->row[i - 1]) >= 0)
            {
                Entry e = (Entry)get(A->row[i - 1]);
                if (e->column == j)
                {
                    a = e->index;
                    break;
                }
                moveNext(A->row[i - 1]);
            }
            while (index(B->row[i - 1]) >= 0)
            {
                Entry temp = (Entry)get(B->row[i - 1]);
                if (temp->column == j)
                {
                    b = temp->index;
                    break;
                }
                moveNext(B->row[i - 1]);
            }
            if (a - b != 0)
            {
                append(Diff->row[i - 1], newEntry(j, a - b));
                Diff->NNZ++;
            }
        }
    }
    return Diff;
}

// computes the vector dot product of two matrix rows represented by Lists P and Q.
// Use this function together with function transpose() to help implement product()
double vectorDot(List P, List Q)
{
    double dotProduct = 0;
    moveFront(P);
    moveFront(Q);
    while (index(P) >= 0 && index(Q) >= 0)
    {
        Entry p = (Entry)get(P);
        Entry q = (Entry)get(Q);
        if (p->column == q->column)
        {
            dotProduct += p->index * q->index;
            moveNext(P);
            moveNext(Q);
        }
        else if (p->column < q->column)
        {
            moveNext(P);
        }
        else
        {
            moveNext(Q);
        }
    }
    return dotProduct;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B)
{
    if (A == NULL || B == NULL)
    {
        printf("Matrix Error: calling product() on NULL Matrix reference\n");
        return NULL;
    }
    if (A->size != B->size)
    {
        printf("Matrix Error: calling product() on different size matrices\n");
        return NULL;
    }
    Matrix Product = newMatrix(A->size);
    Matrix TransposeB = transpose(B);
    for (int i = 0; i < A->size; i++)
    {
        if (length(A->row[i]) > 0)
        {
            for (int j = 0; j < A->size; j++)
            {
                if (length(TransposeB->row[j]) > 0)
                {
                    double dotProduct = vectorDot(A->row[i], TransposeB->row[j]);
                    if (dotProduct != 0)
                    {
                        append(Product->row[i], newEntry(j + 1, dotProduct));
                        Product->NNZ++;
                    }
                }
            }
        }
    }
    freeMatrix(&TransposeB);
    return Product;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE *out, Matrix M)
{
    if (M == NULL)
    {
        printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
        return;
    }
    for (int i = 0; i < M->size; i++)
    {
        if (length(M->row[i]) > 0)
        {
            fprintf(out, "%d: ", i + 1);
            moveFront(M->row[i]);
            while (index(M->row[i]) >= 0)
            {
                Entry e = (Entry)get(M->row[i]);
                fprintf(out, "(%d, %.1f) ", e->column, e->index);
                moveNext(M->row[i]);
            }
            fprintf(out, "\n");
        }
    }
    fprintf(out, "\n");
}
