#include "topic.h"

#include <iostream>
#include <string>

using namespace std;

Topic::Topic ()
: name(""), researchCost(0)
{
}

Topic::Topic (string theName, int cost)
  : name(theName), researchCost(cost)
{
}


bool Topic::operator== (const Topic& right) const
{
	return name == right.name;
}

bool Topic::operator< (const Topic& right) const
{
	return name < right.name;
}


ostream& operator<< (ostream& out, const Topic& topic)
{
  out << topic.name << ": " <<  topic.researchCost;
  return out;
}

