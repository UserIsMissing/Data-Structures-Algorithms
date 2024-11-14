#!/bin/bash
RELATIVE_PATH="../cse-101-public-tests/pa6"
TIME=8

echo ""
echo ""

echo "Press Enter To Continue with ModelBigIntegerTest Results"
read verbose

echo ""
echo ""

g++ -std=c++17 -Wall -c -g "$RELATIVE_PATH/"ModelBigIntegerTest.cpp BigInteger.cpp List.cpp -lm
g++ -std=c++17 -Wall -o ModelBigIntegerTest ModelBigIntegerTest.o BigInteger.o List.o -lm

timeout $TIME valgrind --leak-check=full -v ./ModelBigIntegerTest -v > BITest-out.txt

cat BITest-out.txt

rm -f *.o BITest-out.txt ModelBigIntegerTest
