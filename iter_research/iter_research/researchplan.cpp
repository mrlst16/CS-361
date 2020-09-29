#include "researchplan.h"

#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include<vector>

using namespace std;


ResearchPlan::ResearchPlan()
: researchTopic()
{

}

ResearchPlan::~ResearchPlan(){
}


ResearchPlan::ResearchPlan (const Topic& topic)
:
     researchTopic(topic)
{
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
    for(auto it = requirements.begin(); it != requirements.end(); ++it)
    {
        Topic t = *it;
        if(t == topic)
            return;
    }
	requirements.push_back(topic);
}

void ResearchPlan::removeRequirement(const Topic& topic)
{
    for(auto it = begin(); it != end(); ++it)
    {
        Topic t = *it;
        if(t == topic)
            requirements.erase(it);
    }
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
    return one.getNumberOfRequirements() < two.getNumberOfRequirements()
        || one.getTopic() < two.getTopic();
}

std::ostream& operator<< (std::ostream& out, const ResearchPlan& plan){

    out << "Plan topic: " << plan.getTopic().name << endl
    << "There is(are) " << plan.getNumberOfRequirements() << " requirement(s): "
    << endl;
    out << "(";
    for(auto it = plan.begin(); it != plan.end(); ++it)
        out << (*it).name << endl;

    out << ")";
    return out;
}
