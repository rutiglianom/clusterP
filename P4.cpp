// Matthew Rutigliano
// 20 May 2021
// Revision History: All functions written 5/19/21

// Program Overview:
// Two test programs are run, testDub and testCluster. TestDub creates an array holding a user-specified quantity
// of dubPrime objects, initialized of varying size. These objects are queried to make sure then work, before being
// compared to see if any have matching values and compared to find the minimum. A sum dubPrime is made,
// and all the array objects are added to it. The maximum is found, and decremented until it deactivates. 
// (Kind of barbaric really) Finally, the result of 100 being added to each object is printed.
// TestCluster does many similar thing to an array of clusterP objects. A small dubPrime is added to each clusterP
// and the minimums are found. Lengths are compared to see if any match. One big clusterP is created holding all
// the objects' internal values. A large clusterP is added to each object, then a large dubPrime. Finally, the original
// maximum values are printed again to show the changes were temporary.

#include "dubPrime.h"
#include "clusterP.h"
#include <iostream>

using namespace std;

// Global addition operators
dubPrime operator+(int n, dubPrime& dub);

dubPrime operator-(int n, dubPrime& dub);

clusterP operator+(const dubPrime& dub, clusterP clust);

void testDub(int len, int val);

void query(dubPrime* arr, int len, int val);

int dubMin(dubPrime* arr, int len);

int dubMax(dubPrime* arr, int len);

void equalVal(dubPrime* arr, int len);

void sum(dubPrime* arr, int len, int val);

void kill(dubPrime& dub);

void sumInt(dubPrime* arr, int len, int val);

void testCluster(int len, int val);

void minimum(clusterP* arr, int len, int val);

void maximum(clusterP* arr, int len, int val);

void inversions(clusterP* arr, int len, int val);

void addDub(clusterP* arr, int len, int seed);

void equalLen(clusterP* arr, int len);

void sumClust(clusterP* arr, int len, int val);

void largeSum(clusterP* arr, int len, int val);

void largeDub(clusterP* arr, int len, int val);

int main() {
	const int ARR_LEN = 10;
	const int QUERY_VAL = 1;
	
	testDub(ARR_LEN, QUERY_VAL);
	
	cout << endl;
	
	testCluster(ARR_LEN, QUERY_VAL);
}

dubPrime operator+(int n, dubPrime& dub) {
	return dub + n;
}

dubPrime operator-(int n, dubPrime& dub) {
	return dub - n;
}

clusterP operator+(const dubPrime& dub, clusterP clust) {
	return clust + dub;
}

void testDub(int len, int val) {
	cout << "Testing dubPrimes:\n";
	dubPrime* dubArr = new dubPrime[len];
	
	cout << "Querying array:\n";
	query(dubArr, len, val);
	
	cout << "Index of smallest value in array: " << dubMin(dubArr, len) << endl;
	
	cout << "Testing for equal values:\n";
	equalVal(dubArr, len);
	
	cout << "Adding all values and rounding to nearest prime\n";
	sum(dubArr, len, val);
	
	int max = dubMax(dubArr, len);
	cout << "Index of largest value in array: " << max << endl;
	cout << "Deactivating largest value in array:\n";
	kill(dubArr[max]);
	
	cout << "Sum of each object with 100:\n";
	sumInt(dubArr, len, 100);
	
	delete [] dubArr;
}

void query(dubPrime* arr, int len, int val) {
	for(int i=0; i<len; i++) {
		cout << i << " Query: " << arr[i].query(val) << endl;
	}
}

int dubMin(dubPrime* arr, int len) {
	int min = 0;
	for(int i=1; i<len; i++) 
		min = arr[i] < arr[min] ? i : min;
	
	return min;
}

int dubMax(dubPrime* arr, int len) {
	int max = 0;
	for(int i=1; i<len; i++) 
		max = arr[i] > arr[max] ? i : max;
	
	return max;
}

void equalVal(dubPrime* arr, int len) {
	bool none = true;
	for(int i=0; i<len-1; i++) {
		if (arr[i] == arr[i+1]) {
			cout << "Value of " << i << " and " << i+1 << " are equal\n";
			none = false;
		}
	}
	if (none) { cout << "No equal values\n"; }
}

void sum(dubPrime* arr, int len, int val) {
	dubPrime* sum = new dubPrime(arr[0]);
	for(int i=1; i<len; i++)
		*sum += arr[i];
	cout << "Sum query: " << sum->query(val) << endl;
	delete sum;
}

void kill(dubPrime& dub) {
	while(dub.getActive())
		dub--;
	cout << "Querying dead object: " << dub.query(1) << endl;
}

void sumInt(dubPrime* arr, int len, int val) {
	for(int i=0; i<len; i++) {
		cout << i << " + " << val << " Query: " << (100 + arr[i]).query(val) << endl;
	}
}

void testCluster(int len, int val) {
	cout << "Testing clusterPs:\n";
	clusterP* clustArr = new clusterP[len];
	
	cout << "Array minimums:\n";
	minimum(clustArr, len, val);
	
	cout << "Array maximums:\n";
	maximum(clustArr, len, val);
	
	cout << "Adding small dubPrime to each clusterP\n";
	addDub(clustArr, len, 1);
	minimum(clustArr, len, val);
	
	cout << "Comparing lengths of each clusterP:\n";
	equalLen(clustArr, len);
	
	cout << "Creating one clusterP with all internal objects:\n";
	sumClust(clustArr, len, val);
	
	cout << "Temporarily adding large clusterP to each object:\n";
	largeSum(clustArr, len, val);
	
	cout << "Doing the same thing with a large dubPrime:\n";
	largeDub(clustArr, len, val);
	
	cout << "Unaltered original values:\n";
	maximum(clustArr, len, val);
	
	delete [] clustArr;
}

void minimum(clusterP* arr, int len, int val) {
	for(int i=0; i<len; i++)
		cout << i << " Minimum: " << arr[i].minimum(val) << endl;
}

void maximum(clusterP* arr, int len, int val) {
	for(int i=0; i<len; i++)
		cout << i << " Maximum: " << arr[i].maximum(val) << endl;
}

void inversions(clusterP* arr, int len, int val) {
	for(int i=0; i<len; i++)
		cout << i << " Inversions: " << arr[i].inversions(val) << endl;
}

void addDub(clusterP* arr, int len, int seed) {
	dubPrime dub(seed);
	for(int i=0; i<len; i++)
		arr[i] += dub;
}

void equalLen(clusterP* arr, int len) {
	bool none = true;
	for(int i=0; i<len-1; i++) {
		if (arr[i] == arr[i+1]) {
			cout << "Length of " << i << " and " << i+1 << " are equal\n";
			none = false;
		}
	}
	if (none) { cout << "No equal lengths\n"; }
}

void sumClust(clusterP* arr, int len, int val) {
	clusterP* sum = new clusterP(arr[0]);
	for(int i=1; i<len; i++) {
		*sum += arr[i];
	}
	cout << "Sum maximum: " << sum->maximum(val) << endl;
	delete sum;
}

void largeSum(clusterP* arr, int len, int val) {
	clusterP* large = new clusterP(500);
	for(int i=0; i<len; i++) {
		cout << i << " maximum: " << (*large + arr[i]).maximum(val) << endl;
	}
	delete large;
}

void largeDub(clusterP* arr, int len, int val) {
	dubPrime* large = new dubPrime(500);
	for(int i=0; i<len; i++) {
		cout << i << " maximum: " << (*large + arr[i]).maximum(val) << endl;
	}
	delete large;
}