# ------------------------------------------------------------------------------
# Cole Schreiner
# caschrei
# pa1
# ------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes Lex
# make ListClient        makes ListClient
# make clean             removes all binaries
# make checkClient       checks ListClient for memory errors
# make checkLex          checks Lex for memory errors
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -g -std=c17 -Wall -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -g -std=c17 -Wall -c Lex.c

ListClient: ListClient.o List.o
	gcc -g -std=c17 -Wall -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -g -std=c17 -Wall -c ListClient.c

List.o : List.c List.h
	gcc -g -std=c17 -Wall -c List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o

checkClient : 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./ListClient

checkLex :
	valgrind --leak-check=full ./Lex

ListTest : ListTest.o List.o
	gcc -g -std=c17 -Wall -o ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	gcc -g -std=c17 -Wall -c ListTest.c