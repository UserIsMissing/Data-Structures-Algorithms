/*
Cole Schreiner
caschrei
pa6
ListTest.cpp
*/

#include <csetjmp>
#include <csignal>
#include <cstdbool>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "List.h"

#define FIRST_TEST Empty_size
#define MAXSCORE 53
#define CHARITY 10

#define RED "\033[0;31m"
#define CYAN "\033[0;36m"
#define GREEN "\033[0;32m"
#define NC "\033[0m"

using namespace std;

static uint8_t testsPassed;
static volatile sig_atomic_t testStatus;
static uint8_t disable_exit_handler;
jmp_buf test_crash;

enum Test_e {
  Empty_size = 0,
  InsertAfter_size,
  InsertBefore_size,
  EraseAfter_size,
  EraseBefore_size,
  Concat_size,
  Cleanup_size,

  EmptyList_position,
  MoveFront_position,
  MoveBack_position,
  MoveNext_position,
  MovePrev_position,
  InsertAfter_position,
  InsertBefore_position,
  FindNext_position,
  FindPrev_position,
  EraseAfter_position,
  EraseBefore_position,
  Cleanup_position,
  Concat_position,

  Assign_equals,
  InsertAfter_equals,
  InsertBefore_equals,
  EraseAfter_equals,
  EraseBefore_equals,
  Cleanup_equals,
  Concat_equals,

  Empty_clear,
  NonEmpty_clear,

  MoveNext_value,
  MovePrev_value,
  PeekNext_value,
  PeekPrev_value,
  FindNext_value,
  FindPrev_value,

  NUM_TESTS,
};

string testName(int test) {
  if (test == Empty_size)
    return "Empty_size";
  if (test == InsertAfter_size)
    return "InsertAfter_size";
  if (test == InsertBefore_size)
    return "InsertBefore_size";
  if (test == EraseAfter_size)
    return "EraseAfter_size";
  if (test == EraseBefore_size)
    return "EraseBefore_size";
  if (test == Concat_size)
    return "Concat_size";
  if (test == Cleanup_size)
    return "Cleanup_size";

  if (test == EmptyList_position)
    return "EmptyList_position";
  if (test == MoveFront_position)
    return "MoveFront_position";
  if (test == MoveBack_position)
    return "MoveBack_position";
  if (test == MoveNext_position)
    return "MoveNext_position";
  if (test == MovePrev_position)
    return "MovePrev_position";
  if (test == InsertAfter_position)
    return "InsertAfter_position";
  if (test == InsertBefore_position)
    return "InsertBefore_position";
  if (test == FindNext_position)
    return "FindNext_position";
  if (test == FindPrev_position)
    return "FindPrev_position";
  if (test == EraseAfter_position)
    return "EraseAfter_position";
  if (test == EraseBefore_position)
    return "EraseBefore_position";
  if (test == Cleanup_position)
    return "Cleanup_position";
  if (test == Concat_position)
    return "Concat_position";

  if (test == Assign_equals)
    return "Assign_equals";
  if (test == InsertAfter_equals)
    return "InsertAfter_equals";
  if (test == InsertBefore_equals)
    return "InsertBefore_equals";
  if (test == EraseAfter_equals)
    return "EraseAfter_equals";
  if (test == EraseBefore_equals)
    return "EraseBefore_equals";
  if (test == Cleanup_equals)
    return "Cleanup_equals";
  if (test == Concat_equals)
    return "Concat_equals";

  if (test == Empty_clear)
    return "Empty_clear";
  if (test == NonEmpty_clear)
    return "NonEmpty_clear";

  if (test == MoveNext_value)
    return "MoveNext_value";
  if (test == MovePrev_value)
    return "MovePrev_value";
  if (test == PeekNext_value)
    return "PeekNext_value";
  if (test == PeekPrev_value)
    return "PeekPrev_value";
  if (test == FindNext_value)
    return "FindNext_value";
  if (test == FindPrev_value)
    return "FindPrev_value";

  return "";
}

