#include "researchplan.h"
#include "unittest.h"
#include <array>
#include <list>
#include <sstream>

using namespace std;

/**
 * A "test fixture" is a mechanism for providing common access to test
 * data that may be used in multiple tests.
 */
class Fixture {
public:
	const Topic alphabet;
	const Topic mining;
	const Topic commerce;
	const Topic sailing;
	const Topic trade;
	const Topic wheel;

	std::array<Topic, 2> topics2;
	std::array<Topic, 3> topics3;
	std::array<Topic, 4> topics4;
	std::array<Topic, 5> topics5;


	Fixture();

};

Fixture::Fixture()
: alphabet ("Alphabet", 15),
  mining ("Mining", 25),
  commerce ("Commerce", 30),
  sailing ("Sailing", 36),
  trade ("Trade", 45),
  wheel ("Wheel", 10),
  topics2{commerce, sailing},
  topics3{alphabet, mining, commerce},
  topics4{mining, alphabet, commerce, sailing},
  topics5{alphabet, mining, commerce, sailing, trade}
{

}



UnitTest(PlanDefaultConstructor) {
	ResearchPlan plan;
	assertThat (plan.getTopic(), isEqualTo(Topic()));
	assertThat (plan.getNumberOfRequirements(), isEqualTo(0));
	assertThat (plan, isEqualTo(ResearchPlan()));
	assertThat (plan, not(isLessThan(ResearchPlan())));
	assertThat (plan, not(isGreaterThan(ResearchPlan())));
}

UnitTest(PlanConstructor) {
	Fixture fix;
	ResearchPlan plan (fix.alphabet);

	assertThat (plan.getTopic(), isEqualTo(fix.alphabet));
	assertThat (plan.getNumberOfRequirements(), isEqualTo(0));
	assertThat (plan, isNotEqualTo(ResearchPlan()));
	assertThat (plan, isLessThan(ResearchPlan(fix.mining)));

	assertThat (plan.begin(), isEqualTo(plan.end()));

	ostringstream out;
	out << plan;
	assertThat (out.str(), contains("Alphabet"));
}

UnitTest(PlanConsInitList0) {
	Fixture fix;
	ResearchPlan plan (fix.trade, {fix.alphabet, fix.sailing, fix.commerce});
	ResearchPlan plan2 (fix.trade, {fix.alphabet, fix.commerce, fix.sailing});


	assertThat (plan.getTopic(), isEqualTo(fix.trade));
	assertThat (plan.getNumberOfRequirements(), isEqualTo(3));
	assertThat (plan, isNotEqualTo(ResearchPlan()));
	assertThat (plan, isLessThan(ResearchPlan(fix.wheel)));
	assertThat (plan, isGreaterThan(ResearchPlan(fix.mining)));

	assertThat(plan, isEqualTo(plan2));

	std::array<Topic,3> expected {fix.alphabet, fix.commerce, fix.sailing};
	assertThat (equal(plan.begin(), plan.end(),
			expected.begin(), expected.end()), isEqualTo(true));


	ostringstream out;
	out << plan;
	assertThat (out.str(), contains("Trade"));
	assertThat (out.str(), contains("(Alphabet"));
	assertThat (out.str(), contains("Commerce"));
	assertThat (out.str(), contains("Sailing"));
}

UnitTest(PlanConsInitListSingle) {
	Fixture fix;
	ResearchPlan plan (fix.trade, {fix.sailing});

	assertThat (plan.getTopic(), isEqualTo(fix.trade));
	assertThat (plan.getNumberOfRequirements(), isEqualTo(1));
	assertThat (plan, isNotEqualTo(ResearchPlan()));
	assertThat (plan, isLessThan(ResearchPlan(fix.wheel)));
	assertThat (plan, isGreaterThan(ResearchPlan(fix.mining)));

	std::array<Topic,1> expected {fix.sailing};
		assertThat (equal(plan.begin(), plan.end(),
				expected.begin(), expected.end()), isEqualTo(true));


	ostringstream out;
	out << plan;
	assertThat (out.str(), contains("Trade"));
	assertThat (out.str(), contains("(Sailing"));
}

