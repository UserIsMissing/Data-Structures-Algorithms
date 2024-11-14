#!/bin/bash
# usage: ../cse-101-public-tests/pa8/pa8.sh
# (run within your pa8 directory to test your code)

RELATIVE_PATH="../cse-101-public-tests/pa8"
EXE_ALL=( pa8-func-check.sh pa8-func2-check.sh pa8-unit-check.sh pa8-make-check.sh )
EXE_RANGE=$((${#EXE_ALL[*]} - 1))
echo $EXE_RANGE
for i in $(seq 0 $EXE_RANGE); do
  FULLPATH="$RELATIVE_PATH/${EXE_ALL[i]}"
  chmod +x $FULLPATH
  ./$FULLPATH $1
done
