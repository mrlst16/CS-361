#include "unittest.h"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <set>
#include "encyclopedia.h"

using namespace std;


UnitTest(EncyclopediaConstructor) {
	Encyclopedia enc;
	assertThat (enc.end(), isEqualTo(enc.begin()));
}


UnitTest(EncyclopediaAddCourse) {
	Topic alphabet ("Alphabet", 15);
	Topic commerce ("Commerce", 25);
	Topic sailing ("Sailing", 36);
	Topic mapping ("Mapping", 30);
	Topic trading ("Trading", 35);

	Encyclopedia enc;
	enc.addPlanRequirement(commerce, alphabet);
	assertThat (distance(enc.begin(), enc.end()), isEqualTo(2));
	assertTrue(enc.containsTopic(alphabet));
	assertTrue(enc.containsTopic(commerce));
	assertFalse(enc.containsTopic(sailing));
	assertFalse(enc.containsTopic(mapping));
	assertFalse(enc.containsTopic(trading));

	set<Topic> expected1 {alphabet, commerce};
	set<Topic> observed1;
	transform(enc.begin(), enc.end(), inserter(observed1, observed1.begin()),
			[] (const ResearchPlan& plan) {return plan.getTopic();});
	assertThat(observed1, isEqualTo(expected1));

	enc.addPlanRequirement(trading, sailing);
	assertThat (distance(enc.begin(), enc.end()), isEqualTo(4));
	assertTrue(enc.containsTopic(alphabet));
	assertTrue(enc.containsTopic(commerce));
	assertTrue(enc.containsTopic(sailing));
	assertFalse(enc.containsTopic(mapping));
	assertTrue(enc.containsTopic(trading));

	set<Topic> expected2 {alphabet, commerce, sailing, trading};
	set<Topic> observed2;
	transform(enc.begin(), enc.end(), inserter(observed2, observed2.begin()),
			[] (const ResearchPlan& plan) {return plan.getTopic();});
	assertThat(observed2, isEqualTo(expected2));

	enc.addPlanRequirement(trading, mapping);
	assertThat (distance(enc.begin(), enc.end()), isEqualTo(5));
	assertTrue(enc.containsTopic(alphabet));
	assertTrue(enc.containsTopic(commerce));
	assertTrue(enc.containsTopic(sailing));
	assertTrue(enc.containsTopic(mapping));
	assertTrue(enc.containsTopic(trading));

	enc.addPlanRequirement(mapping, commerce);
	assertThat (distance(enc.begin(), enc.end()), isEqualTo(5));
	assertTrue(enc.containsTopic(alphabet));
	assertTrue(enc.containsTopic(commerce));
	assertTrue(enc.containsTopic(sailing));
	assertTrue(enc.containsTopic(mapping));
	assertTrue(enc.containsTopic(trading));

	enc.addPlanRequirement(sailing, commerce);
	assertThat (distance(enc.begin(), enc.end()), isEqualTo(5));
	assertTrue(enc.containsTopic(alphabet));
	assertTrue(enc.containsTopic(commerce));
	assertTrue(enc.containsTopic(sailing));
	assertTrue(enc.containsTopic(mapping));
	assertTrue(enc.containsTopic(trading));

	set<Topic> expected3 {alphabet, commerce, mapping, sailing, trading};
	set<Topic> observed3;
	transform(enc.begin(), enc.end(), inserter(observed3, observed3.begin()),
			[] (const ResearchPlan& plan) {return plan.getTopic();});
	assertThat(observed3, isEqualTo(expected3));

	auto plan = enc.getPlan(commerce);
    assertThat (plan.getTopic(), isEqualTo(commerce));
    assertThat(plan.getNumberOfRequirements(), isEqualTo(1));

    plan = enc.getPlan(trading);
    assertThat (plan.getTopic(), isEqualTo(trading));
    assertThat(plan.getNumberOfRequirements(), isEqualTo(2));
}




UnitTest(EncyclopediaRemoveCourse) {
	Topic alphabet ("Alphabet", 15);
	Topic commerce ("Commerce", 25);
	Topic sailing ("Sailing", 36);
	Topic mapping ("Mapping", 30);
	Topic trading ("Trading", 35);

	Encyclopedia enc;
	enc.addPlanRequirement(commerce, alphabet);
	enc.addPlanRequirement(trading, sailing);
	enc.addPlanRequirement(trading, mapping);
	enc.addPlanRequirement(mapping, commerce);
	enc.addPlanRequirement(sailing, commerce);

	enc.removeTopic(mapping);

	assertThat (distance(enc.begin(), enc.end()), isEqualTo(4));
	assertTrue(enc.containsTopic(alphabet));
	assertTrue(enc.containsTopic(commerce));
	assertTrue(enc.containsTopic(sailing));
	assertFalse(enc.containsTopic(mapping));
	assertTrue(enc.containsTopic(trading));

    auto plan = enc.getPlan(trading);
    assertThat (plan.getTopic(), isEqualTo(trading));
    assertThat(plan.getNumberOfRequirements(), isEqualTo(1));
}

