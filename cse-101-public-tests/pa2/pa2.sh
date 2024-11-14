#!/bin/bash
# usage: ../cse-101-public-tests/pa2/pa2.sh
# (run within your pa2 directory to test your code)

RELATIVE_PATH="../cse-101-public-tests/pa2"
EXE_ALL=( pa2-func-check.sh pa2-lunit-check.sh pa2-gunit-check.sh pa2-make-check.sh )
EXE_RANGE=$((${#EXE_ALL[*]} - 1))
echo $EXE_RANGE
for i in $(seq 0 $EXE_RANGE); do
  FULLPATH="$RELATIVE_PATH/${EXE_ALL[i]}"
  chmod +x $FULLPATH
  ./$FULLPATH
done
