#!/bin/bash
# usage: ../cse-101-public-tests/pa4/pa4.sh
# (run within your pa4 directory to test your code)

RELATIVE_PATH="../cse-101-public-tests/pa4"
EXE_ALL=( pa4-func-check.sh pa4-lunit-check.sh pa4-munit-check.sh pa4-make-check.sh )
EXE_RANGE=$((${#EXE_ALL[*]} - 1))
echo $EXE_RANGE
for i in $(seq 0 $EXE_RANGE); do
  FULLPATH="$RELATIVE_PATH/${EXE_ALL[i]}"
  chmod +x $FULLPATH
  ./$FULLPATH
done
