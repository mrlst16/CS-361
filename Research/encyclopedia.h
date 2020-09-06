#ifndef ENCYCLOPEDIA_H
#define ENCYCLOPEDIA_H

#include <iostream>
#include <vector>
#include "researchplan.h"

/**
 * The master list of all research topics, organized
 * by their research plans.
 */
class Encyclopedia {
public:
	class iterator {
	public:
	  typedef std::random_access_iterator_tag iterator_category;
	  typedef Topic                     value_type;
	  typedef ptrdiff_t                  difference_type;
	  typedef value_type*                pointer;
	  typedef value_type&                reference;

	  iterator() {}

	  // Get the data element at this position
	  reference operator*() const {return pos->getTopic();}
	  pointer operator->() const {return &(pos->getTopic());}

	  // Move position forward 1 place
	  iterator& operator++();
	  iterator operator++(int);

	  // Random access
	  iterator operator+ (int offset) const {return iterator(pos+offset);}
	  int operator- (const iterator& right) const {return pos-right.pos;}

	  // Comparison operators
	  bool operator== (const iterator& right) const {return pos == right.pos;}
	  bool operator!= (const iterator& right) const {return pos != right.pos;}
	private:
	  std::vector<ResearchPlan>::iterator pos;

	  iterator (std::vector<ResearchPlan>::iterator p)
	  : pos(p) {}

	  friend class Encyclopedia;
	};

	class const_iterator {
	public:
	  typedef std::random_access_iterator_tag iterator_category;
	  typedef Topic                     value_type;
	  typedef ptrdiff_t                  difference_type;
	  typedef const value_type*                pointer;
	  typedef const value_type&                reference;

	  const_iterator() {}

	  // Get the data element at this position
	  reference operator*() const {return pos->getTopic();}
	  pointer operator->() const {return &(pos->getTopic());}

	  // Move position forward 1 place
	  const_iterator& operator++();
	  const_iterator operator++(int);

	  // Random access
	  const_iterator operator+ (int offset) const {return const_iterator(pos+offset);}
	  int operator- (const const_iterator& right) const {return pos-right.pos;}

	  // Comparison operators
	  bool operator== (const const_iterator& right) const {return pos == right.pos;}
	  bool operator!= (const const_iterator& right) const {return pos != right.pos;}
	private:
	  std::vector<ResearchPlan>::const_iterator pos;

	  const_iterator (std::vector<ResearchPlan>::const_iterator p)
	  : pos(p) {}

	  friend class Encyclopedia;
	};


    /**
     *  Create a new encyclopedia.
     */
	Encyclopedia();


	/**
	 * Provide access to the topics in the encyclopedia.
	 */
	iterator begin() {return iterator(plans.begin());}
	iterator end() {return iterator(plans.end());}

	const_iterator begin() const {return const_iterator(plans.begin());}
	const_iterator end() const {return const_iterator(plans.end());}


	/**
	 * Adds a plan requirement to the encyclopedia. This is a pair of topics,
	 * possibly never seen before, such that one topic must have been researched
	 * before research can begin on the other.
	 *
	 * @param topic1  a topic, possibly never seen before
	 * @param requiredPriorTopic  another topic that must be researched
	 *                    before topic1.
	 */
	void addPlanRequirement (
			const Topic& topic1,
			const Topic& requiredPriorTopic);

	/**
	 * Remove a topic from the encyclopedia, including any
	 * plan requirements in which it participates.
	 */
	void removeTopic (const Topic& topic);

	/**
	 * See if a topic is already in the catalog.
	 *
	 * @param topic a topic whose name is to be searched for
	 * @return true iff topic is in the catalog
	 */
	bool containsTopic (const Topic& topic) const;

	/**
	 * Fetch a plan by topic name.
	 * @param topic a topic whose name is to be searched for
	 * @return the plan for the topic that same name.
	 * @throws NoSuchPlan if a plan for that topic does not exist.
	 */
	ResearchPlan& getPlan (const Topic& topic);
	const ResearchPlan& getPlan (const Topic& topic) const;


	/**
	 * Read an encyclopedia from an input stream.
	 *
	 * Input is repeated lines of
	 *
	 *   topic: prior topic 1, prior topic 2, ... , cost
	 *
	 * Topic names may be any mixture of alphanumeric characters and
	 * blanks, but must have at least one non-blank character, must not begin
	 * with a blank, and must not include the characters ',' or ':'.
	 *
	 * Leading blanks may appear before a topic name in the input, but are
	 * ignored.
	 *
	 * The end of input is signaled by the end of the input stream or by a
	 * line consisting solely of the string "---". (Three hyphens.)
	 *
	 * @param input the input stream
	 */
	void read (istream& input);


	bool operator== (const Encyclopedia& right) const;

private:

	/**
	 * All of the plans in this encyclopedia.
	 */
	std::vector<ResearchPlan> plans;

	/**
	 * Check to see if a research plan already exists for this
	 * topic. If not, create one.  Return the created plan or
	 * existing one that was found.
	 */
	ResearchPlan& findOrAdd (const std::string& topicName);

    /**
     * Remove leading spaces from a string.
     */
	static std::string trim (std::string str);

	/**
	 * Split a string into fields separated by a delimiter character.
	 *
	 * @param str: the string to be split
	 * @param delimiter: the character separating the parts of the string
	 * @returns a vector containing one or more parts of the string, with
	 *    the delimiter character removed.
	 */
	static std::vector<std::string> split (
			const std::string& str,
			char delimiter);


};

std::ostream& operator<< (std::ostream& out, const Encyclopedia& cat);

#endif
