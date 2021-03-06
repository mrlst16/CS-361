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
  topics4{alphabet, mining, commerce, sailing},
  topics5{alphabet, mining, commerce, sailing, trade}
{

}



UnitTest(PlanDefaultConstructor) {
    cout << "Memory beginning on PlanDefaultConstructor " << MemoryChecked::getCurrentCount() << endl;
	ResearchPlan plan;
	assertThat (plan.getTopic(), isEqualTo(Topic()));
	assertThat (plan.getNumberOfRequirements(), isEqualTo(0));
	assertThat (plan, isEqualTo(ResearchPlan()));
	assertThat (plan, not(isLessThan(ResearchPlan())));
	assertThat (plan, not(isGreaterThan(ResearchPlan())));
}

UnitTest(PlanConstructor) {
    cout << "Memory beginning on PlanConstructor " << MemoryChecked::getCurrentCount() << endl;

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
	cout << "Memory beginning on PlanConsInitList0 " << MemoryChecked::getCurrentCount() << endl;
	Fixture fix;
	ResearchPlan plan (fix.trade, {fix.alphabet, fix.commerce, fix.sailing});

	assertThat (plan.getTopic(), isEqualTo(fix.trade));
	assertThat (plan.getNumberOfRequirements(), isEqualTo(3));
	assertThat (plan, isNotEqualTo(ResearchPlan()));
	assertThat (plan, isLessThan(ResearchPlan(fix.wheel)));
	assertThat (plan, isGreaterThan(ResearchPlan(fix.mining)));

	ostringstream out;
	out << plan;
	assertThat (out.str(), contains("Trade"));
	assertThat (out.str(), contains("(Alphabet"));
	assertThat (out.str(), contains("Commerce"));
	assertThat (out.str(), contains("Sailing"));
}

UnitTest(PlanConsInitListSingle) {
	cout << "Memory beginning on PlanConsInitListSingle " << MemoryChecked::getCurrentCount() << endl;
	Fixture fix;
	ResearchPlan plan (fix.trade, {fix.sailing});

	assertThat (plan.getTopic(), isEqualTo(fix.trade));
	assertThat (plan.getNumberOfRequirements(), isEqualTo(1));
	assertThat (plan, isNotEqualTo(ResearchPlan()));
	assertThat (plan, isLessThan(ResearchPlan(fix.wheel)));
	assertThat (plan, isGreaterThan(ResearchPlan(fix.mining)));

	ostringstream out;
	out << plan;
	assertThat (out.str(), contains("Trade"));
	assertThat (out.str(), contains("(Sailing"));
}

UnitTest(PlanConsInitListEmpty) {
	cout << "Memory beginning on PlanConsInitListEmpty " << MemoryChecked::getCurrentCount() << endl;
	Fixture fix;
	ResearchPlan plan (fix.trade, {});

	assertThat (plan.getTopic(), isEqualTo(fix.trade));
	assertThat (plan.getNumberOfRequirements(), isEqualTo(0));
	assertThat (plan, isNotEqualTo(ResearchPlan()));
	assertThat (plan, not(isLessThan(ResearchPlan(fix.commerce))));
	assertThat (plan, isGreaterThan(ResearchPlan(fix.mining)));

	ostringstream out;
	out << plan;
	assertThat (out.str(), contains("Trade"));
	assertThat (out.str(), contains("()"));
}

UnitTest(PlanConsIter0) {
	cout << "Memory beginning on PlanConsIter0 " << MemoryChecked::getCurrentCount() << endl;
	Fixture fix;
    Topic arg1 = fix.trade;

	ResearchPlan plan1 (arg1, fix.topics3.begin(), fix.topics3.end());

	vector<Topic> v(fix.topics3.begin(), fix.topics3.end());
	ResearchPlan plan2 (fix.trade, v.begin(), v.end());

	assertThat (plan1.getTopic(), isEqualTo(fix.trade));
	assertThat (plan1.getNumberOfRequirements(), isEqualTo(3));
	assertThat (plan1, isEqualTo(plan2));

	list<Topic> list(fix.topics4.begin(), fix.topics4.end());
	ResearchPlan plan3 (fix.trade, list.begin(), list.end());

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
	cout << "Memory beginning on PlanConsIterEmpty " << MemoryChecked::getCurrentCount() << endl;
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
	cout << "Memory beginning on PlanAddPrereq " << MemoryChecked::getCurrentCount() << endl;
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

	ostringstream out;
	out << plan;
	string outStr = out.str();
	assertThat (outStr, contains("Trade"));
	assertThat (outStr, contains("Sailing"));
	assertThat (outStr, contains("Commerce"));

}

