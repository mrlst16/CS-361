#include "researchplan.h"

#include <cassert>
#include <iostream>
#include <string>
#include <utility>

using namespace std;


ResearchPlan::ResearchPlan()
: researchTopic()
{

}

ResearchPlan::~ResearchPlan(){
}


ResearchPlan::ResearchPlan (const Topic& topic)
: researchTopic(topic)
{
}

template<typename Iterator>
ResearchPlan::ResearchPlan (const Topic topic, Iterator begin, Iterator end)
:
    researchTopic(topic)
{
    for(auto it = begin; it != end; ++it)
        requirements.push_back(*it);
}


ResearchPlan::ResearchPlan (const Topic topic, std::array<Topic, 3>::iterator start, std::array<Topic, 3>::iterator finish)
:
    researchTopic(topic)
{
    for(std::array<Topic, 3>::iterator it = start; it != finish; ++it)
        requirements.push_back(*it);
}

ResearchPlan::ResearchPlan(const Topic& topic, initializer_list<Topic> topicPrerequisites)
:researchTopic(topic)
{
    for(auto it = topicPrerequisites.begin(); it != topicPrerequisites.end(); ++it)
        requirements.push_back(*it);
}

ResearchPlan::ResearchPlan(const ResearchPlan& other)
:
    researchTopic(other.researchTopic)
{
    requirements = other.requirements;
}


void ResearchPlan::addRequirement(const Topic& topic)
{
	requirements.push_back(topic);
}

void ResearchPlan::removeRequirement(const Topic& topic)
{

}

Topic ResearchPlan::getRequirement(int i) const
{
	return requirements[i];
}

const ResearchPlan& ResearchPlan::operator=(const ResearchPlan& other){
    requirements = other.requirements;
    researchTopic = other.researchTopic;

    return *this;
}

bool operator==(const ResearchPlan one, const ResearchPlan two)
{
	bool result = one.getTopic().name == two.getTopic().name
	&& one.getNumberOfRequirements() == two.getNumberOfRequirements();
	if(!result) return result;

	for(int i = 0; i < one.getNumberOfRequirements(); i++){
        if(!(one.getRequirement(i) == two.getRequirement(i)))
            return false;
	}
	return true;
}

bool operator<(const ResearchPlan one, const ResearchPlan two)
{
    bool topicOneLess = one.getTopic() < two.getTopic();
    bool oneNRLess = one.getNumberOfRequirements() <= two.getNumberOfRequirements();
    bool result = topicOneLess && oneNRLess;

    return result;
}

std::ostream& operator<< (std::ostream& out, const ResearchPlan& plan){

    out << "Plan topic: " << plan.getTopic().name << endl;
    out << "There is(are) " << plan.getNumberOfRequirements() << " requirement(s)" << endl;
    for(auto it = plan.begin(); it != plan.end(); ++it)
        out << (*it).name << endl;
    return out;
}
