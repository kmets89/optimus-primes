/* Kaylan Mettus
* CS302-1002
* Assignment #7
* 
* This program finds the number of primes up to a limit */

#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>

using namespace std;

// Loops over numbers up to user-specified limit and increases the
// count if each number is prime
void primeCnt();
//Determines if a number is prime using an estimated square root
bool isPrime(int);
// Increments the count of prime numbers
void incPrimeCnt();
// Increments the counter for numbers being assessed
int getNext();

mutex myLock;
int numPrimes = 0, counter = 0, lim;

int main(int argc, char *argv[])
{
	stringstream ss;
	int size;
	thread *thds = new thread[size];
		
	 // check command line args
	if (argc == 1) {
		cout << "Usage: primes -t <threadCount> -l <limitValue>" << endl;
		return 0;
	}
	
	if (argc != 5) {
		cout << "Error, invalid command line options." << endl;
		return	0;
	}
	
	if (string(argv[1]) != "-t") {
		cout << "main: Invalid thread count specifier." << endl;
		return 0;
	}
	
	if (string(argv[2]) != "") {
		ss << argv[2];
		ss >> size;
		if (size < 1)
		{
			cout << "main: Invalid thread count value." << endl;
			return 0;
		}
	}
	
	if (string(argv[3]) != "-l") {
		cout << "main: Invalid limit value specifier." << endl;
		return 0;
	}
	
	if (string(argv[4]) != "") {
		ss.clear();
		ss << argv[4];
		ss >> lim;
		if ( lim < 1)
		{
		cout << "main: Invalid limit value." << endl;
		return 0;
		}
	}

	// show results with times 
	// start timer... 
	auto t1 = chrono::high_resolution_clock::now(); 
	
	for (int i = 0; i < size; i++)
		thds[i] = thread(primeCnt);
		
	for (int j = 0; j < size; j++)
		thds[j].join();
	
	// show results with times 
	auto t2 = chrono::high_resolution_clock::now();
	cout << "Program took: " 
	<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() 
	<< " milliseconds" << endl;
	
	cout <<  numPrimes << endl;

	delete [] thds;

	return 0;
}
 
void primeCnt()
{
	int i = 0;
	cout << endl;
	while ((i = getNext()) <= lim)
	{
		if (isPrime(i))
			incPrimeCnt();
	} 
}

bool isPrime(int num)
{
	int k = num, kNext = 1;
	
	if (num == 1)
		return false;
	
	// 2 is prime
	if (num == 2)
		return true;
	
	// any num divisible by 2 is not prime
	if (num % 2 == 0)
		return false;
	
	// find estimated sqrt
	while ((k - kNext) > 1)
	{
		k = (k + kNext) / 2;
		kNext = num / k;
	}
	k++; //round up
	
	// check if divisible by odd numbers up to the est sqrt to see if prime
	for (int i = 3; i < k; i+= 2)
		if (num % i == 0)
			return false;
	return true;
}

void incPrimeCnt()
{
	lock_guard<mutex> lock(myLock);
	
	numPrimes++;
}

int getNext()
{	
	lock_guard<mutex> lock(myLock);
	
	if (counter > 2)
		counter += 2;
	// after 2, no need to check even numbers
	else
		counter++;
	return counter;
}
