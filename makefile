# Make file for word ladder assignment.

CC	= g++ -g -Wall -pedantic -std=c++11 -pthread

all: primes

primes: primes.o
	$(CC) -o primes primes.o

primes.o: primes.cpp
	$(CC) -c primes.cpp

# -----
# clean by removing object files.

clean:
	rm	$(OBJS)

