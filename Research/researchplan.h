#ifndef RESEARCHPLAN_H
#define RESEARCHPLAN_H

#include <iostream>
#include <string>

#include "topic.h"

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
    int numberOfRequirements; ///< How many requirements for this topic?
    int maxRequirements;      ///< How many requirements will fit into the array?
    Topic * requirements;      ///< Pointer to an array of requirements.
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
	int getNumberOfRequirements() const;

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

	/**
	 * Get the name of the i_th requirement.
	 *
	 * @precondition 0 <= i && i < getNumberofRequirements()
	 * @param i index of the requirement to retrieve
	 * @return a topic whose name indicates a required prior research topic.
	 *         The cost info in the returned topic is not necessarily accurate.
	 */
	Topic getRequirement(int i) const;

	const ResearchPlan& operator=(const ResearchPlan& other);
private:
	friend std::ostream& operator<< (std::ostream& out, const ResearchPlan& plan);
};

std::ostream& operator<< (std::ostream& out, const ResearchPlan& plan);

bool operator==(const ResearchPlan one, const ResearchPlan two);

bool operator< (const ResearchPlan one, const ResearchPlan two);



#endif
