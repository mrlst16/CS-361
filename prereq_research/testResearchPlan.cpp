#include "unittest.h"
#include <sstream>
#include "researchplan.h"

using namespace std;


UnitTest(ResearchPlanDefaultConstructor) {
	ResearchPlan plan;
	assertThat (plan.getTopic(), isEqualTo(Topic()));
	assertThat (plan.getNumberOfRequirements(), isEqualTo(0));
	assertThat (plan, isEqualTo(ResearchPlan()));
	assertThat (plan, not(isLessThan(ResearchPlan())));
	assertThat (plan, not(isGreaterThan(ResearchPlan())));
}

UnitTest(ResearchPlanConstructor) {
	Topic alphabet ("Alphabet", 15);
	Topic mining ("Mining", 15);
	Topic commerce ("Commerce", 25);
	ResearchPlan plan (alphabet);

	assertThat (plan.getTopic(), isEqualTo(alphabet));
	assertThat (plan.getNumberOfRequirements(), isEqualTo(0));
	assertThat (plan, isNotEqualTo(ResearchPlan()));
	assertThat (plan, isLessThan(ResearchPlan(mining)));
	assertThat (plan, isLessThan(ResearchPlan(commerce)));

	ostringstream out;
	out << plan;
	assertThat (out.str(), contains("Alphabet"));
}



UnitTest(ResearchPlanAddPrior) {
	Topic alphabet ("Alphabet", 15);
	Topic commerce ("Commerce", 25);
	Topic sailing ("Sailing", 36);
	Topic mapping ("Mapping", 30);
	Topic trading ("Trading", 35);

	ResearchPlan plan0(trading);
	ResearchPlan plan (trading);
	assertThat (plan, isEqualTo(plan0));

	plan.addRequirement(sailing);
	assertThat (plan.getNumberOfRequirements(), isEqualTo(1));
	assertThat (plan, isNotEqualTo(plan0));
	assertThat (plan.getRequirement(0), isEqualTo(sailing));

	plan.addRequirement(mapping);
	assertThat (plan.getNumberOfRequirements(), isEqualTo(2));
	assertThat (plan.getRequirement(0), isEqualTo(sailing));
	assertThat (plan.getRequirement(1), isEqualTo(mapping));

	plan.addRequirement(sailing);
	assertThat (plan.getNumberOfRequirements(), isEqualTo(2));
	assertThat (plan.getRequirement(0), isEqualTo(sailing));
	assertThat (plan.getRequirement(1), isEqualTo(mapping));

	ostringstream out;
	out << plan;
	string outStr = out.str();
	assertThat (outStr, contains("Trading"));
	assertThat (outStr, contains("Mapping"));
	assertThat (outStr, contains("Sailing"));

}

UnitTest(ResearchPlanRemovePrior) {
	Topic alphabet ("Alphabet", 15);
	Topic commerce ("Commerce", 25);
	Topic sailing ("Sailing", 36);
	Topic mapping ("Mapping", 30);
	Topic trading ("Trading", 35);

	ResearchPlan plan0(trading);
	ResearchPlan plan (trading);
	assertThat (plan, isEqualTo(plan0));

	plan.addRequirement(sailing);
	assertThat (plan.getNumberOfRequirements(), isEqualTo(1));
	assertThat (plan, isNotEqualTo(plan0));
	assertThat (plan.getRequirement(0), isEqualTo(sailing));

	plan.addRequirement(mapping);
	assertThat (plan.getNumberOfRequirements(), isEqualTo(2));
	assertThat (plan.getRequirement(0), isEqualTo(sailing));
	assertThat (plan.getRequirement(1), isEqualTo(mapping));

	plan.removeRequirement(sailing);
	assertThat (plan.getNumberOfRequirements(), isEqualTo(1));
	assertThat (plan.getRequirement(0), isEqualTo(mapping));

	ostringstream out;
	out << plan;
	string outStr = out.str();
	assertThat (outStr, contains("Trading"));
	assertThat (outStr, contains("Mapping"));
	assertThat (outStr, not(contains("Sailing")));

}




UnitTest(ResearchPlanCopy) {
	Topic alphabet ("Alphabet", 15);
	Topic commerce ("Commerce", 25);
	Topic sailing ("Sailing", 36);
	Topic mapping ("Mapping", 30);
	Topic trading ("Trading", 35);

	ResearchPlan plan(trading);
	plan.addRequirement(sailing);
	plan.addRequirement(mapping);

	ResearchPlan plan2 (plan);
	assertThat(plan2, isEqualTo(plan));

	plan2.addRequirement(alphabet);
	assertThat(plan2, isNotEqualTo(plan));

	assertThat (plan.getNumberOfRequirements(), isEqualTo(2));
	assertThat (plan2.getNumberOfRequirements(), isEqualTo(3));
	assertThat (plan.getRequirement(0), isEqualTo(sailing));
	assertThat (plan2.getRequirement(0), isEqualTo(sailing));
	assertThat (plan.getRequirement(1), isEqualTo(mapping));
	assertThat (plan2.getRequirement(1), isEqualTo(mapping));
	assertThat (plan2.getRequirement(2), isEqualTo(alphabet));

	plan.removeRequirement(sailing);
	assertThat (plan.getNumberOfRequirements(), isEqualTo(1));
	assertThat (plan2.getNumberOfRequirements(), isEqualTo(3));
	assertThat (plan.getRequirement(0), isEqualTo(mapping));
	assertThat (plan2.getRequirement(0), isEqualTo(sailing));
	assertThat (plan2.getRequirement(1), isEqualTo(mapping));
	assertThat (plan2.getRequirement(2), isEqualTo(alphabet));
}

UnitTest(ResearchPlanAssign) {
	Topic alphabet ("Alphabet", 15);
	Topic commerce ("Commerce", 25);
	Topic sailing ("Sailing", 36);
	Topic mapping ("Mapping", 30);
	Topic trading ("Trading", 35);

	ResearchPlan plan(trading);
	plan.addRequirement(sailing);
	plan.addRequirement(mapping);

	ResearchPlan plan2;
	ResearchPlan c3(plan2 = plan);
	assertThat(plan2, isEqualTo(plan));
	assertThat(c3, isEqualTo(plan));

	plan2.addRequirement(alphabet);
	assertThat(plan2, isNotEqualTo(plan));

	assertThat (plan.getNumberOfRequirements(), isEqualTo(2));
	assertThat (plan2.getNumberOfRequirements(), isEqualTo(3));
	assertThat (plan.getRequirement(0), isEqualTo(sailing));
	assertThat (plan2.getRequirement(0), isEqualTo(sailing));
	assertThat (plan.getRequirement(1), isEqualTo(mapping));
	assertThat (plan2.getRequirement(1), isEqualTo(mapping));
	assertThat (plan2.getRequirement(2), isEqualTo(alphabet));

	plan.removeRequirement(sailing);
	assertThat (plan.getNumberOfRequirements(), isEqualTo(1));
	assertThat (plan2.getNumberOfRequirements(), isEqualTo(3));
	assertThat (plan.getRequirement(0), isEqualTo(mapping));
	assertThat (plan2.getRequirement(0), isEqualTo(sailing));
	assertThat (plan2.getRequirement(1), isEqualTo(mapping));
	assertThat (plan2.getRequirement(2), isEqualTo(alphabet));


}


UnitTest(zzCheckForMemoryLeaks) {
	assertThat(MemoryChecked::getCurrentCount(), isEqualTo(0));
}


