// Matthew Rutigliano
// 22 April 2021
// Revision history: See "dubPrime.h"

#include "dubPrime.h"

dubPrime::dubPrime() {
	mode = true;
	queryLimit = ++dubPrimeCount * queryLimitMultiplier;
	x = dubPrimeCount * xMin;
	x = nextPrime(x);
	isActive = true;
	updateActive(x);
}

dubPrime::dubPrime(int seed) {
	mode = true;
	queryLimit = ++dubPrimeCount * queryLimitMultiplier;
	x = seed * xMin;
	x = nextPrime(x);
	isActive = true;
	updateActive(x);
}

dubPrime::dubPrime(const dubPrime& dub) {
	mode = dub.mode;
	queryCount = dub.queryCount;
	queryLimit = dub.queryLimit;
	x = dub.x;
	isActive = dub.isActive;
	dubPrimeCount++;
}

dubPrime& dubPrime::operator=(const dubPrime& dub) {
	if (&dub != this) {
		mode = dub.mode;
		queryCount = dub.queryCount;
		queryLimit = dub.queryLimit;
		x = dub.x;
		isActive = dub.isActive;
	}
	return *this;
}


int dubPrime::dubPrimeCount = 0;

// Post Condition: Object may transition from up mode to down mode
// Object may become inactive
int dubPrime::query(int p) {
	int result = -1;
	if (isActive) {
		int e = p + 1;
		if (!isEven(e)) { e++; }

		if (mode) {
			result = x + e;
			result = nextPrime(result);
		} else {
			result = x - e;
			result = prevPrime(result);
		}

		mode = ++queryCount < queryLimit;
		updateActive(result);
	}
	return result;
}

// Post Condition: Object will stay in or transition to up mode
void dubPrime::reset() {
	if (isActive) {
		queryCount = 0;
		mode = true;
	}
}

// Post Condition: Object will stay in or transition to up mode
void dubPrime::revive() {
	if (isActive) {
		mode = true;
		queryLimit = (queryLimit * dubPrimeCount) + queryCount;
	}
}

bool dubPrime::getActive() {
	return isActive;
}

bool dubPrime::getMode() {
	return mode;
}


bool dubPrime::isEven(int n) {
	return ((n % 2) == 0);
}

bool dubPrime::isPrime(int n) {
	bool result = !(isEven(n));
	if (result) {
		for (int i = 3; i < n / 2; i=i+2) {
			if ((n % i) == 0) {
				result = false;
				break;
			}
		}
	}
	return result;
}

int dubPrime::nextPrime(int n) {
	int next = n;
	if (isEven(next)) { next++; }
	while(!isPrime(next += 2)) {}
	return next;
}

void dubPrime::updateActive(int n) {
	if (isActive)
		isActive = n >= xMin;
}

int dubPrime::prevPrime(int n) {
	int prev = n;
	if (isEven(prev)) { prev--; }
	while(!isPrime(prev -= 2)) {}
	return prev;
}

dubPrime dubPrime::operator++() {
	x = nextPrime(x);
	updateActive(x);
	return *this;
}

dubPrime dubPrime::operator++(int dum) {
	dubPrime oldState = *this;
	x = nextPrime(x);
	updateActive(x);
	return oldState;
}

dubPrime dubPrime::operator--() {
	x = prevPrime(x);
	updateActive(x);
	return *this;
}

dubPrime dubPrime::operator--(int dum) {
	dubPrime oldState = *this;
	x = prevPrime(x);
	updateActive(x);
	return oldState;
}

dubPrime dubPrime::operator+(const dubPrime& dub) {
	dubPrime sum;
	if (isActive) 
		sum.x = nextPrime(x + dub.x);
	else 
		sum.x = -1;
	sum.updateActive(sum.x);
	return sum;
}

dubPrime dubPrime::operator+(int n) {
	dubPrime sum;
	if (isActive) 
		sum.x = nextPrime(x + n);
	else 
		sum.x = -1;
	sum.updateActive(sum.x);
	return sum;
}

dubPrime dubPrime::operator-(const dubPrime& dub) {
	dubPrime dif;
	if (isActive) 
		dif.x = prevPrime(x - dub.x);
	else 
		dif.x = -1;
	dif.updateActive(dif.x);
	return dif;
}

dubPrime dubPrime::operator-(int n) {dubPrime dif;
	if (isActive) 
		dif.x = prevPrime(x - n);
	else 
		dif.x = -1;
	dif.updateActive(dif.x);
	return dif;
}

dubPrime& dubPrime::operator+=(const dubPrime& dub) {
	x = nextPrime(x + dub.x);
	updateActive(x);
	return *this;
}

dubPrime& dubPrime::operator+=(int n) {
	x = nextPrime(x + n);
	updateActive(x);
	return *this;
}

dubPrime& dubPrime::operator-=(const dubPrime& dub) {
	x = prevPrime(x - dub.x);
	updateActive(x);
	return *this;
}

dubPrime& dubPrime::operator-=(int n) {
	x = prevPrime(x - n);
	updateActive(x);
	return *this;
}

bool dubPrime::operator==(const dubPrime& dub) {
	return x == dub.x;
}

bool dubPrime::operator==(int n) {
	return x == n;
}

bool dubPrime::operator!=(const dubPrime& dub) {
	return x != dub.x;
}

bool dubPrime::operator!=(int n) {
	return x != n;
}

bool dubPrime::operator>(const dubPrime& dub) {
	return x > dub.x;
}

bool dubPrime::operator>(int n) {
	return x > n;
}

bool dubPrime::operator<(const dubPrime& dub) {
	return x < dub.x;
}

bool dubPrime::operator<(int n) {
	return x < n;
}

bool dubPrime::operator>=(const dubPrime& dub) {
	return x >= dub.x;
}

bool dubPrime::operator>=(int n) {
	return x >= n;
}

bool dubPrime::operator<=(const dubPrime& dub) {
	return x <= dub.x;
}

bool dubPrime::operator<=(int n) {
	return x <= n;
}
