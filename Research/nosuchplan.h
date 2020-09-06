#ifndef NOSUCHPLAN_H_
#define NOSUCHPLAN_H_

#include <string>
#include <exception>

/**
 * Error signaled when trying to retrieve a plan for an unknown topic
 * from an Encyclopedia.
 */
struct NoSuchPlan : public exception {

	std::string topicName;

   NoSuchPlan (std::string topic): topicName(topic) {}

   const char * what () const throw () {
	  static const std::string msg = "There is no plan for: ";
      return (msg + topicName).c_str();
   }
};



#endif /* NOSUCHPLAN_H_ */
