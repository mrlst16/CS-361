#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include "encyclopedia.h"
#include "nosuchplan.h"


using namespace std;


Encyclopedia::Encyclopedia()
{

}


// Remove leading spaces from a string
string Encyclopedia::trim (string str)
{
	string::size_type k = 0;
	while (str[k] == ' ')
		++k;
	return str.substr(k);
}

// Split a string into fields separated by
// a delimiter character.
vector<string> Encyclopedia::split (const string& str, char delimiter)
{
	vector<string> results;
	string::size_type start = 0;
	while (start != string::npos)
	{
		string::size_type splitPos = str.find(delimiter, start);
		if (splitPos == string::npos)
		{
			results.push_back(str.substr(start));
			start = splitPos;
		}
		else
		{
			results.push_back(str.substr(start, splitPos-start));
			start = splitPos + 1;
		}
	}
	return results;
}

void Encyclopedia::read (istream& input)
{
  string line;
  getline (input, line);
  while (input && (line != "---")) {
	  vector<string> parts = split(line, ':');
	  if (parts.size() != 2)
		  continue;
	  string nameToResearch = trim(parts[0]);
	  parts = split(parts[1], ',');
	  string costStr = parts[parts.size()-1];
	  int cost = stoi(costStr);
	  for (unsigned i = 0; i < parts.size()-1; ++i)
	  {
		  string requiredTopicName = trim(parts[i]);
		  ResearchPlan& priorPlan = findOrAdd(requiredTopicName);
		  Topic priorTopic = priorPlan.getTopic();
		  ResearchPlan& plan = findOrAdd(nameToResearch);
		  plan.addRequirement(priorTopic);
	  }
	  ResearchPlan& plan = findOrAdd(nameToResearch);
	  plan.getTopic().researchCost = cost;
	  getline (input, line);
  }
}


void Encyclopedia::addPlanRequirement (
        const Topic& topic1,
        const Topic& requiredTopic)
{
	findOrAdd(requiredTopic.name);
	ResearchPlan& plan1 = findOrAdd(topic1.name);
	plan1.addRequirement(requiredTopic);
}


void Encyclopedia::removeTopic (const Topic& topic)
{
	for (ResearchPlan& plan: plans)
	{
		plan.removeRequirement (topic);
	}
	auto pos = find_if(plans.begin(), plans.end(),
			[&] (ResearchPlan& plan){return plan.getTopic() == topic;});
	if (pos != plans.end()) {
		plans.erase(pos);
	}
}


ResearchPlan& Encyclopedia::getPlan (const Topic& topic)
{
	for (ResearchPlan& plan: plans)
	{
		if (plan.getTopic() == topic)
			return plan;
	}
	throw NoSuchPlan(topic.name);
}

const ResearchPlan& Encyclopedia::getPlan (const Topic& topic) const
{
	for (const ResearchPlan& plan: plans)
	{
		if (plan.getTopic() == topic)
			return plan;
	}
	throw NoSuchPlan(topic.name);
}


bool Encyclopedia::containsTopic (const Topic& topic) const {
	for (const ResearchPlan& plan: plans)
	{
		if (plan.getTopic() == topic)
			return true;
	}
	return false;
}

ResearchPlan& Encyclopedia::findOrAdd (const std::string& topicName)
{
	for (ResearchPlan& plan: plans)
	{
		if (plan.getTopic().name == topicName)
			return plan;
	}
	ResearchPlan newPlan (Topic(topicName, 0));
	plans.push_back(newPlan);
	return plans.back();
}



bool Encyclopedia::operator== (const Encyclopedia& right) const
{
	auto rightItr = right.plans.begin();
	for (const ResearchPlan& plan1: plans)
	{
		if (rightItr == right.plans.end())
			return false;
		if (!(plan1 == *rightItr))
			return false;
		++rightItr;
	}
	return (rightItr == right.plans.end());
}


std::ostream& operator<< (std::ostream& out, const Encyclopedia& encyc)
{
	for (const Topic& t: encyc)
	{
		out << encyc.getPlan(t) << endl;
	}
	return out;
}


// Move position forward 1 place
Encyclopedia::iterator& Encyclopedia::iterator::operator++()
{
	++pos;
	return *this;
}

Encyclopedia::iterator Encyclopedia::iterator::operator++(int)
{
	iterator saved = *this;
	pos++;
	return saved;
}

Encyclopedia::const_iterator& Encyclopedia::const_iterator::operator++()
{
	++pos;
	return *this;
}

Encyclopedia::const_iterator Encyclopedia::const_iterator::operator++(int)
{
	const_iterator saved = *this;
	pos++;
	return saved;
}
