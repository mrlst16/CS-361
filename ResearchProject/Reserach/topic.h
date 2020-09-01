#ifndef COURSENAME_H
#define COURSENAME_H

#include <iostream>
#include <string>
#include "memoryChecked.h"

using namespace std;

/*
 * A topic that can be researched.
 */
struct Topic {
	std::string name;
	int researchCost;


	Topic();

	Topic (std::string theName, int theCost);

	bool operator== (const Topic& right) const;
	bool operator< (const Topic& right) const;
private:
	MemoryChecked _mem;
};

std::ostream& operator<< (std::ostream& out, const Topic& c);



#endif
