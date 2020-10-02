#ifndef RESEARCHPLAN_H
#define RESEARCHPLAN_H

#include <iostream>
#include <string>
#include<vector>
#include<array>
#include<list>
#include "topic.h"
#include <algorithm>

using namespace std;

/**
 * A ResearchPlan describes the prior requirements for researching
 * a research topic.  It consists of a topic to be researched and a list of
 * research requirements, prior topics that must have been successfully
 * completed before research on this one can begin.
 */
class ResearchPlan {
    //** You may not change the declarations in this private: area.
    Topic researchTopic;           ///< The topic to be researched

public:

	/**
	 * Create a new plan for a default topic (Topic()) and having no
	 * known prerequisites;
	 */
	ResearchPlan();

	/**
	 * Destructor, which needs implemented because we have to delete our pointers
	 */
	~ResearchPlan();

	/**
	 * Create a new plan for researching a given topic and having no
	 * known prerequisites;
	 *
	 * @param topic the topic to be researched
	 */
	ResearchPlan (const Topic& topic);

	/**
	 * Create a new plan for researching a given topic and having no
	 * known prerequisites;
	 *
	 * @param topic the topic to be researched
	 * @param topicPrerequisites the pre-required topics to be researched before the main topic
	 */
    ResearchPlan (const Topic& topic, initializer_list<Topic> topicPrerequisites);

    template<typename Iterator>
    ResearchPlan(const Topic& topic, Iterator begin, Iterator end)
    :
        researchTopic(topic)
    {
        for(auto it = begin; it != end; ++it){
            requirements.push_back(*it);
        }
    }

	/**
	 * Copy constructor
	 *
	 * @param other, the other object being copied
	 */
	ResearchPlan (const ResearchPlan& other);

	/**
	 * @return the topic to be researched
	 */
	const Topic& getTopic() const {return researchTopic;}
	Topic& getTopic() {return researchTopic;}

	/**
	 * @return the number of known requirements for this plan.
	 */
	int getNumberOfRequirements() const{return requirements.size();};

	/**
	 * Adds topic to the list of requirements for this plan.
	 * If this topic is already in the list, this has no effect.
	 *
	 * @param topic a required prior topic
	 */
	void addRequirement(const Topic& topic);

	/**
	 * Removes a topic from the list of requirements for this plan.
	 * If this topic is not already required, this has no effect.
	 *
	 * @param topic a prior required topic
	 */
	void removeRequirement(const Topic& topic);

	const ResearchPlan& operator=(const ResearchPlan& other);

	std::list<Topic>::iterator begin(){return requirements.begin();};
	std::list<Topic>::iterator end(){return requirements.end();};
	std::list<Topic>::const_iterator begin() const {return requirements.begin();};
	std::list<Topic>::const_iterator end() const {return requirements.end();};
private:
	friend std::ostream& operator<< (std::ostream& out, const ResearchPlan& plan);
	std::list<Topic> requirements;
};

std::ostream& operator<< (std::ostream& out, const ResearchPlan& plan);

bool operator==(const ResearchPlan one, const ResearchPlan two);

bool operator< (const ResearchPlan one, const ResearchPlan two);



#endif
