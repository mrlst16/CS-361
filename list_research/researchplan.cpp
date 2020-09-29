#include "researchplan.h"

#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <list>

using namespace std;

template <typename T>
void addSortUnique(list<T>& lst, T item) {

	if (lst.size() == 0) {
		lst.insert(lst.begin(), item);
		return;
	}

	auto start = lst.begin();
	T* previousP = &(*start);

	if(item < (*previousP)){
        //cout << "Found a pre req" << endl;
        lst.push_front(item);
        return;
    }

	for (auto it = start; it != lst.end(); it++) {

		T previous = *previousP;
		T current = *it;


		if(
            item == previous
			|| item == current
                //Do nothing, because we don't want duplicates
			)
			return;
		if (
			(previous < item && item < current)
			) {
			lst.insert(it, item);
			return;
		}

		previousP = &current;
	}

	lst.insert(lst.end(), item);

}

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
    addSortUnique(requirements, topic);
}

void ResearchPlan::removeRequirement(const Topic& topic)
{
    for(auto it = begin(); it != end(); ++it)
    {
        Topic t = *it;
        if(t == topic){
            requirements.erase(it);
            return;
        }
    }
}

Topic ResearchPlan::getRequirement(int i) const
{
    auto it = this->requirements.begin();
    int counter = 0;
    for(auto it = begin(); it != end(); ++it)
    {
        if(counter == i)
            return *it;

        i++;
    }
//    if(i > 0){
//        std::advance(it, i-1);
//    }
//    int numReq = this->getNumberOfRequirements();
//    if(i >= numReq - 1){
//        cout << "Advancing " << (numReq - 1) << endl;
//        std::advance(it, numReq-1);
//    }
    return *it;
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

    if(one.getNumberOfRequirements() != two.getNumberOfRequirements())
        return false;

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
