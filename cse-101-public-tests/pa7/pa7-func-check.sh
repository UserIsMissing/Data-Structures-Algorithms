#!/bin/bash
RELATIVE_PATH="../cse-101-public-tests/pa7"
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

MAXTIME=$(($1*20))

NUMTESTS=5
PNTSPERTEST=3
let MAXPTS=$NUMTESTS*$PNTSPERTEST

echo ""
echo ""

g++ -std=c++17 -Wall -c -g Order.cpp Dictionary.cpp
g++ -std=c++17 -Wall -o Order Order.o Dictionary.o

ordertestspassed=$(expr 0)
echo "Please be warned that the following tests discard all output to stdout while reserving stderr for valgrind output"
echo "Order tests: If nothing between '=' signs, then test is passed"
echo "Press enter to continue"
read verbose
for NUM in $(seq 1 $NUMTESTS); do
  rm -f outfile$NUM.txt
  timeout $MAXTIME /usr/bin/time -po time$NUM.txt valgrind --leak-check=full -v ./Order "$RELATIVE_PATH/"infile$NUM.txt outfile$NUM.txt &> valgrind-out$NUM.txt
  t=$?
  userTime=`perl -ane 'print $F[1] if $F[0] eq "user"' time$NUM.txt`
  tooSlow=$(echo "$userTime > $MAXTIME" |bc -l)
  diff -bBwu outfile$NUM.txt "$RELATIVE_PATH/"model-outfile$NUM.txt &> diff$NUM.txt >> diff$NUM.txt
  echo "Order Test $NUM:"
  echo "=========="
  cat diff$NUM.txt
  if [ $t -eq 124 ] || [ $tooSlow -eq 1 ]; then
    echo -e "${RED}ORDER TEST TIMED OUT (Slower than $MAXTIME) ${NC}"
  fi
  echo "=========="
  if [ -e diff$NUM.txt ] && [[ ! -s diff$NUM.txt ]] && [[ $tooSlow -eq 0 ]] && [[ ! $t -eq 124 ]]; then
    let ordertestspassed+=1
  fi
done

let ordertestpoints=${PNTSPERTEST}*ordertestspassed

echo "Passed $ordertestspassed / $NUMTESTS Order tests"
echo "This gives a total of $ordertestpoints / $MAXPTS points"
echo ""
echo ""

echo "Press Enter To Continue with Valgrind Results for Order"
#TODO find a way to automate detecting if leaks and errors are found and how many
read garbage

for NUM in $(seq 1 $NUMTESTS); do
   echo "Order Valgrind Test $NUM: (Press enter to continue...)"
   read verbose
   echo "=========="
   cat valgrind-out$NUM.txt
   echo "=========="
done

echo ""
echo ""
rm -f *.o Order

