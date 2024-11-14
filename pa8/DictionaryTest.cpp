/*
Cole Schreiner
caschrei
pa8
DictionaryTest.cpp
*/

#include <csetjmp>
#include <csignal>
#include <cstdbool>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include "Dictionary.h"

#define FIRST_TEST Empty_size
#define MAXSCORE 45
#define CHARITY 10

#define RED "\033[0;31m"
#define CYAN "\033[0;36m"
#define GREEN "\033[0;32m"
#define NC "\033[0m"

using namespace std;

// static uint8_t testsPassed;
static volatile sig_atomic_t testStatus;
// static uint8_t disable_exit_handler;
jmp_buf test_crash;

enum Test_e
{
  Empty_size = 0,
  SetValue_size,
  Remove_size,

  Empty_traverse,
  Empty_clear,
  NonEmpty_clear,

  Begin_value,
  End_value,
  Next_value,
  Prev_value,
  SetValue_value,
  Remove_value,
  GetValue_value,

  Repeated_setValue,
  MultiString_equals,
  ToString_equals,
  PreString_equals,
  Contains_value,

  NUM_TESTS,
};

string testName(int test)
{
  if (test == Empty_size)
    return "Empty_size";
  if (test == SetValue_size)
    return "SetValue_size";
  if (test == Remove_size)
    return "Remove_size";

  if (test == Empty_traverse)
    return "Empty_traverse";
  if (test == Empty_clear)
    return "Empty_clear";
  if (test == NonEmpty_clear)
    return "NonEmpty_clear";

  if (test == Begin_value)
    return "Begin_value";
  if (test == End_value)
    return "End_value";
  if (test == Next_value)
    return "Next_value";
  if (test == Prev_value)
    return "Prev_value";
  if (test == SetValue_value)
    return "SetValue_value";
  if (test == Remove_value)
    return "Remove_value";
  if (test == GetValue_value)
    return "GetValue_value";

  if (test == Repeated_setValue)
    return "Repeated_setValue";
  if (test == MultiString_equals)
    return "MultiString_equals";
  if (test == ToString_equals)
    return "ToString_equals";
  if (test == PreString_equals)
    return "PreString_equals";
  if (test == Contains_value)
    return "Contains_value";

  return "";
}

