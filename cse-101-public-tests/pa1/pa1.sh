#!/bin/bash
# usage: ../cse-101-public-tests/pa1/pa1.sh
# (run within your pa1 directory to test your code)

RELATIVE_PATH="../cse-101-public-tests/pa1"
EXE_ALL=( pa1-func-check.sh pa1-unit-check.sh pa1-make-check.sh )
EXE_RANGE=$((${#EXE_ALL[*]} - 1))
for i in $(seq 0 $EXE_RANGE); do
  FULLPATH="$RELATIVE_PATH/${EXE_ALL[i]}"
  chmod +x $FULLPATH
  ./$FULLPATH
done
