# cse101-pt.f23/pa2

The following is a set of performance tests to run on your FindPath program. It
takes six example input files and compares your results to our correct model
outputs. It also includes a testing client for your List and Graph ADT's as per
the requirements of PA2. We have made this available to you to check your work
before making your final submission.

## Usage

```bash
chmod +x ./../cse-101-public-tests/pa2/pa2.sh
./../cse-101-public-tests/pa2/pa2.sh
```

The FindPath tests will print out the difference between your output and the correct output,
using the `diff` command. Lack of any output between the set of "=========="
means that your program is running correctly.

Any lines prefixed with `-` are from your own output, and are incorrect. Any
lines prefixed with `+` are from the correct output, and are missing in your
output.

The ListTest and GraphTest will list all of unit tests they perform and which
you've passed/failed.

## Removal

The following command will remove all text files and shell scripts in your
directory. Since you should not have any files that end in `.txt` or `.sh`
anyway, this should serve to delete all the files we gave you.

```bash
rm -f *.txt *.sh
```
