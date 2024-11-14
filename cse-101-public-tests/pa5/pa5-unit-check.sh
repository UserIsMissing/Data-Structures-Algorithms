#!/bin/bash
RELATIVE_PATH="../cse-101-public-tests/pa5"

echo "Press Enter To Continue with List Unit Test"
read verbose

echo ""
echo ""

g++ -std=c++17 -Wall -c -g "$RELATIVE_PATH/"ModelListTest.cpp List.cpp
g++ -std=c++17 -Wall -o ModelListTest ModelListTest.o List.o

timeout 10 valgrind --leak-check=full -v ./ModelListTest -v > ListTest-out.txt 2> ListTest-mem.txt
if [ $? -eq 124 ]; then
   echo -e "${RED} MODEL LIST TEST TIMED OUT ${NC}"
fi

cat ListTest-out.txt
echo
echo "Press Enter for Memory Leaks Report:"
read verbose
cat ListTest-mem.txt

rm -f *.o

