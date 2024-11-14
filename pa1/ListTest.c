/*
Cole Schreiner
caschrei
pa1
*/

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
    // Create lists using descriptive names
    List numbersInOrder = newList();
    List numbersReversed = newList();

    // Populate lists using range-based for loop
    for (int i = 1; i <= 20; ++i) {
        append(numbersInOrder, i);
        prepend(numbersReversed, i);
    }


    // Print lists with clearer headings
    printf("Numbers in order:\n");
    printList(stdout, numbersInOrder);
    printf("\nNumbers reversed:\n");
    printList(stdout, numbersReversed);

    // Iterate and print elements directly
    printf("\nNumbers in order (iterated):\n");
    for (moveFront(numbersInOrder); index(numbersInOrder) >= 0; moveNext(numbersInOrder)) {
        printf("%d ", get(numbersInOrder));
    }

    printf("\nNumbers reversed (iterated):\n");
    for (moveBack(numbersReversed); index(numbersReversed) >= 0; movePrev(numbersReversed)) {
        printf("%d ", get(numbersReversed));
    }

    // Copy and compare lists
    List copiedList = copyList(numbersInOrder);
    printf("\n\nLists equal?\n");
    printf("- A and B: %s\n", equals(numbersInOrder, numbersReversed) ? "true" : "false");
    printf("- B and C: %s\n", equals(numbersReversed, copiedList) ? "true" : "false");
    printf("- C and A: %s\n", equals(copiedList, numbersInOrder) ? "true" : "false");

    // Move elements
    printf("\nLength of lists: is %d\n", length(numbersInOrder));
    printf("index of cursor: is %d\n", index(numbersInOrder));
    moveBack(numbersInOrder);
    printf("index of cursor: is %d\n", index(numbersInOrder));
    moveBack(numbersInOrder);
    moveBack(numbersInOrder);
    moveFront(numbersInOrder);
    printf("index of cursor: is %d\n", index(numbersInOrder));
    printf("front of list: is %d\n", front(numbersInOrder));
    printf("back of list: is %d\n", back(numbersInOrder));


    // Clear and print length
    printf("\nLength of A: %d\n", length(numbersInOrder));
    clear(numbersInOrder);
    printf("Length of A after clearing: %d\n", length(numbersInOrder));

    freeList(&numbersInOrder);
    freeList(&numbersReversed);
    freeList(&copiedList);

    return 0;
}
