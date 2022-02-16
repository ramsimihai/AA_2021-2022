# 321CA - Soare Mihai Daniel - Maximum Flow
CC = g++
CFLAGS = -Wall -Wextra -O2
LDLIBS = -lm

build: Dinics Edmonds-Karp Greedy

run-best:
	./test1

run-p1:
	./test2
run-p2:
	./test3

Dinics:
	$(CC) $(CFLAGS) Dinics.cpp -o test1

Edmonds-Karp:
	$(CC) $(CFLAGS) Edmonds-Karp.cpp -o test2

Greedy:
	$(CC) $(CFLAGS) Greedy.cpp -o test3

.PHONY: clean

clean:
	rm -rf *.o test1 test2 test3 test.in test.out
