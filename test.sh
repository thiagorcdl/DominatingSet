#!/bin/bash

cd fullerenes
for i in c*; do
	echo -e "\n\nChecking $i:"
	time ../backtrack < $i > ../out/$i
done

exit 0
