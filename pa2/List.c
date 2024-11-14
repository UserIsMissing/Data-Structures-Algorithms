/*
Cole Schreiner
caschrei
pa1
List.c
*/

#include "List.h"
// #include <string.h>
// #include<stdio.h>
// #include<stdlib.h>
// #include<assert.h>
// #include<stdbool.h>

// structs --------------------------------------------------------------------
// private Node type
typedef struct NodeObj *Node;

// private NodeObj type
typedef struct NodeObj
{
    int data;
    Node next;
    Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj
{
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------
// newNode()
// Returns reference to new Node object. Initializes next, prev, and data fields.
Node newNode(int data)
{
    Node N = malloc(sizeof(NodeObj));
    assert(N != NULL);
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return (N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node *pN)
{
    if (pN != NULL && *pN != NULL)
    {
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// Creates and returns a new empty List.
List newList()
{
    List L = malloc(sizeof(struct ListObj));
    assert(L != NULL);
    L->front = L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return (L);
}

// freeList()
// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List *pL)
{
    if (pL != NULL && *pL != NULL)
    {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------
// Returns the number of elements in L.
int length(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling length() on NULL List reference\n");
        exit(1);
    }
    return (L->length);
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling index() on NULL List reference\n");
        exit(1);
    }
    if (L->cursor == NULL)
    {
        return -1;
    }
    return (L->index);
}

// Returns front element of L.
// Pre: length()>0
int front(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0)
    {
        printf("List Error: length is less than or equal to 0\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return (L->front->data);
    }
}

// Returns back element of L.
// Pre: length()>0
int back(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0)
    {
        printf("List Error: length is less than or equal to 0\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return (L->back->data);
    }
}

// Returns cursor element of L.
// Pre: length()>0, index()>=0
int get(List L)
{
    if (length(L) > 0 && index(L) >= 0)
    {
        return (L->cursor->data);
    }
    else
    {
        printf("List Error: Calling get()\n");
        exit(EXIT_FAILURE);
    }
}

// Returns true iff Lists A and B are in same state,
// and returns false otherwise.
bool equals(List A, List B)
{
    if (A == NULL || B == NULL)
    {
        fprintf(stderr, "List Error: calling equals() on NULL reference\n");
        return false; // Return false instead of exiting
    }
    if (length(A) != length(B))
    {
        return false; // End early for unequal lengths
    }

    Node nodeA = A->front;
    Node nodeB = B->front;

    while (nodeA != NULL && nodeB != NULL)
    {
        if (nodeA->data != nodeB->data)
        {
            return false;
        }
        nodeA = nodeA->next;
        nodeB = nodeB->next;
    }
    // If they end at the same time, they are the same
    return (true);
}

// Manipulation procedures ----------------------------------------------------
// Resets L to its original empty state.
void clear(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node current = L->front;
    while (current != NULL)
    {
        Node temp = current;
        current = current->next;
        freeNode(&temp);
    }

    // Update indicate empty list
    L->front = L->back = NULL;
    L->length = 0;
    L->index = -1;
    L->cursor = NULL;
}

// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, int x)
{
    if (L == NULL)
    {
        printf("List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) <= 0 || index(L) < 0)
    {
        printf("List Error: Preconditions not met for set()\n");
        exit(EXIT_FAILURE);
    }
    L->front->data = x;
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) >= 0)
    {
        L->cursor = L->front;
        L->index = 0;
    }
    else // If the list is empty, set cursor to NULL
    {
        L->cursor = NULL;
        L->index = -1;
    }
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) > 0)
    {
        L->cursor = L->back;
        L->index = length(L) - 1;
    }
    else // If the list is empty, set cursor to NULL
    {
        L->cursor = NULL;
        L->index = -1;
    }
}

// If cursor is defined and not at front, move cursor one step toward the front of L;
// If cursor is defined and at front, cursor becomes undefined;
// If cursor is undefined, do nothing
void movePrev(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    // If cursor is defined and not at front, move cursor one step toward the front of L;
    if (L->index > 0)
    {
        L->index--;
        L->cursor = L->cursor->prev;
    }
    // If cursor is defined and at front, cursor becomes undefined;
    if (L->index == 0)
    {
        L->index = -1;
    }
}

// If cursor is defined and not at back, move cursor one step toward the back of L;
// If cursor is defined and at back, cursor becomes undefined;
// If cursor is undefined do nothing
void moveNext(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->index < length(L))
    {
        L->index++;
        L->cursor = L->cursor->next;

        if (L->index == length(L))
        {
            L->index = -1;
        }
    }
}

// Insert new element into L.
// If L is non-empty, insertion takes place before front element.
void prepend(List L, int x)
{
    if (L == NULL)
    {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (L->front == NULL) // If the list is empty, set front and back to the new Node
    {
        L->back = L->front = N;
    }
    else // If the list is not empty, insert before the front element
    {
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
    }
    L->length++;
    L->index++;
}

// Insert new element into L.
// If L is non-empty, insertion takes place after back element.
void append(List L, int x)
{
    if (L == NULL)
    {
        printf("List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (L->back == NULL) // If the list is empty, set front and back to the new Node
    {
        L->front = L->back = N;
    }
    else // Handle non-empty list
    {
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
    }
    L->length++;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x)
{
    if (L == NULL)
    {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
        // **NOTE: I might consider using fprintf(stderr, "..."); return; for better error handling in the future
    }
    if (length(L) <= 0 || index(L) < 0)
    {
        printf("List Error: Preconditions not met for insertBefore()\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);

    N->next = L->cursor;
    N->prev = L->cursor->prev;

    if (L->cursor->prev != NULL)
    {
        L->cursor->prev->next = N;
    }
    else
    {
        L->front = N;
    }
    L->cursor->prev = N;

    // Update length and index
    L->length++;
    L->index++;
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x)
{
    if (L == NULL)
    {
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0 || index(L) < 0)
    {
        printf("List Error: Preconditions not met for insertAfter()\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == L->back)
    {
        append(L, x);
        return;
    }
    Node N = newNode(x);

    N->next = L->cursor->next;
    N->prev = L->cursor;
    L->cursor->next = N;

    if (L->cursor->next != NULL)
    {
        L->cursor->next->prev = N;
    }
    else
    {
        L->back = N;
    }

    // Update length
    L->length++;
}

// Delete the front element.
// Pre: length()>0
void deleteFront(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0)
    {
        printf("List Error: Preconditions not met for deleteFront()\n");
        exit(EXIT_FAILURE);
    }

    // Pointing temporary node to the front element
    Node temp = L->front;
    L->front = L->front->next; // Update front pointer
    if (L->front == NULL)      // If List is 1 element
    {
        L->back = NULL; // If list is empty
        L->index = -1;
    }
    else // Otherwise list is not 0 or 1
    {
        L->front->prev = NULL;
    }
    if (L->index == 0)
    {
        L->index = -1;
        L->cursor = NULL;
    }
    L->index--;
    L->length--;
    freeNode(&temp);
}

// Delete the back element.
// Pre: length()>0
void deleteBack(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0)
    {
        printf("List Error: Preconditions not met for deleteBack()\n");
        exit(EXIT_FAILURE);
    }

    Node temp = L->back;
    L->back = L->back->prev; // Update back pointer
    if (L->back == NULL)     // If List is 1 element
    {
        L->front = NULL; // If list is empty
        L->index = -1;
    }
    else // Otherwise list is not 0 or 1
    {
        L->back->next = NULL;
    }
    if (L->index == length(L) - 1)
    {
        L->index = -1;
        L->cursor = NULL;
    }
    L->length--;
    freeNode(&temp);
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0 || index(L) < 0)
    {
        printf("List Error: Preconditions not met for delete()\n");
        exit(EXIT_FAILURE);
    }

    Node temp = L->cursor;

    // If cursor is at front of the list
    if (L->front == L->back)
    {
        L->front = L->back = NULL;
    }
    // Else if: cursor is at the back
    else if (L->cursor == L->front)
    {
        L->front = L->cursor->next;
        L->front->prev = NULL;
    }
    // Else if: cursor is at the back
    else if (L->cursor == L->back)
    {
        L->back = L->cursor->prev;
        L->back->next = NULL;
    }
    // Cursor is somewhere in the middle of the list
    else
    {
        // Squeezing current cursor away
        // The cursor's prev element has a next element of the current next element
        L->cursor->prev->next = L->cursor->next; // At 'next', the previous item should be 'prev' and not current cursor
        // The cursor's next item has a prev item of the current prev element
        L->cursor->next->prev = L->cursor->prev; // At 'prev', the next item should be 'next' (after cursor) and not current cursor
    }

    L->length--;
    L->index = -1;
    freeNode(&temp);
}

// Other operations -----------------------------------------------------------
// Prints to the file pointed to by out, a string representation of L consisting of
// a space separated sequence of integers, with front on left.
void printList(FILE *out, List L)
{
    if (L == NULL)
    {
        printf("List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (out == NULL)
    {
        printf("List Error: calling printList() on NULL file pointer\n");
        exit(EXIT_FAILURE);
    }

    Node current = L->front;
    while (current != NULL)
    {
        fprintf(out, FORMAT " ", current->data);
        current = current->next;
    }
    fprintf(out, "\n");
}

// Returns a new List representing the same integer sequence as L.
// The cursor in the new list is undefined, regardless of the state of the cursor in L.
// The state of L is unchanged.
List copyList(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling copyList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    List newL = newList();
    Node current = L->front;
    while (current != NULL)
    {
        append(newL, current->data);
        current = current->next;
    }

    newL->index = -1;
    return newL;
}

// Optional--------------------------------------------------------------------
// Returns a new List which is the concatenation of A and B.
// The cursor in the new List is undefined, regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B)
{
    if (A == NULL || B == NULL)
    {
        printf("List Error: calling concatList() on NULL reference\n");
        exit(EXIT_FAILURE);
    }

    List newL = newList();
    Node currentA = A->front;
    while (currentA != NULL)
    {
        append(newL, currentA->data);
        currentA = currentA->next;
    }

    Node currentB = B->front;
    while (currentB != NULL)
    {
        append(newL, currentB->data);
        currentB = currentB->next;
    }

    newL->index = -1;
    return newL;
}