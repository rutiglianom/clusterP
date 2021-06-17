// Matthew Rutigliano
// 22 April 2021
// Revision History: Data members, constructor, query, isPrime, isEven written 4/3/21
// reset and revive written 4/5/21
// ported to c++, added mode getter, added copy constructor 4/10/21
// Increment and decrement operators added 5/13/21
// nextPrime and prevPrime added 5/15/21
// Addition, subtraction, comparison operators added 5/15/21

// Class Invariant:
// dubPrime object encapsulates prime number greater than 100
// This internal value is influenced by optional seed parameter inputted by user
// Querying object with value p will return nearest prime number greater than p away from internal value when in up mode,
//     less than p away from internal value when in down mode
// Objects begin in up mode, then transition to down mode after an internally determined number of queries (user tracked)
// Amount of queries possible before transitioning will be unique to each object
// Once in down mode, object remains in down mode until it is reset or revived
// Resetting object returns it to up mode, allows the same amount of queries
// Reviving object returns it to up mode, allows an updated amount of queries
// Constructor determines internal value, number of queries possible before transitioning
// Any query returning a number less than 10 will permenantly deactivate the object (tracked by user)
// Once deactivated, query will return -1, reset and revive will do nothing, Active returns false
// Initializing multiple objects with no seed will produce objects with increasing internal values
// Incrementing object updates internal value to next prime number
// Decrementing object updates internal value to previous prime number
// Decrementing object to be less than 100 will deactivate object
// Increment operators support pre and post usage
// Adding or subtracting dubPrime to another dubPrime or integer yields dubPrime with internal value of next prime number greater
//     than sum or difference of two internal values (or internal value and integer value)
// Global commutative addition and subtraction function in P4.cpp (compiler won't link when it's in dubPrime.cpp)
// Shortcut addition assignment is supported for both additions, subtractions
// Adding or subtracting deactivated dubPrime will yield deactivated dubPrime
// Adding or subtracting value great enough to make internal value less than 100 will deactivate object
// Comparison operators compare internal values between dubPrime objects, integers

// Interface Invariant:
// Optional seed value must be greater than 0
// Client must track Active state

#ifndef DUBPRIME_H
#define DUBPRIME_H

class dubPrime {
	private:
	int x;
	int queryCount;
	int queryLimit;
	bool mode;
	bool isActive;
	static int dubPrimeCount;
	const int xMin = 101;
	const int queryLimitMultiplier = 2;
	void updateActive(int n);
	
	bool isEven(int n);
	bool isPrime(int n);
	int nextPrime(int n);
	int prevPrime(int n);
	
	public:
	// Postcondition: Object may become inactive
	dubPrime();
	
	// Postcondition: Object may become inactive
	dubPrime(int seed);
	
	// Postcondition: Object may become inactive
	dubPrime(const dubPrime& dub);
	
	// Postcondition: Object may become inactive
	dubPrime& operator=(const dubPrime& dub);
	

	// Post Condition: Object may transition from up mode to down mode
	// Object may become inactive
	int query(int p);

	// Post Condition: Object will stay in or transition to up mode
	void reset();

	// Post Condition: Object will stay in or transition to up mode
	void revive();

	bool getActive();
	
	bool getMode();
	
	dubPrime operator++();
	
	dubPrime operator++(int dum);
	
	// Postcondition: Object may become inactive
	dubPrime operator--();
	
	// Postcondition: Object may become inactive
	dubPrime operator--(int dum);
	
	dubPrime operator+(const dubPrime& dub);
	
	dubPrime operator+(int n);
	
	// Postcondition: Object may become inactive
	dubPrime operator-(const dubPrime& dub);
	
	// Postcondition: Object may become inactive
	dubPrime operator-(int n);
	
	// Postcondition: Object may become inactive
	dubPrime& operator+=(const dubPrime& dub);
	
	// Postcondition: Object may become inactive
	dubPrime& operator+=(int n);
	
	// Postcondition: Object may become inactive
	dubPrime& operator-=(const dubPrime& dub);
	
	// Postcondition: Object may become inactive
	dubPrime& operator-=(int n);
	
	bool operator==(const dubPrime& dub);
	
	bool operator==(int n);
	
	bool operator!=(const dubPrime& dub);
	
	bool operator!=(int n);
	
	bool operator>(const dubPrime& dub);
	
	bool operator>(int n);
	
	bool operator<(const dubPrime& dub);
	
	bool operator<(int n);
	
	bool operator>=(const dubPrime& dub);
	
	bool operator>=(int n);
	
	bool operator<=(const dubPrime& dub);
	
	bool operator<=(int n);
};

#endif

// Implementation Invariant: 
// Internal value (x) determined by multiplying seed by minimum acceptable value (11)
// Amount of queries before transitioning modes (queryLimit) determined by multiplying amount of query objects with arbitrary scaling value
// Resetting returns counter of queries performed (queryCount) to 0
// Reviving recalculates queryLimit as the old limit multiplied by the amount of objects, summed with the current queryCount
// Active parameter isActive controls query, reset, revive, addition, subtraction, incrementing
// updateActive(int) function updates active parameter based off of passed value
// updateActive runs at initialization, and with every destructive addition or subtraction self assignment