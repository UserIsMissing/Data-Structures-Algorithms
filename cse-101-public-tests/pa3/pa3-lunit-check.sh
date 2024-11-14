#!/bin/bash
RELATIVE_PATH="../cse-101-public-tests/pa3"
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo ""
echo ""

echo "Press Enter To Continue with ListTest Results"
read verbose

gcc -c -std=c17 -Wall -g "$RELATIVE_PATH/"ModelListTest.c List.c
gcc -o ModelListTest ModelListTest.o List.o

timeout 6 ./ModelListTest -v > ListTest-out.txt
if [ $? -eq 124 ]; then
    echo -e "${RED} ModelListTest TEST TIMED OUT ${NC}"
fi

cat ListTest-out.txt

rm -f garbage

