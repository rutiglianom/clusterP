// Matthew Rutigliano
// 22 April 2021
// Revision History: Data members, constructor, copy constructor, overloaded assignment operator written 4/14/21
// Move constructor, move assignment operator, minimum, maximum, inversions written 4/17/21
// Addition, destructive addition, comparison operators written 5/17/21

// Class Invariant:
// clusterP object encapsulates a variable amount of dubPrime subobjects
// Seed parameter of constructor influences amount of subobjects,
//     range of values they get as seeds
// Minimum and maximum will query all the dubPrime subobjects with value p, returning
//     the minimum and maximum value respectively
// Inversions will return the number of inversions when subobjects are queried with value p
//     (Inversion is when two neighboring dubPrime subobjects are in opposite modes and query to
//      the same value)
// Once they enter down mode, dubPrime subobjects will remain in down mode for the remainder
//     of the clusterP object's life
// Deep copying and move semantics are supported
// Initializing multiple objects with no seed will produce objects of increasing size
// Adding dubPrime and clusterP yields clusterP with dubPrime in internal array
// Adding two clusterP objects yields clusterP with internal array containing all values from both objects
// Global commutative addition function in P4.cpp (compiler won't link when it's in clusterP.cpp)
// Shortcut addition assignment is supported for both additions
// Comparison operators compare size of arrays between clusterP objects, integers

// Interface Invariant:
// Optional seed value must be greater than 0 to guarantee functionality
// No states need to be monitored by client

#include "dubPrime.h"

#ifndef CLUSTERP_H
#define CLUSTERP_H

class clusterP {
	private:
	const int seedScaler = 2;
	static int clusterCount;
	int primeArrSize;
	int dubCount;
	int dubSeed;
	dubPrime** primeArr;
	
	int query(int x, int p);
	
	void replace(int x);
	
	void copy(const clusterP& c);
	
	void clearArr();
	
	public:
	// No states need to be monitored by user
	clusterP();
	
	clusterP(unsigned int seed);
	
	clusterP(const clusterP& c);
	
	clusterP(clusterP&& c);
	
	clusterP& operator=(const clusterP& c);
	
	clusterP& operator=(clusterP&& c);
	
	~clusterP();
	
	int minimum(int p);
	
	int maximum(int p);
	
	int inversions(int p);
	
	clusterP operator+(const clusterP& clust);
	
	clusterP operator+(const dubPrime& dub);
	
	clusterP& operator+=(const clusterP& clust);
	
	clusterP& operator+=(const dubPrime& dub);
	
	bool operator>(const clusterP& clust);
	
	bool operator>=(const clusterP& clust);
	
	bool operator<(const clusterP& clust);
	
	bool operator<=(const clusterP& clust);
	
	bool operator==(const clusterP& clust);
	
	bool operator!=(const clusterP& clust);
	
	bool operator>(int val);
	
	bool operator>=(int val);
	
	bool operator<(int val);
	
	bool operator<=(int val);
	
	bool operator==(int val);
	
	bool operator!=(int val);
	
};

#endif

// Implementation Invariant: 
// primeArr is double pointer pointing to array of clusterP pointers on heap. This allows for variable cardinality
// Internal value primeArrSize determined by multiplying seed with seedScaler
// Internal dubPrime seeds determined by multiplying the sum of seed and each array index with seedScaler
// dubPrimes are internally monitored with every query and replaced when deactivated
// Replacement gets a new seed value to avoid another deactivation
// Shortcut addition operators create new array, copy all values and new values into it, update size, and delete
//     old array