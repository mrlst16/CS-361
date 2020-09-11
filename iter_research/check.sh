#!/bin/sh
gdb -ex 'ptype ResearchPlan' -batch $1 > sanityCheck.txt
OK=1
if ! grep -q  'vector<Topic.*requirements' sanityCheck.txt; then
    OK=0
fi
if grep -q 'int numberOfRequirements' sanityCheck.txt; then
    OK=0
fi
if grep -q 'int maxRequirements' sanityCheck.txt; then
    OK=0
fi
intCount=`grep int sanityCheck.txt | wc -l`
if test $intCount -ne 1 ; then
    OK=0
fi

if test $OK -eq 0 ; then
	echo ReseachPlan data members were not modified according to the assignment instructions.
	rm $1 $2
	exit 1
fi
