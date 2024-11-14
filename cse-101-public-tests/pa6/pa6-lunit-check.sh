#!/bin/bash
RELATIVE_PATH="../cse-101-public-tests/pa6"

echo ""
echo ""

echo "Press Enter To Continue with List Unit Test"
read verbose

echo ""
echo ""

g++ -std=c++17 -Wall -c -g "$RELATIVE_PATH/"ModelListTest.cpp List.cpp
g++ -std=c++17 -Wall -o ModelListTest ModelListTest.o List.o

timeout 5 valgrind --leak-check=full -v ./ModelListTest -v > ListTest-out.txt 2> ListTest-mem.txt

cat ListTest-out.txt
echo
echo "Press Enter for Memory Leaks Report:"
read verbose
cat ListTest-mem.txt

rm -f *.o ModelListTest
