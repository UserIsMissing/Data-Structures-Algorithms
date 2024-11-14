#!/bin/bash

RELATIVE_PATH="../cse-101-public-tests/pa2"

echo ""
echo ""

rm -f *.o

echo ""

echo "Press Enter To Continue with ListTest Results"
read verbose

gcc -c -std=c17 -Wall -g "$RELATIVE_PATH/"ModelListTest.c List.c
gcc -o ModelListTest ModelListTest.o List.o

timeout 5 ./ModelListTest -v
if [ $? -eq 124 ]; then
    echo -e "${RED} ModelListTest TEST TIMED OUT ${NC}"
fi

echo ""
echo ""

rm -f garbage