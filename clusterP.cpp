// Matthew Rutigliano
// 22 April 2021
// Revision history: See "clusterP.h"

#include "clusterP.h"
#include <memory>
#include <iostream>

int clusterP::clusterCount = 0;

clusterP::clusterP() {
	dubSeed = ++clusterCount;
	dubCount = 0;
	primeArrSize = dubSeed * seedScaler;
	primeArr = new dubPrime*[primeArrSize];
	for(dubCount; dubCount<primeArrSize; dubCount++) {
		primeArr[dubCount] = new dubPrime((dubSeed + dubCount) * seedScaler);
	}
}

clusterP::clusterP(unsigned int seed) {
	dubSeed = seed;
	clusterCount++;
	dubCount = 0;
	primeArrSize = dubSeed * seedScaler;
	primeArr = new dubPrime*[primeArrSize];
	for(dubCount; dubCount<primeArrSize; dubCount++) {
		primeArr[dubCount] = new dubPrime((dubSeed + dubCount) * seedScaler);
	}
}

clusterP::clusterP(const clusterP& c) {
	clusterCount++;
	copy(c);
}

clusterP::clusterP(clusterP&& c) {
	primeArrSize = c.primeArrSize;
	primeArr = c.primeArr;
	dubCount = c.dubCount;
	dubSeed = c.dubSeed;
	
	c.primeArrSize = 0;
	c.dubCount = 0;
	c.dubSeed = 0;
	c.primeArr = nullptr;
}

clusterP& clusterP::operator=(const clusterP& c) {
	if (&c != this) {
		for(int i=0; i<primeArrSize; i++) {
			delete primeArr[i];
		}
		delete primeArr;
		copy(c);
	}
	return *this;
}

clusterP& clusterP::operator=(clusterP&& c) {
	std::swap(dubCount, c.dubCount);
	std::swap(dubSeed, c.dubSeed);
	std::swap(primeArrSize, c.primeArrSize);
	std::swap(primeArr, c.primeArr);
	return *this;
}

clusterP::~clusterP() {
	clearArr();
}

void clusterP::clearArr() {
	for(int i=0; i<primeArrSize; i++) {
		delete primeArr[i];
	}
	delete primeArr;
}

int clusterP::minimum(int p) {
	int min = primeArr[0]->query(p);
	int res;
	for(int i=1; i<primeArrSize; i++) {
		res = query(i, p);
		min = min < res ? min : res;
	}
	return min;
}

int clusterP::maximum(int p) {
	int max = primeArr[0]->query(p);
	int res;
	for(int i=1; i<primeArrSize; i++) {
		res = query(i, p);
		max = max > res ? max : res;
	}
	return max;
}

int clusterP::inversions(int p) {
	int inv = 0;
	for(int i=0; i<primeArrSize-1; i++) {
		if (primeArr[i]->getMode() != primeArr[i+1]->getMode()) {
			if (query(i, p) == query(i+1, p))
				inv++;
		}
	}
	return inv;
}

int clusterP::query(int x, int p) {
	if(!(primeArr[x]->getActive()))
		replace(x);
	return primeArr[x]->query(p);
}

// Helper functions
void clusterP::copy(const clusterP& c) {
	dubCount = c.dubCount;
	dubSeed = c.dubSeed;
	primeArrSize = c.primeArrSize;
	primeArr = new dubPrime*[primeArrSize];
	for(int i=0; i<primeArrSize; i++) {
		primeArr[i] = new dubPrime(*c.primeArr[i]);
	}
}

void clusterP::replace(int x) {
	delete primeArr[x];
	primeArr[x] = new dubPrime((dubSeed + dubCount++) * seedScaler);
}

// Addition operators
clusterP clusterP::operator+(const clusterP& clust) {
	clusterP sum;
	sum.clearArr();
	sum.primeArrSize = primeArrSize + clust.primeArrSize;
	sum.primeArr = new dubPrime*[sum.primeArrSize];
	sum.dubCount = 0;
	for(sum.dubCount; sum.dubCount<primeArrSize; sum.dubCount++) {
		sum.primeArr[sum.dubCount] = new dubPrime(*primeArr[sum.dubCount]);
	}
	for(sum.dubCount; sum.dubCount<sum.primeArrSize; sum.dubCount++) {
		sum.primeArr[sum.dubCount] = new dubPrime(*clust.primeArr[sum.dubCount - primeArrSize]);
	}
	return sum;
}

clusterP clusterP::operator+(const dubPrime& dub) {
	clusterP sum;
	sum.clearArr();
	sum.primeArrSize = primeArrSize + 1;
	sum.primeArr = new dubPrime*[sum.primeArrSize];
	sum.dubCount = 0;
	for(sum.dubCount; sum.dubCount<primeArrSize; sum.dubCount++)
		sum.primeArr[sum.dubCount] = new dubPrime(*primeArr[sum.dubCount]);
	sum.primeArr[sum.dubCount++] = new dubPrime(dub);
	return sum;
}

clusterP& clusterP::operator+=(const clusterP& clust) {
	dubPrime** newArr = new dubPrime*[primeArrSize + clust.primeArrSize];
	for(int i=0; i<primeArrSize; i++)
		newArr[i] = primeArr[i];
	for(int i=0; i<clust.primeArrSize; i++)
		newArr[i + primeArrSize] = new dubPrime(*(clust.primeArr[i]));
	primeArrSize += clust.primeArrSize;
	delete [] primeArr;
	primeArr = newArr;
	return *this;
}

clusterP& clusterP::operator+=(const dubPrime& dub) {
	dubPrime** newArr = new dubPrime*[primeArrSize+1];
	for(int i=0; i<primeArrSize; i++)
		newArr[i] = primeArr[i];
	newArr[primeArrSize++] = new dubPrime(dub);
	delete [] primeArr;
	primeArr = newArr;
	return *this;
}

// Compare size of arrays
bool clusterP::operator>(const clusterP& clust) {
	return primeArrSize > clust.primeArrSize;
}

bool clusterP::operator>=(const clusterP& clust) {
	return primeArrSize >= clust.primeArrSize;
}
bool clusterP::operator<(const clusterP& clust) {
	return primeArrSize < clust.primeArrSize;
}

bool clusterP::operator<=(const clusterP& clust) {
	return primeArrSize <= clust.primeArrSize;
}

bool clusterP::operator==(const clusterP& clust) {
	return primeArrSize == clust.primeArrSize;
}

bool clusterP::operator!=(const clusterP& clust) {
	return primeArrSize != clust.primeArrSize;
}

bool clusterP::operator>(int val) {
	return primeArrSize > val;
}

bool clusterP::operator>=(int val) {
	return primeArrSize >= val;
}
bool clusterP::operator<(int val) {
	return primeArrSize < val;
}

bool clusterP::operator<=(int val) {
	return primeArrSize <= val;
}

bool clusterP::operator==(int val) {
	return primeArrSize == val;
}

bool clusterP::operator!=(int val) {
	return primeArrSize != val;
}