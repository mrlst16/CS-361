#include <algorithm>
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <string>
#include <vector>

#include "encyclopedia.h"
#include "memoryChecked.h"
#include "researchplan.h"

using namespace std;

void readPlayerInfo (istream& input, vector<string>& knownTopics)
{
	string line;
	getline (input, line);
	while (input && (line != "---"))
	{
		knownTopics.push_back(line);
		getline (input, line);
	}
}


bool containsTopicName (const vector<string>& alreadyKnown,
		                const string& topicName)
{
	for (const string& known: alreadyKnown)
	{
		if (topicName == known)
		{
			return true;
		}
	}
	return false;
}


bool couldBeResearched (const ResearchPlan& plan,
		                const vector<string>& alreadyKnown)
{
	for (Topic required: plan)
	{
		if (!containsTopicName(alreadyKnown, required.name))
		{
			return false ; // If any required prior topic is unknown.
		}
	}
	return true; // If every required prior topic is already known.
}



/**
 * Print a list of the research topics that could be researched
 * by a game player, given the encyclopedia of possible research plans
 * and the list of topics already known/researched.
 */
void permittedResearch(const Encyclopedia& encyc,
		               const vector<string>& alreadyKnown)
{
	vector<Topic> researchable;
	Topic lowestCostTopic ("nonsense", numeric_limits<int>::max());
	for (const Topic& topic: encyc)
	{
		ResearchPlan plan = encyc.getPlan(topic);
		if ((!containsTopicName(alreadyKnown, plan.getTopic().name))
				&& couldBeResearched(plan, alreadyKnown))
		{
			researchable.push_back(topic);
			if (topic.researchCost < lowestCostTopic.researchCost)
			{
				lowestCostTopic = topic;
			}
		}
	}
	cout << "There are " << researchable.size()
							<< " topics available for research." << endl;
	sort (researchable.begin(), researchable.end());
	for (const Topic& topic: researchable)
	{
		cout << setw(24) << topic.name << setw(0) << "  " << topic.researchCost << endl;
	}
	cout << "The cheapest to research is " << lowestCostTopic << endl;
}



//int main (int argc, char** argv)
//{
//	{
//		Encyclopedia encyclopedia;
//		vector<string> alreadyResearched;
//		if (argc > 1)
//		{
//			ifstream in (argv[1]);
//			encyclopedia.read (in);
//			readPlayerInfo (in, alreadyResearched);
//		}
//		else
//		{
//			encyclopedia.read (cin);
//			readPlayerInfo (cin, alreadyResearched);
//		}
//		permittedResearch (encyclopedia, alreadyResearched);
//	}
//	return 0;
//}