UnitTest(EncyclopediaCopy) {
	Topic alphabet ("Alphabet", 15);
	Topic commerce ("Commerce", 25);
	Topic sailing ("Sailing", 36);
	Topic mapping ("Mapping", 30);
	Topic trading ("Trading", 35);

	Encyclopedia enc;
	enc.addPlanRequirement(commerce, alphabet);
	enc.addPlanRequirement(trading, sailing);
	enc.addPlanRequirement(trading, mapping);
	enc.addPlanRequirement(mapping, commerce);
	enc.addPlanRequirement(sailing, commerce);

	Encyclopedia enc2 (enc);

	assertThat(enc2, isEqualTo(enc));

	enc.removeTopic(mapping);

	assertThat(enc2, isNotEqualTo(enc));

	assertThat (distance(enc2.begin(), enc2.end()), isEqualTo(5));
	assertTrue(enc2.containsTopic(alphabet));
	assertTrue(enc2.containsTopic(commerce));
	assertTrue(enc2.containsTopic(sailing));
	assertTrue(enc2.containsTopic(mapping));
	assertTrue(enc2.containsTopic(trading));

    auto plan = enc2.getPlan(trading);
    assertThat (plan.getTopic(), isEqualTo(trading));
    assertThat(plan.getNumberOfRequirements(), isEqualTo(2));
}



UnitTest(EncyclopediaAssign) {
	Topic alphabet ("Alphabet", 15);
	Topic commerce ("Commerce", 25);
	Topic sailing ("Sailing", 36);
	Topic mapping ("Mapping", 30);
	Topic trading ("Trading", 35);

	Encyclopedia enc;
	enc.addPlanRequirement(commerce, alphabet);
	enc.addPlanRequirement(trading, sailing);
	enc.addPlanRequirement(trading, mapping);
	enc.addPlanRequirement(mapping, commerce);
	enc.addPlanRequirement(sailing, commerce);

	Encyclopedia enc2;

	Encyclopedia enc3 (enc2 = enc);

	assertThat(enc2, isEqualTo(enc));
	assertThat(enc3, isEqualTo(enc));

	enc.removeTopic(mapping);

	assertThat(enc2, isNotEqualTo(enc));

	assertThat (distance(enc2.begin(), enc2.end()), isEqualTo(5));
	assertTrue(enc2.containsTopic(alphabet));
	assertTrue(enc2.containsTopic(commerce));
	assertTrue(enc2.containsTopic(sailing));
	assertTrue(enc2.containsTopic(mapping));
	assertTrue(enc2.containsTopic(trading));

    auto plan = enc2.getPlan(trading);
    assertThat (plan.getTopic(), isEqualTo(trading));
    assertThat(plan.getNumberOfRequirements(), isEqualTo(2));
}




UnitTest(EncyclopediaRead) {
	Topic agriculture ("Agriculture", 10);
	Topic alphabet ("Alphabet", 15);
	Topic printing ("Printing", 100);
	Topic publishing ("Publishing", 100);

	string testIn =
			string("Agriculture: 10\n") +
			+ "Alphabet: 15\n"
			"Printing: Alphabet, 100\n" +
			"Publishing: Printing, Agriculture, 100\n"
			+ "---";
	istringstream in (testIn);
	Encyclopedia enc;
	enc.read(in);

	assertTrue (enc.containsTopic(agriculture));
	assertTrue (enc.containsTopic(printing));
	assertTrue (enc.containsTopic(publishing));
	assertTrue (enc.containsTopic(alphabet));

	assertThat(distance(enc.begin(), enc.end()), isEqualTo(4));

    assertThat(enc.getPlan(agriculture).getNumberOfRequirements(), isEqualTo(0));
    assertThat(enc.getPlan(printing).getNumberOfRequirements(), isEqualTo(1));
    assertThat(enc.getPlan(publishing).getNumberOfRequirements(), isEqualTo(2));

    assertThat(enc.getPlan(agriculture).getTopic().researchCost, isEqualTo(10));
    assertThat(enc.getPlan(alphabet).getTopic().researchCost, isEqualTo(15));
    assertThat(enc.getPlan(printing).getTopic().researchCost, isEqualTo(100));
    assertThat(enc.getPlan(publishing).getTopic().researchCost, isEqualTo(100));

}



