#!/bin/bash
# usage: ../cse-101-public-tests/pa7/pa7.sh
# (run within your pa7 directory to test your code)

RELATIVE_PATH="../cse-101-public-tests/pa7"
EXE_ALL=( pa7-func-check.sh pa7-unit-check.sh pa7-make-check.sh )
EXE_RANGE=$((${#EXE_ALL[*]} - 1))
echo $EXE_RANGE
for i in $(seq 0 $EXE_RANGE); do
  FULLPATH="$RELATIVE_PATH/${EXE_ALL[i]}"
  chmod +x $FULLPATH
  ./$FULLPATH $1
done
