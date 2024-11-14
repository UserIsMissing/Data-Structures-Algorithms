#!/bin/bash
RELATIVE_PATH="../cse-101-public-tests/pa3"
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo ""
echo ""

rm -f *.o FindComponents

echo "Press Enter To Continue with GraphTest Results"
read verbose

echo ""
echo ""

gcc -c -std=c17 -Wall -g "$RELATIVE_PATH/"ModelGraphTest.c Graph.c List.c
gcc -o ModelGraphTest ModelGraphTest.o Graph.o List.o

timeout 6 valgrind --leak-check=full -v ./ModelGraphTest -v > GraphTest-out.txt 2> GraphTest-mem.txt
if [ $? -eq 124 ]; then
    echo -e "${RED} ModelGraphTest TEST TIMED OUT ${NC}"
fi

cat GraphTest-mem.txt
cat GraphTest-out.txt

rm -f garbage

