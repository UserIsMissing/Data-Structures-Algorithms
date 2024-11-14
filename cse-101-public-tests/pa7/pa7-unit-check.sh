#!/bin/bash
RELATIVE_PATH="../cse-101-public-tests/pa7"

MAXTIME=$(($1*5))

echo ""
echo ""

echo "Press Enter To Continue with Dictionary Unit Test"
read verbose

echo ""
echo ""

g++ -std=c++17 -Wall -c -g "$RELATIVE_PATH/"ModelDictionaryTest.cpp Dictionary.cpp
g++ -std=c++17 -Wall -o ModelDictionaryTest ModelDictionaryTest.o Dictionary.o

timeout $MAXTIME valgrind --leak-check=full -v ./ModelDictionaryTest -v > DictionaryTest-out.txt 

cat DictionaryTest-out.txt 

rm -f *.o ModelDictionaryTest DictionaryTest-out.txt

