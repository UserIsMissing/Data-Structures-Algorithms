#!/bin/bash
RELATIVE_PATH="../cse-101-public-tests/pa4"
TIME=8
RED='\033[0;31m'
NC='\033[0m' # No Color

echo ""
echo ""

rm -f *.o Sparse ModelMatrixTest

echo "Press Enter To Continue with MatrixTest Results"
read verbose

echo ""
echo ""

gcc -c -std=c17 -Wall -g "$RELATIVE_PATH/"ModelMatrixTest.c Matrix.c List.c
gcc -o ModelMatrixTest ModelMatrixTest.o Matrix.o List.o

timeout 20 /usr/bin/time -po time.txt valgrind --leak-check=full -v ./ModelMatrixTest -v > MatrixTest-out.txt 2> MatrixTest-mem.txt
t=$?
userTime=`perl -ane 'print $F[1] if $F[0] eq "user"' time.txt`
tooSlow=$(echo "$userTime > $TIME" |bc -l)
cat MatrixTest-mem.txt
cat MatrixTest-out.txt
if [ $t -eq 124 ] || [ $tooSlow -eq 1 ]; then
  echo -e "${RED} MATRIX MODEL TEST TIMED OUT ${NC}"
fi

rm -f garbage MatrixTest-mem.txt MatrixTest-out.txt