uint8_t runTest(Dictionary *pA, Dictionary *pB, int test)
{
  Dictionary A = *pA;
  Dictionary B = *pB;
  switch (test)
  {
  case Empty_size:
  {
    if (A.size() != 0)
      cout << "Empty_size: Test 1 failed" << endl;
    return 0;
  }
    case SetValue_size:
    {
      A.setValue("a", 1);
      A.setValue("b", 2);
      A.setValue("c", 3);
      A.setValue("e", 5);
      if (A.size() != 4)
        cout << "SetValue_size: Test 1 failed" << endl;
      return 0;
    }
    case Remove_size:
    {
      A.setValue("c", 3);
      A.setValue("a", 1);
      A.setValue("b", 2);
      A.remove("a");
      if (A.size() != 2)
        cout << "Remove_size: Test 1 failed" << endl;
      A.setValue("e", 5);
      A.remove("c");
      if (A.size() != 2)
        cout << "Remove_size: Test 2 failed" << endl;
      return 0;
    }
    case Empty_traverse:
    {
      try
      {
        A.begin();
        A.currentVal();
        cout << "Empty_traverse: Test 1 failed" << endl;
      }
      catch (logic_error const &)
      {
      }
      try
      {
        A.end();
        A.currentVal();
        cout << "Empty_traverse: Test 2 failed" << endl;
      }
      catch (logic_error const &)
      {
      }
      try
      {
        A.currentVal();
        cout << "Empty_traverse: Test 3 failed" << endl;
      }
      catch (logic_error const &)
      {
      }
      try
      {
        A.currentKey();
        cout << "Empty_traverse: Test 4 failed" << endl;
      }
      catch (logic_error const &)
      {
      }

      return 0;
    }
    case Empty_clear:
    {
      A.clear();
      if (A.size() != 0)
      {
        cout << "Empty_clear: Test 1 failed" << endl;
      }
      try
      {
        A.currentKey();
        cout << "Empty_clear: Test 2 failed" << endl;
      }
      catch (logic_error const &)
      {
      }
      return 0;
    }
    case NonEmpty_clear:
    {
      A.setValue("c", 3);
      A.setValue("b", 2);
      A.setValue("a", 1);
      A.begin();
      A.clear();
      if (A.size() != 0)
      {
        cout << "NonEmpty_clear: Test 1 failed" << endl;
      }
      try
      {
        A.currentKey();
        cout << "NonEmpty_clear: Test 2 failed" << endl;
      }
      catch (logic_error const &)
      {
      }
      return 0;
    }
    case Begin_value:
    {
      A.setValue("d", 1);
      A.setValue("b", 5);
      A.setValue("c", 16);
      A.setValue("f", 176);
      A.setValue("e", 3214);

      A.begin();
      if (A.currentVal() != 5 || A.currentKey() != "b")
        cout << "Begin_value: Test 1 failed" << endl;

      A.remove("b");
      A.begin();

      if (A.currentVal() != 16 || A.currentKey() != "c")
        cout << "Begin_value: Test 2 failed" << endl;
      return 0;
    }
    case End_value:
    {
      A.setValue("d", 1);
      A.setValue("b", 5);
      A.setValue("c", 16);
      A.setValue("f", 176);
      A.setValue("e", 3214);

      A.end();
      if (A.currentVal() != 176 || A.currentKey() != "f")
        cout << "End_value: Test 1 failed" << endl;

      A.remove("f");
      A.end();

      if (A.currentVal() != 3214 || A.currentKey() != "e")
        cout << "End_value: Test 2 failed" << endl;
      return 0;
    }
    case Next_value:
    {
      A.setValue("a", 1);
      A.setValue("b", 5);
      A.setValue("c", 16);
      A.setValue("d", 176);
      A.setValue("e", 3214);
      A.begin();
      A.next();
      A.next();

      if (A.currentKey() != "c" || A.currentVal() != 16)
        cout << "Next_value: Test 1 failed" << endl;
      A.next();
      A.next();
      A.next();
      if (A.hasCurrent())
        cout << "Next_value: Test 2 failed" << endl;
      return 0;
    }
    case Prev_value:
    {
      A.setValue("a", 1);
      A.setValue("b", 5);
      A.setValue("e", 3214);
      A.end();
      A.prev();
      if (A.currentKey() != "b" || A.currentVal() != 5)
        cout << "Prev_value: Test 1 failed" << endl;
      A.prev();
      A.prev();
      if (A.hasCurrent())
        cout << "Prev_value: Test 2 failed" << endl;
      return 0;
    }
    case SetValue_value:
    {
      A.setValue("a", 1);
      A.setValue("b", 5);
      A.setValue("e", 10);
      A.end();
      A.setValue("h", 15);
      A.setValue("f", 20);
      A.setValue("i", 100);
      if (A.currentKey() != "e" || A.currentVal() != 10)
        cout << "SetValue_value: Test 1 failed" << endl;
      A.end();
      A.prev();
      A.prev();
      if (A.currentKey() != "f" || A.currentVal() != 20)
        cout << "SetValue_value: Test 2 failed" << endl;
      return 0;
    }
    case Remove_value:
    {
      string ideal1 = "d\nb\nc (RED)\nf\ne (RED)\ng (RED)\n";
      string ideal2 = "e\nb\nc (RED)\nf\ng (RED)\n";
      string ideal3 = "e\nb\nc (RED)\nf\n";
      A.setValue("d", 1);
      A.setValue("b", 5);
      A.setValue("a", 10);
      A.setValue("c", 15);
      A.setValue("f", 20);
      A.setValue("e", 25);
      A.setValue("g", 30);
      A.begin();
      A.remove("a");
      if (A.hasCurrent())
        cout << "Remove_value: Test 1 failed" << endl;
      if (A.pre_string() != ideal1)
        cout << "Remove_value: Test 12 failed" << endl;
      A.end();
      A.remove("d");
      if (A.currentKey() != "g" || A.currentVal() != 30)
        cout << "Remove_value: Test 2 failed" << endl;
      if (A.pre_string() != ideal2)
        cout << "Remove_value: Test 22 failed" << endl;
      A.remove("g");
      if (A.hasCurrent())
        cout << "Remove_value: Test 3 failed" << endl;
      if (A.pre_string() != ideal3)
        cout << "Remove_value: Test 32 failed" << endl;
      return 0;
    }
    case GetValue_value:
    {
      if (A.contains("f"))
        cout << "GetValue_value: Test 1 failed" << endl;
      A.setValue("a", 1);
      A.setValue("b", 5);
      A.setValue("e", 10);
      A.setValue("h", 15);
      A.setValue("f", 20);
      A.setValue("i", 100);

      if (A.getValue("f") != 20)
        cout << "GetValue_value: Test 2 failed" << endl;

      A.remove("f");

      if (A.contains("f"))
        cout << "GetValue_value: Test 3 failed" << endl;

      return 0;
    }
    case Repeated_setValue:
    {
      A.setValue("d", 2);
      A.setValue("d", 5);

      if (A.size() != 1)
        cout << "Repeated_setValue: Test 1 failed" << endl;

      if (A.getValue("d") != 5)
        cout << "Repeated_setValue: Test 2 failed" << endl;

      A.setValue("d", 1);

      if (A.getValue("d") != 1)
        cout << "Repeated_setValue: Test 3 failed" << endl;

      A.remove("d");

      if (A.size() != 0)
        cout << "Repeated_setValue: Test 4 failed" << endl;

      return 0;
    }
    case MultiString_equals:
    {
      A.clear();
      B.clear();
      if (A.to_string() != B.to_string())
        cout << "MultiString_equals: Test 1 failed" << endl;

      A.setValue("a", 1);
      A.setValue("b", 5);
      A.setValue("e", 10);
      A.setValue("h", 15);
      A.setValue("f", 20);
      A.setValue("i", 100);

      if (A.to_string() == B.to_string())
        cout << "MultiString_equals: Test 2 failed" << endl;

      B.setValue("a", 1);
      B.setValue("b", 5);
      B.setValue("e", 10);
      B.setValue("h", 15);
      B.setValue("f", 20);
      B.setValue("i", 100);

      if (A.to_string() != B.to_string())
        cout << "MultiString_equals: Test 3 failed" << endl;

      B.clear();
      B.setValue("i", 100);
      B.setValue("f", 20);
      B.setValue("h", 15);
      B.setValue("e", 10);
      B.setValue("b", 5);
      B.setValue("a", 1);

      if (A.to_string() != B.to_string())
        cout << "MultiString_equals: Test 4 failed" << endl;

      if (A.pre_string() == B.pre_string())
        cout << "MultiString_equals: Test 5 failed" << endl;

      B.clear();
      B.setValue("a", 10);
      B.setValue("b", 50);
      B.setValue("e", 100);
      B.setValue("h", 150);
      B.setValue("f", 200);
      B.setValue("i", 1000);

      if (A.to_string() == B.to_string())
        cout << "MultiString_equals: Test 6 failed" << endl;
      return 0;
    }

    case ToString_equals:
    {
      std::string ideal = "a : 1\nb : 5\ne : 10\nf : 20\nh : 15\ni : 100\n";
      A.setValue("a", 1);
      A.setValue("b", 5);
      A.setValue("e", 10);
      A.setValue("h", 15);
      A.setValue("f", 20);
      A.setValue("i", 100);
      std::string val = A.to_string();
      if (val != ideal)
        cout << "ToString_equals: Test 1 failed" << endl;
      return 0;
    }
    case PreString_equals:
    {
      std::string ideal1 = "b\na\nf (RED)\ne\nh\ni (RED)\n";
      std::string ideal2 =
          "heat\neradicate (RED)\nbolstering\nabjuration (RED)\nfeather\ninsignia\n";
      std::string ideal3 =
          "heat\neradicate (RED)\nabjuration\nabbreviation (RED)\nbolstering (RED)\n"
          "feather\ngodsend (RED)\njustify (RED)\ninsignia\nquizzical\nleaflet (RED)\nsolemnly (RED)\n";
      A.setValue("a", 1);
      A.setValue("b", 5);
      A.setValue("e", 10);
      A.setValue("h", 15);
      A.setValue("f", 20);
      A.setValue("i", 100);

      if (A.pre_string() != ideal1)
        cout << "PreString_equals: Test 1 failed" << endl;

      B.setValue("insignia", 100);
      B.setValue("feather", 20);
      B.setValue("heat", 15);
      B.setValue("eradicate", 10);
      B.setValue("bolstering", 5);
      B.setValue("abjuration", 1);

      if (B.pre_string() != ideal2)
        cout << "PreString_equals: Test 2 failed" << endl;

      B.setValue("justify", 100);
      B.setValue("leaflet", 20);
      B.setValue("godsend", 15);
      B.setValue("quizzical", 10);
      B.setValue("solemnly", 5);
      B.setValue("abbreviation", 1);

      if (B.pre_string() != ideal3)
        cout << "PreString_equals: Test 3 failed" << endl;
      return 0;
    }
    case Contains_value:
    {
      if (A.contains("d"))
        cout << "Contains_value: Test 1 failed" << endl;

      A.setValue("d", 1);
      if (!A.contains("d"))
        cout << "Contains_value: Test 2 failed" << endl;

      A.remove("d");
      if (A.contains("d"))
        cout << "Contains_value: Test 1 failed" << endl;
      return 0;
    }
    }
    return 255;
  }

// Now run the test cases from inside an int main loop
int main(int argc, char *argv[])
{
  Dictionary A;
  Dictionary B;
  uint8_t testsPassed = 0;
  for (int i = 0; i < NUM_TESTS; i++)
  {
    testStatus = 0;
    cout << "Running test " << testName(i) << "..." << endl;
    if (setjmp(test_crash) == 0)
    {
      runTest(&A, &B, i);
      cout << "Test " << testName(i) << " passed" << endl;
      testsPassed++;
    }
    else
    {
      cout << RED << "Test " << testName(i) << " failed" << NC << endl;
    }
  }
  cout << GREEN << "Passed " << (int)testsPassed << " out of " << NUM_TESTS << " tests" << NC << endl;
  return 0;
}