UnitTest(PlanConsInitListEmpty) {
	Fixture fix;
	ResearchPlan plan (fix.trade, {});

	assertThat (plan.getTopic(), isEqualTo(fix.trade));
	assertThat (plan.getNumberOfRequirements(), isEqualTo(0));
	assertThat (plan, isNotEqualTo(ResearchPlan()));
	assertThat (plan, not(isLessThan(ResearchPlan(fix.commerce))));
	assertThat (plan, isGreaterThan(ResearchPlan(fix.mining)));

	assertThat(plan.begin(), isEqualTo(plan.end()));

	ostringstream out;
	out << plan;
	assertThat (out.str(), contains("Trade"));
	assertThat (out.str(), contains("()"));
}

UnitTest(PlanConsIter0) {
	Fixture fix;
	ResearchPlan plan1 (fix.trade, fix.topics3.begin(), fix.topics3.end());

	vector<Topic> v(fix.topics3.begin(), fix.topics3.end());
	ResearchPlan plan2 (fix.trade, v.begin(), v.end());

	assertThat (plan1.getTopic(), isEqualTo(fix.trade));
	assertThat (plan1.getNumberOfRequirements(), isEqualTo(3));
	assertThat (plan1, isEqualTo(plan2));

	std::array<Topic, 3> expected3 {fix.alphabet, fix.commerce, fix.mining};
	assertTrue (equal(plan1.begin(), plan1.end(), expected3.begin(), expected3.end()));

	list<Topic> list(fix.topics4.begin(), fix.topics4.end());
	ResearchPlan plan3 (fix.trade, list.begin(), list.end());
	std::array<Topic, 4> expected4 {fix.alphabet, fix.commerce, fix.mining, fix.sailing};
	assertTrue (equal(plan3.begin(), plan3.end(), expected4.begin(), expected4.end()));

	assertThat(plan1, isNotEqualTo(plan3));

	ostringstream out;
	out << plan1;
	assertThat (out.str(), contains("Trade"));
	assertThat (out.str(), contains("(Alphabet"));
	assertThat (out.str(), contains("Mining"));
	assertThat (out.str(), contains("Commerce"));
}

/**
 * Generate an always empty iterator range
 */
class BogusContainer {
	Topic x;
public:
	typedef Topic* iterator;
	typedef const Topic* const_iterator;

	iterator begin() {return &x;}
	iterator end() {return &x;}

	const_iterator begin() const {return &x;}
	const_iterator end() const {return &x;}
};

UnitTest(PlanConsIterEmpty) {
	Fixture fix;
	ResearchPlan plan1 (fix.trade, fix.topics3.begin(), fix.topics3.begin());

	vector<Topic> v(fix.topics3.begin(), fix.topics3.end());
	ResearchPlan plan2 (fix.trade, v.begin()+1, v.begin()+1);

	assertThat (plan1.getTopic(), isEqualTo(fix.trade));
	assertThat (plan1.getNumberOfRequirements(), isEqualTo(0));
	assertThat (plan1, isEqualTo(plan2));

	BogusContainer bc;
	ResearchPlan plan3 (fix.trade, bc.begin(), bc.end());

	assertThat(plan1, isEqualTo(plan3));

	ostringstream out;
	out << plan1;
	assertThat (out.str(), contains("Trade"));
	assertThat (out.str(), contains("()"));
}






UnitTest(PlanAddPrereq) {
	Fixture fix;

	ResearchPlan plan0(fix.trade);
	ResearchPlan plan (fix.trade);
	assertThat (plan, isEqualTo(plan0));

	plan.addRequirement(fix.commerce);
	assertThat (plan.getNumberOfRequirements(), isEqualTo(1));
	assertThat (plan, isNotEqualTo(plan0));
	assertThat (*(plan.begin()), isEqualTo(fix.commerce));

	plan.addRequirement(fix.sailing);
	assertThat (plan.getNumberOfRequirements(), isEqualTo(2));
	assertTrue (equal(plan.begin(), plan.end(),
			    fix.topics2.begin(), fix.topics2.end()));

	plan.addRequirement(fix.commerce);
	assertThat (plan.getNumberOfRequirements(), isEqualTo(2));
	assertTrue (equal(plan.begin(), plan.end(),
			    fix.topics2.begin(), fix.topics2.end()));

	std::array<Topic, 2> expected {fix.commerce, fix.sailing};
	assertTrue (equal(plan.begin(), plan.end(), expected.begin(), expected.end()));


	ostringstream out;
	out << plan;
	string outStr = out.str();
	assertThat (outStr, contains("Trade"));
	assertThat (outStr, contains("Sailing"));
	assertThat (outStr, contains("Commerce"));

}