uint8_t runTest(List *pA, List *pB, int test) {
  List A = *pA;
  List B = *pB;
  switch (test) {
  case Empty_size: {
    if (A.length() != 0)
      return 1;
    return 0;
  }
  case InsertAfter_size: {
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    A.insertAfter(5);
    A.insertAfter(12);
    if (A.length() != 5)
      cout << "InsertAfter_size: failed test 1" << endl;
    return 0;
  }
  case InsertBefore_size: {
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    A.insertBefore(5);
    A.insertBefore(12);
    if (A.length() != 5)
      cout << "InsertBefore_size: failed test 1" << endl;
    return 0;
  }
  case EraseAfter_size: {
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    A.insertBefore(5);
    A.insertBefore(12);

    A.movePrev();
    A.eraseAfter();
    if (A.length() != 4)
      cout << "EraseAfter_size: failed test 1" << endl;

    A.findPrev(2);
    A.eraseAfter();
    if (A.length() != 3)
        cout << "EraseAfter_size: failed test 2" << endl;

    return 0;
  }
  case EraseBefore_size: {
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    A.insertAfter(5);
    A.insertAfter(12);

    A.moveNext();
    A.eraseBefore();
    if (A.length() != 4)
      cout << "EraseBefore_size: failed test 1" << endl;

    A.findNext(2);
    A.eraseBefore();
    if (A.length() != 3)
      cout << "EraseBefore_size: failed test 2" << endl;

    return 0;
  }
  case Concat_size: {
    List C;
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    B.insertAfter(4);
    B.insertAfter(5);
    B.insertAfter(6);

    C = A.concat(B);
    if (C.length() != 6)
      cout << "Concat_size: failed test 1" << endl;
    return 0;
  }
  case Cleanup_size: {
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(1);
    A.cleanup();
    if (A.length() != 3)
      cout << "Cleanup_size: failed test 1" << endl;
    return 0;
  }
  case EmptyList_position: {
    if (A.position() != 0)
      cout << "EmptyList_position: failed test 1" << endl;
    return 0;
  }
  case MoveFront_position: {
    A.insertBefore(1);
    A.insertBefore(5);
    A.insertBefore(16);
    A.insertBefore(176);
    A.insertBefore(3214);
    A.moveFront();
    if (A.position() != 0)
      cout << "MoveFront_position: failed test 1" << endl;
    return 0;
  }
  case MoveBack_position: {
    A.insertAfter(1);
    A.insertAfter(5);
    A.insertAfter(16);
    A.insertAfter(176);
    A.insertAfter(3214);
    A.moveBack();
    if (A.position() != 5)
      cout << "MoveBack_position: failed test 1" << endl;
    return 0;
  }
  case MoveNext_position: {
    A.insertAfter(3214);
    A.insertAfter(176);
    A.insertAfter(16);
    A.insertAfter(5);
    A.insertAfter(1);
    A.moveNext();
    A.moveNext();
    if (A.position() != 2)
      cout << "MoveNext_position: failed test 1" << endl;
    A.moveNext();
    A.moveNext();
    A.moveNext();
    if (A.position() != 5)
      cout << "MoveNext_position: failed test 2" << endl;
    return 0;
  }
  case MovePrev_position: {
    A.insertBefore(1);
    A.insertBefore(5);
    A.insertBefore(16);
    A.insertBefore(176);
    A.insertBefore(3214);
    A.movePrev();
    A.movePrev();
    if (A.position() != 3)
      cout << "MovePrev_position: failed test 1" << endl;
    A.movePrev();
    A.movePrev();
    A.movePrev();
    if (A.position() != 0)
      cout << "MovePrev_position: failed test 2" << endl;
    return 0;
  }
  case InsertAfter_position: {
    A.insertAfter(200);
    A.insertAfter(176);
    A.insertAfter(16);
    A.insertAfter(5);
    A.insertAfter(1);
    if (A.position() != 0)
      cout << "InsertAfter_position: failed test 1" << endl;

    A.moveBack();
    A.insertAfter(225);
    if (A.position() != 5)
      cout << "InsertAfter_position: failed test 2" << endl;

    A.insertAfter(255);
    A.moveBack();
    if (A.position() != 7)
      cout << "InsertAfter_position: failed test 3" << endl;
    return 0;
  }
  case InsertBefore_position: {
    A.insertBefore(1);
    A.insertBefore(5);
    A.insertBefore(16);
    A.insertBefore(176);
    A.insertBefore(200);
    if (A.position() != 5)
      cout << "InsertBefore_position: failed test 1" << endl;

    A.moveFront();
    A.insertBefore(225);
    if (A.position() != 1)
      cout << "InsertBefore_position: failed test 2" << endl;

    A.insertBefore(255);
    A.moveFront();
    if (A.position() != 0)
      cout << "InsertBefore_position: failed test 3" << endl;
    return 0;
  }
  case FindNext_position: {
    A.insertAfter(16);
    A.insertAfter(200);
    A.insertAfter(176);
    A.insertAfter(16);
    A.insertAfter(5);
    A.insertAfter(1);
    A.findNext(16);
    if (A.position() != 3)
      cout << "FindNext_position: failed test 1" << endl;

    A.movePrev();
    A.insertBefore(225);
    if (A.position() != 3)
      cout << "FindNext_position: failed test 2" << endl;

    A.moveNext();
    A.findNext(16);
    if (A.position() != 7)
      cout << "FindNext_position: failed test 3" << endl;

    A.moveFront();
    A.findNext(16);
    if (A.position() != 4)
      cout << "FindNext_position: failed test 4" << endl;
    return 0;
  }
  case FindPrev_position: {
    A.insertBefore(1);
    A.insertBefore(5);
    A.insertBefore(16);
    A.insertBefore(176);
    A.insertBefore(200);
    A.insertBefore(16);
    A.findPrev(16);
    if (A.position() != 5)
      cout << "FindPrev_position: failed test 1" << endl;

    A.moveNext();
    A.insertAfter(225);
    if (A.position() != 6)
      cout << "FindPrev_position: failed test 2" << endl;

    A.movePrev();
    A.findPrev(16);
    if (A.position() != 2)
      cout << "FindPrev_position: failed test 3" << endl;

    A.moveBack();
    A.findPrev(16);
    if (A.position() != 5)
      cout << "FindPrev_position: failed test 4" << endl;
    return 0;
  }
  case EraseAfter_position: {
    A.insertAfter(200);
    A.insertAfter(176);
    A.insertAfter(15);
    A.insertAfter(10);
    A.insertAfter(5);
    A.findNext(15);
    A.eraseAfter();
    if (A.position() != 3)
      cout << "EraseAfter_position: failed test 1" << endl;

    A.insertAfter(175);
    A.eraseAfter();
    if (A.position() != 3)
      cout << "EraseAfter_position: failed test 2" << endl;

    A.insertBefore(50);
    A.insertBefore(15);
    if (A.position() != 5)
      cout << "EraseAfter_position: failed test 3" << endl;

    A.findPrev(15);
    A.eraseAfter();
    if (A.position() != 4)
      cout << "EraseAfter_position: failed test 4" << endl;

    A.findPrev(15);
    if (A.position() != 2)
      cout << "EraseAfter_position: failed test 5" << endl;

    A.moveFront();
    A.eraseAfter();
    A.eraseAfter();
    A.eraseAfter();
    A.eraseAfter();
    A.eraseAfter();
    if (A.position() != 0)
      cout << "EraseAfter_position: failed test 6" << endl;
    return 0;
  }
  case EraseBefore_position: {
    A.insertBefore(5);
    A.insertBefore(10);
    A.insertBefore(15);
    A.insertBefore(176);
    A.insertBefore(200);
    A.findPrev(15);
    A.eraseBefore();
    if (A.position() != 1)
      cout << "EraseBefore_position: failed test 1" << endl;

    A.insertAfter(175);
    A.eraseBefore();
    if (A.position() != 0)
      cout << "EraseBefore_position: failed test 2" << endl;

    A.insertBefore(15);
    A.insertBefore(50);
    if (A.position() != 2)
      cout << "EraseBefore_position: failed test 3" << endl;

    A.findNext(15);
    A.eraseBefore();
    if (A.position() != 3)
      cout << "EraseBefore_position: failed test 4" << endl;

    A.findPrev(15);
    if (A.position() != 0)
      cout << "EraseBefore_position: failed test 5" << endl;

    A.moveBack();
    if (A.position() != 5)
      cout << "EraseBefore_position: failed test 6" << endl;
    A.eraseBefore();
    A.eraseBefore();
    A.eraseBefore();
    A.eraseBefore();
    A.eraseBefore();
    if (A.position() != 0)
      cout << "EraseBefore_position: failed test 7" << endl;
    return 0;
  }
  case Cleanup_position: {
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(2);
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    A.insertBefore(1);
    A.findPrev(3);
    A.cleanup();
    if (A.position() != 2)
      cout << "Cleanup_position: failed test 1" << endl;

    B.insertBefore(1);
    B.insertBefore(2);
    B.insertBefore(2);
    B.insertBefore(1);
    B.insertBefore(2);
    B.insertBefore(3);
    B.insertBefore(1);
    B.findPrev(3);
    B.movePrev();
    B.cleanup();
    if (B.position() != 2)
      cout << "Cleanup_position: failed test 2" << endl;
    return 0;
  }
  case Concat_position: {
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    B.insertBefore(4);
    B.insertBefore(5);
    B.insertBefore(6);

    if (A.concat(B).position() != 0)
      cout << "Concat_position: failed test 1" << endl;
    return 0;
  }
  case Assign_equals: {
    A.insertAfter(2);
    A.insertAfter(1);
    B = A;
    if (!A.equals(B))
      cout << "Assign_equals: failed test 1" << endl;
    return 0;
  }
  case InsertAfter_equals: {
    A.insertAfter(2);
    A.insertAfter(1);
    B.insertAfter(2);
    if (A.equals(B))
      cout << "InsertAfter_equals: failed test 1" << endl;
    if (A == B)
      cout << "InsertAfter_equals: failed test 2" << endl;

    B.insertAfter(1);
    if (!A.equals(B))
      cout << "InsertAfter_equals: failed test 3" << endl;
    return 0;
  }
  case InsertBefore_equals: {
    A.insertBefore(2);
    A.insertBefore(1);
    B.insertAfter(2);
    if (A.equals(B))
      cout << "InsertBefore_equals: failed test 1" << endl;

    B.moveBack();
    B.insertBefore(1);
    if (!A.equals(B))
      cout << "InsertBefore_equals: failed test 2" << endl;
    return 0;
  }
  case EraseAfter_equals: {
    A.insertBefore(1);
    A.insertAfter(2);
    B.insertBefore(1);
    B.insertBefore(2);
    A.eraseAfter();
    if (A.equals(B))
      cout << "EraseAfter_equals: failed test 1" << endl;

    B.movePrev();
    B.eraseAfter();
    if (!A.equals(B))
      cout << "EraseAfter_equals: failed test 2" << endl;

    A.insertAfter(5);
    B.insertAfter(5);
    A.eraseAfter();
    B.eraseAfter();
    if (!A.equals(B))
      cout << "EraseAfter_equals: failed test 3" << endl;
    return 0;
  }
  case EraseBefore_equals: {
    A.insertBefore(1);
    A.insertAfter(2);
    B.insertBefore(1);
    B.insertBefore(2);
    A.eraseBefore();
    if (A.equals(B))
      cout << "EraseBefore_equals: failed test 1" << endl;

    B.movePrev();
    B.eraseBefore();
    if (!A.equals(B))
      cout << "EraseBefore_equals: failed test 2" << endl;

    A.insertBefore(5);
    B.insertBefore(5);
    A.eraseBefore();
    B.eraseBefore();
    if (!A.equals(B))
      cout << "EraseBefore_equals: failed test 3" << endl;
    return 0;
  }
  case Cleanup_equals: {
    A.insertBefore(3);
    A.insertBefore(3);
    A.insertBefore(1);
    A.insertBefore(3);
    A.insertBefore(2);
    A.insertBefore(2);
    A.insertBefore(1);
    A.insertBefore(4);
    B.insertBefore(3);
    B.insertBefore(1);
    B.insertBefore(2);
    if (A.equals(B))
      cout << "Cleanup_equals: failed test 1" << endl;

    A.cleanup();
    if (A.equals(B))
      cout << "Cleanup_equals: failed test 2" << endl;

    A.moveBack();
    A.eraseBefore();
    if (!A.equals(B))
      cout << "Cleanup_equals: failed test 3" << endl;
    return 0;
  }
  case Concat_equals: {
    List C;
    A.insertBefore(1);
    A.insertAfter(3);
    A.insertAfter(2);
    B.insertBefore(3);
    B.insertBefore(2);
    B.insertBefore(1);
    C.insertAfter(1);
    C.insertAfter(2);
    C.insertAfter(3);
    C.insertAfter(3);
    C.insertAfter(2);
    C.insertAfter(1);
    if (!C.equals(A.concat(B)))
      cout << "Concat_equals: failed test 1" << endl;
    return 0;
  }
  case Empty_clear: {
    A.clear();
    if (A.length() != 0 || A.position() != 0)
      cout << "Empty_clear: failed test 1" << endl;
    return 0;
  }
  case NonEmpty_clear: {
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    A.insertBefore(5);
    A.insertBefore(12);
    A.clear();
    if (A.length() != 0 || A.position() != 0)
      cout << "NonEmpty_clear: failed test 1" << endl;
    return 0;
  }

  case MoveNext_value: {
    A.insertAfter(3215);
    A.insertAfter(176);
    A.insertAfter(22);
    A.insertAfter(5);
    A.insertAfter(1);
    A.moveNext();
    if (A.moveNext() != 5)
      cout << "MoveNext_value: failed test 1" << endl;

    A.eraseBefore();
    A.eraseBefore();
    A.moveNext();
    A.moveNext();
    if (A.moveNext() != 3215)
      cout << "MoveNext_value: failed test 2" << endl;

    A.moveFront();
    if (A.moveNext() != 22)
      cout << "MoveNext_value: failed test 3" << endl;
    return 0;
  }
  case MovePrev_value: {
    A.insertBefore(1);
    A.insertBefore(5);
    A.insertBefore(22);
    A.insertBefore(176);
    A.insertBefore(3215);
    A.movePrev();
    if (A.movePrev() != 176)
      cout << "MovePrev_value: failed test 1" << endl;
    A.eraseAfter();
    A.eraseAfter();
    A.movePrev();
    A.movePrev();
    if (A.movePrev() != 1)
      cout << "MovePrev_value: failed test 2" << endl;

    A.moveBack();
    if (A.movePrev() != 22)
      cout << "MovePrev_value: failed test 3" << endl;
    return 0;
  }
  case PeekNext_value: {
    A.insertAfter(60);
    A.insertAfter(50);
    A.insertAfter(40);
    A.insertBefore(10);
    A.insertBefore(20);
    A.insertBefore(30);
    if (A.peekNext() != 40)
      cout << "PeekNext_value: failed test 1" << endl;

    A.eraseAfter();
    if (A.peekNext() != 50)
      cout << "PeekNext_value: failed test 2" << endl;

    A.moveFront();
    if (A.peekNext() != 10)
      cout << "PeekNext_value: failed test 3" << endl;
    return 0;
  }
  case PeekPrev_value: {
    A.insertAfter(60);
    A.insertAfter(50);
    A.insertAfter(40);
    A.insertBefore(10);
    A.insertBefore(20);
    A.insertBefore(30);
    if (A.peekPrev() != 30)
      cout << "PeekPrev_value: failed test 1" << endl;

    A.eraseBefore();
    if (A.peekPrev() != 20)
      cout << "PeekPrev_value: failed test 2" << endl;

    A.moveBack();
    if (A.peekPrev() != 60)
      cout << "PeekPrev_value: failed test 3" << endl;
    return 0;
  }
  case FindNext_value: {
    A.insertAfter(77);
    A.insertAfter(55);
    A.insertAfter(1);
    A.insertAfter(34);
    A.insertAfter(1);
    A.insertAfter(77);
    A.insertAfter(77);
    A.insertAfter(34);
    if (A.findNext(99) != -1)
      cout << "FindNext_value: failed test 1" << endl;
    if (A.position() != A.length())
      cout << "FindNext_value: failed test 2" << endl;

    A.moveFront();
    if (A.findNext(1) != 4)
      cout << "FindNext_value: failed test 3" << endl;
    if (A.findNext(1) != 6)
      cout << "FindNext_value: failed test 4" << endl;
    if (A.findNext(1) != -1)
      cout << "FindNext_value: failed test 5" << endl;

    A.moveFront();
    A.cleanup();
    if (A.findNext(1) != 3)
      cout << "FindNext_value: failed test 6" << endl;
    if (A.findNext(1) != -1)
      cout << "FindNext_value: failed test 7" << endl;
    return 0;
  }
  case FindPrev_value: {
    A.insertBefore(34);
    A.insertBefore(77);
    A.insertBefore(77);
    A.insertBefore(1);
    A.insertBefore(34);
    A.insertBefore(1);
    A.insertBefore(55);
    A.insertBefore(77);
    if (A.findPrev(99) != -1)
      cout << "FindPrev_value: failed test 1" << endl;
    if (A.position() != 0)
      cout << "FindPrev_value: failed test 2" << endl;

    A.moveBack();
    if (A.findPrev(1) != 5)
      cout << "FindPrev_value: failed test 3" << endl;
    if (A.findPrev(1) != 3)
      cout << "FindPrev_value: failed test 4" << endl;
    if (A.findPrev(1) != -1)
      cout << "FindPrev_value: failed test 5" << endl;

    A.moveBack();
    A.cleanup();
    if (A.findPrev(1) != 2)
      cout << "FindPrev_value: failed test 6" << endl;
    if (A.findPrev(1) != -1)
      cout << "FindPrev_value: failed test 7" << endl;
    return 0;
  }
  }
  return 255;
}

