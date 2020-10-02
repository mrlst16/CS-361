#include "researchplan.h"

#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <list>
#include <utility>

using namespace std;

template <typename T>
void addSortUnique(list<T>& lst, T item) {
	if (lst.size() == 0) {
		lst.push_front(item);
		return;
	}

	auto start = lst.begin();
	T* startP = &(*start);

	if(item < (*startP)){
        lst.push_front(item);
        return;
    }

    int count = 0;
	for (auto it = start; it != lst.end(); it++) {

		T current = *it;
		auto prevIterator = it;
		--prevIterator;
		T previous = count == 0 ? *startP : *prevIterator;

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

		count++;
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
        this->addRequirement(*it);
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

    auto it1 = one.begin();
	auto it2 = two.begin();
	for (; it1 != one.end(); it1++, it2++) {
		Topic one = (*it1);
		Topic two = (*it2);
		bool match = (one == two);
		//cout << "one: " << one << " two: " << two << " match: " << match << endl;
        if(!match) return false;
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