UnitTest(PlanRemovePrereq) {
	cout << "Memory beginning on PlanRemovePrereq " << MemoryChecked::getCurrentCount() << endl;
	Fixture fix;

	ResearchPlan plan0(fix.trade);
	ResearchPlan plan (fix.trade);
	assertThat (plan, isEqualTo(plan0));

	plan.addRequirement(fix.commerce);
	plan.addRequirement(fix.sailing);

	plan.removeRequirement(fix.commerce);
	assertThat (plan.getNumberOfRequirements(), isEqualTo(1));
	assertThat (*(plan.begin()), isEqualTo(fix.sailing));

	ostringstream out;
	out << plan;
	string outStr = out.str();
	assertThat (outStr, contains("Trade"));
	assertThat (outStr, contains("Sailing"));
	assertThat (outStr, not(contains("Commerce")));

}




UnitTest(PlanCopy) {
	cout << "Memory beginning on PlanCopy " << MemoryChecked::getCurrentCount() << endl;
	Fixture fix;

	ResearchPlan plan(fix.trade);
	plan.addRequirement(fix.commerce);
	plan.addRequirement(fix.sailing);

	ResearchPlan plan2 (plan);
	assertThat(plan2, isEqualTo(plan));

	plan2.addRequirement(fix.alphabet);
	assertThat(plan2, isNotEqualTo(plan));

	assertThat (plan.getNumberOfRequirements(), isEqualTo(2));
	assertThat (plan2.getNumberOfRequirements(), isEqualTo(3));
	assertTrue (equal(plan.begin(), plan.end(),
			fix.topics2.begin(), fix.topics2.end()));

	std::array<Topic, 3> plan2prereqs {fix.commerce, fix.sailing, fix.alphabet};
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
	cout << "Memory beginning on PlanAssign " << MemoryChecked::getCurrentCount() << endl;
	Fixture fix;

	ResearchPlan plan(fix.trade);
	plan.addRequirement(fix.commerce);
	plan.addRequirement(fix.sailing);

	ResearchPlan plan2;
	ResearchPlan plan3(plan2 = plan);
	assertThat(plan2, isEqualTo(plan));
	assertThat(plan3, isEqualTo(plan));

	plan2.addRequirement(fix.alphabet);
	assertThat(plan2, isNotEqualTo(plan));

	assertThat (plan.getNumberOfRequirements(), isEqualTo(2));
	assertThat (plan2.getNumberOfRequirements(), isEqualTo(3));
	assertTrue (equal(plan.begin(), plan.end(),
			fix.topics2.begin(), fix.topics2.end()));

	std::array<Topic, 3> plan2prereqs {fix.commerce, fix.sailing, fix.alphabet};
	assertTrue (equal(plan2.begin(), plan2.end(),
				plan2prereqs.begin(), plan2prereqs.end()));

	plan.removeRequirement(fix.commerce);
	assertThat (plan.getNumberOfRequirements(), isEqualTo(1));
	assertThat (plan2.getNumberOfRequirements(), isEqualTo(3));
	assertThat (*(plan.begin()), isEqualTo(fix.sailing));
	assertTrue (equal(plan2.begin(), plan2.end(),
					plan2prereqs.begin(), plan2prereqs.end()));
}


UnitTest(zzCheckForMemoryLeaks) {
	assertThat(MemoryChecked::getCurrentCount(), isEqualTo(0));
}


