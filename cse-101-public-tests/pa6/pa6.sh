#!/bin/bash
# usage: ../cse-101-public-tests/pa6/pa6.sh
# (run within your pa6 directory to test your code)

RELATIVE_PATH="../cse-101-public-tests/pa6"
EXE_ALL=( pa6-func-check.sh pa6-lunit-check.sh pa6-bunit-check.sh pa6-make-check.sh )
EXE_RANGE=$((${#EXE_ALL[*]} - 1))
echo $EXE_RANGE
for i in $(seq 0 $EXE_RANGE); do
  FULLPATH="$RELATIVE_PATH/${EXE_ALL[i]}"
  chmod +x $FULLPATH
  ./$FULLPATH
done
