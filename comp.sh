#!/bin/bash

cd ../fullerenes
for i in c*; do
	echo -e "\n\nChecking $i on 1:"
	time ../a1/bt1 < $i > ../a1/out/1$i
	echo -e "\n\nChecking $i on 2:"
	time ../a1/bt2 < $i > ../a1/out/2$i
done

exit 0