UnitTest(PlanRemovePrereq) {
	Fixture fix;

	ResearchPlan plan0(fix.trade);
	ResearchPlan plan (fix.trade);
	assertThat (plan, isEqualTo(plan0));

	plan.addRequirement(fix.commerce);
	plan.addRequirement(fix.sailing);
	plan.addRequirement(fix.alphabet);

	plan.removeRequirement(fix.commerce);
	assertThat (plan.getNumberOfRequirements(), isEqualTo(2));
	std::array<Topic, 2> expected {fix.alphabet, fix.sailing};
	assertTrue (equal(plan.begin(), plan.end(), expected.begin(), expected.end()));

	ostringstream out;
	out << plan;
	string outStr = out.str();
	assertThat (outStr, contains("Trade"));
	assertThat (outStr, contains("Sailing"));
	assertThat (outStr, not(contains("Commerce")));

}




UnitTest(PlanCopy) {
	Fixture fix;

	ResearchPlan plan(fix.trade);
	plan.addRequirement(fix.sailing);
	plan.addRequirement(fix.commerce);

	ResearchPlan plan2 (plan);
	assertThat(plan2, isEqualTo(plan));

	plan2.addRequirement(fix.alphabet);
	assertThat(plan2, isNotEqualTo(plan));

	assertThat (plan.getNumberOfRequirements(), isEqualTo(2));
	assertThat (plan2.getNumberOfRequirements(), isEqualTo(3));
	assertTrue (equal(plan.begin(), plan.end(),
			fix.topics2.begin(), fix.topics2.end()));

	std::array<Topic, 3> plan2prereqs {fix.alphabet, fix.commerce, fix.sailing};
	assertTrue (equal(plan2.begin(), plan2.end(),
				plan2prereqs.begin(), plan2prereqs.end()));

	plan.removeRequirement(fix.commerce);
	assertThat (plan.getNumberOfRequirements(), isEqualTo(1));
	assertThat (plan2.getNumberOfRequirements(), isEqualTo(3));
	assertThat (*(plan.begin()), isEqualTo(fix.sailing));
	assertTrue (equal(plan2.begin(), plan2.end(),
					plan2prereqs.begin(), plan2prereqs.end()));
}

UnitTest(PlanAssign) {
	Fixture fix;

	ResearchPlan plan(fix.trade);
	plan.addRequirement(fix.commerce);
	plan.addRequirement(fix.sailing);
    cout << "PLanAssign" << endl;
	cout << "Plan: " << endl <<plan << endl;
	ResearchPlan plan2;
	cout << "Plan2: " << endl <<plan2 << endl;
	ResearchPlan plan3(plan2 = plan);
	cout << "Plan3: " << endl <<plan3 << endl;
	assertThat(plan2, isEqualTo(plan));
	assertThat(plan3, isEqualTo(plan));

	plan2.addRequirement(fix.alphabet);
	assertThat(plan2, isNotEqualTo(plan));

	assertThat (plan.getNumberOfRequirements(), isEqualTo(2));
	assertThat (plan2.getNumberOfRequirements(), isEqualTo(3));
	assertTrue (equal(plan.begin(), plan.end(),
			fix.topics2.begin(), fix.topics2.end()));

	std::array<Topic, 3> plan2prereqs {fix.sailing, fix.commerce, fix.alphabet};
	std::array<Topic, 3> expected3 {fix.alphabet, fix.commerce, fix.sailing};
	assertTrue (equal(plan2.begin(), plan2.end(),
				expected3.begin(), expected3.end()));

	plan.removeRequirement(fix.commerce);
	std::array<Topic, 1> expected1 {fix.sailing};
	assertThat (plan.getNumberOfRequirements(), isEqualTo(1));
	assertThat (plan2.getNumberOfRequirements(), isEqualTo(3));
	assertThat (*(plan.begin()), isEqualTo(fix.sailing));
	assertTrue (equal(plan.begin(), plan.end(),
					expected1.begin(), expected1.end()));
	assertTrue (equal(plan2.begin(), plan2.end(),
					expected3.begin(), expected3.end()));
}


UnitTest(zzCheckForMemoryLeaks) {
	assertThat(MemoryChecked::getCurrentCount(), isEqualTo(0));
}