void segfault_handler(int signal) { // everyone knows what this is
  testStatus = 255;
  longjmp(test_crash, 1);
}

void exit_attempt_handler(void) { // only I decide when you are done
  if (disable_exit_handler)
    return; // allow this to be disabled
  testStatus = 255;
  longjmp(test_crash, 2);
}

void abrupt_termination_handler(int signal) { // program killed externally
  testStatus = 255;
  longjmp(test_crash, 3);
}

int main(int argc, char **argv) {
  if (argc > 2 || (argc == 2 && strcmp(argv[1], "-v") != 0)) {
    printf("Usage: %s [-v]", (argc > 0 ? argv[0] : "./ListTest"));
    exit(1);
  }

  printf("\n"); // more spacing
  if (argc == 2)
    printf("\n"); // consistency in verbose mode

  testsPassed = 0;
  disable_exit_handler = 0;
  atexit(exit_attempt_handler);
  signal(SIGSEGV, segfault_handler);
  for (uint8_t i = FIRST_TEST; i < NUM_TESTS; i++) {
    List A, B;
    uint8_t fail_type;
    try {

      testStatus = runTest(&A, &B, i);
      fail_type = setjmp(test_crash);
    } catch (...) {
      testStatus = 255;
      fail_type = 3;
    }
    if (argc == 2) { // it's verbose mode
      cout << "Test " + testName(i) + ": "
           << (testStatus == 0 ? GREEN "PASSED" NC : RED "FAILED" NC);
      if (testStatus == 255) {
        cout << ": due to a " RED
             << (fail_type == 1
                     ? "segfault"
                     : (fail_type == 2
                            ? "program exit"
                            : (fail_type == 3 ? "exception being thrown"
                                              : "program interruption")))
             << NC << endl;
        cout << "\nWARNING: Program will now stop running tests\n" << endl;
        break;
      } else if (testStatus != 0) {
        cout << ": test " CYAN << testStatus << NC << endl;
      } else {
        cout << endl;
      }
    }
    if (testStatus == 0) {
      testsPassed++;
    }
  }

  disable_exit_handler = 1;

  uint8_t totalScore = (testsPassed / 2) * 3 + (testsPassed % 2) * 2;

  if (argc == 2 && testStatus != 255)
    cout << "\nYou passed " << unsigned(testsPassed) << " out of " << NUM_TESTS
         << " tests" << endl;
  else if (testStatus == 255) {
    totalScore = CHARITY; // charity points
    if (argc == 2)
      cout << RED "Receiving charity points because your program crashes" NC
           << endl;
  }
  cout << "You will receive " << unsigned(totalScore) << " out of " << MAXSCORE
       << " possible points on the ListTests\n"
       << endl;
  return 0;
}