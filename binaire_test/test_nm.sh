#!/bin/sh
mkdir /tmp/__nm_tests 2> /dev/null
for it in $@
do
	../cmake-build-debug/nm_otool $it | cat -e > /tmp/__nm_tests/our 2>&1
	nm $it | cat -e > /tmp/__nm_tests/their 2>&1
	diff /tmp/__nm_tests/our /tmp/__nm_tests/their > /tmp/__nm_tests"/$it"_diff
	if [[ -s /tmp/__nm_tests/"$it"_diff ]] ;
	then echo "$it: FAILURE" ;
	else echo "$it: SUCCESS" ;
	fi
done
