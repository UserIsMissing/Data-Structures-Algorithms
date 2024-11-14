/*
Cole Schreiner
caschrei
pa4
ListTest.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

int main(int argc, char *argv[])
{
    // Create a new list
    List list = newList();

    // Test length() function
    printf("Length of list: %d\n", length(list)); // Expected output: 0

    // Test prepend() function
    int a = 10;
    prepend(list, &a);
    printf("Length of list after prepend: %d\n", length(list)); // Expected output: 1

    // Test append() function
    int b = 20;
    append(list, &b);
    printf("Length of list after append: %d\n", length(list)); // Expected output: 2

    // Test front() function
    int *frontElement = front(list);
    printf("Front element of list: %d\n", *frontElement); // Expected output: 10

    // Test back() function
    int *backElement = back(list);
    printf("Back element of list: %d\n", *backElement); // Expected output: 20

    // Test moveFront() function
    moveFront(list);
    int *cursorElement = get(list);
    printf("Cursor element after moveFront: %d\n", *cursorElement); // Expected output: 10

    // Test moveBack() function
    moveBack(list);
    cursorElement = get(list);
    printf("Cursor element after moveBack: %d\n", *cursorElement); // Expected output: 20

    // Test movePrev() function
    movePrev(list);
    printf("Cursor element after movePrev: %d\n", *cursorElement); // Expected output: 10

    // Test moveNext() function
    moveNext(list);
    printf("Cursor element after moveNext: %d\n", *cursorElement); // Expected output: 20

    // Test insertBefore() function
    int c = 3;
    insertBefore(list, &c);
    printf("Cursor element after insertBefore: %d\n", length(list)); // Expected output: 3

    // Test insertAfter() function
    // print newly inserted element
    insertAfter(list, &c);
    int *insertedElement = get(list);
    printf("Inserted element: %d\n", *insertedElement); // Expected output: 20

    
    // Test set() function
    int d = 4;
    set(list, &d);
    printf("Cursor element after set: %d\n", *cursorElement); // Expected output: 20

    // Test clear() function
    clear(list);
    printf("Length of list after clear: %d\n", length(list)); // Expected output: 0

    // Free the list
    freeList(&list);

    return 0;
}