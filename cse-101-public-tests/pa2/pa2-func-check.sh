#!/bin/bash
RELATIVE_PATH="../cse-101-public-tests/pa2"

NUMTESTS=6
PNTSPERTEST=4
let MAXPTS=$NUMTESTS*$PNTSPERTEST
let MAXPTS=20

rm -f *.o

gcc -c -Wall -std=c17 -g FindPath.c Graph.c List.c
gcc -o FindPath FindPath.o Graph.o List.o


echo ""
echo ""

pathtestspassed=$(expr 0)
echo "Please be warned that the following tests discard all output to stdout/print stderr separately"
echo "FindPath tests: If nothing between '=' signs, then test is passed"
echo "Press enter to continue"
read verbose
for NUM in $(seq 1 $NUMTESTS); do
  rm -f outfile$NUM.txt
  timeout 5 ./FindPath "$RELATIVE_PATH/"infile$NUM.txt outfile$NUM.txt &> garbage >> garbage #all stdout/stderr thrown away
  if [ $? -eq 124 ]; then
    echo -e "${RED} FindPath TEST TIMED OUT ${NC}"
  fi
  diff -bBwu outfile$NUM.txt "$RELATIVE_PATH/"model-outfile$NUM.txt > diff$NUM.txt &>> diff$NUM.txt
  echo "FindPath Test $NUM:"
  echo "=========="
  cat diff$NUM.txt
  echo "=========="
  if [ -e diff$NUM.txt ] && [[ ! -s diff$NUM.txt ]]; then # increment number of tests passed counter
    let pathtestspassed+=1
  fi
done

echo ""
echo ""

let pathtestspoints=$PNTSPERTEST*$pathtestspassed
if [ "$pathtestspoints" -gt "$MAXPTS" ]; then # max 20 points
  let pathtestspoints=$(expr $MAXPTS)
fi
echo "Passed $pathtestspassed FindPath tests for a total of $pathtestspoints / $MAXPTS points"

echo ""
echo ""

rm -f garbage

