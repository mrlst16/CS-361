#include "researchplan.h"

#include <cassert>
#include <iostream>
#include <string>
#include <utility>

using namespace std;


ResearchPlan::ResearchPlan()
: researchTopic(), numberOfRequirements(0), maxRequirements(0), requirements(nullptr)
{

}

ResearchPlan::~ResearchPlan(){
    delete [] requirements;
}


ResearchPlan::ResearchPlan (const Topic& topic)
: researchTopic(topic), numberOfRequirements(0), maxRequirements(10),
  requirements(new Topic[maxRequirements])
{
    requirements[0] = topic;
}

ResearchPlan::ResearchPlan(const ResearchPlan& other)
:
    researchTopic(other.researchTopic),
    numberOfRequirements(other.numberOfRequirements),
    maxRequirements(other.maxRequirements),
    requirements(new Topic[other.maxRequirements])
{
    cout << "Copy constructor " << numberOfRequirements << endl;
    for(int i = 0; i < other.numberOfRequirements; i++)
        addRequirement(other.requirements[i]);
}


int ResearchPlan::getNumberOfRequirements() const
{
	return numberOfRequirements;
}


void ResearchPlan::addRequirement(const Topic& topic)
{
	for (int i = 0; i < numberOfRequirements; ++i)
		if (requirements[i] == topic)
			return;
	assert (numberOfRequirements < maxRequirements);
	requirements[numberOfRequirements] = topic;
	++numberOfRequirements;
}


void ResearchPlan::removeRequirement(const Topic& topic)
{
	for (int i = 0; i < numberOfRequirements; ++i)
		if (requirements[i] == topic)
		{
			for (int j = i+1; j < numberOfRequirements; ++j)
				requirements[j-1] = requirements[j];
			--numberOfRequirements;
			break;
		}
}


Topic ResearchPlan::getRequirement(int i) const
{
	assert (i >= 0 && i < numberOfRequirements);
	return requirements[i];
}

const ResearchPlan& ResearchPlan::operator=(const ResearchPlan& other){

    maxRequirements = other.maxRequirements;
    numberOfRequirements = other.numberOfRequirements;

    delete [] requirements;
    requirements = new Topic[maxRequirements];
    for(int i= 0; i < numberOfRequirements; i++)
        requirements[i] = other.requirements[i];

    researchTopic = other.researchTopic;

    return *this;
}


bool operator==(const ResearchPlan one, const ResearchPlan two)
{
	return one.getTopic().name == two.getTopic().name
		&& one.getNumberOfRequirements() == two.getNumberOfRequirements();
}

bool operator<(const ResearchPlan one, const ResearchPlan two)
{
	return one.getNumberOfRequirements() < two.getNumberOfRequirements()
		&& one.getNumberOfRequirements() == two.getNumberOfRequirements();
}
