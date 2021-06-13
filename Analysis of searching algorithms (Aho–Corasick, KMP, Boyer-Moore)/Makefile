CC = g++
CFLAGS = -Wall -Wextra 
EXE  = algo_test

build : algo_test.o BoyerMoore.o Aho_Corasick.o KMP.o

BoyerMoore.o : BoyerMoore.cpp
	$(CC) BoyerMoore.cpp -c $(CFLAGS)

Aho_Corasick.o : Aho_Corasick.cpp
	$(CC) Aho_Corasick.cpp -c $(CFLAGS)
KMP.o :	KMP.cpp
	$(CC) KMP.cpp -c $(CFLAGS)

algo_test.o : algo_test.cpp BoyerMoore.o Aho_Corasick.o KMP.o
	$(CC) algo_test.cpp BoyerMoore.o Aho_Corasick.o KMP.o -o algo_test $(CFLAGS)

run_test:
	./algo_test

.PHONY: clean

clean:
	rm -rf *.o $(EXE)
