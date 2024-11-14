#!/bin/bash
RELATIVE_PATH="../cse-101-public-tests/pa1"
echo "Press Enter To Continue with ListTest Results"
read verbose

echo ""
echo ""

gcc -c -std=c17 -Wall -g "$RELATIVE_PATH/ModelListTest.c" List.c
gcc -std=c17 -o ModelListTest ModelListTest.o List.o

timeout 5 valgrind --leak-check=full -v ./ModelListTest -v > ListTest-out.txt 2> ListTest-mem.txt
if [ $? -eq 124 ]; then
    echo -e "${RED} ModelListTest TEST TIMED OUT ${NC}"
fi

cat ListTest-out.txt

echo "List Valgrind Test: (press enter)"
read garbage
cat ListTest-mem.txt

rm -f *.o ModelListTest* Lex ListTest-out.txt ListTest-mem.txt

