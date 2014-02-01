#!/bin/bash

if [ $# -eq 0 ]; then
	echo -e "Usage:\n	$ ./test.sh /path/to/fullerenes"
	exit 1
fi
cdir=`pwd`
cd $1
for i in c*; do
	echo -e "\n\nChecking $i:"
	time $cdir/backtrack < $i > $cdir/out/$i
done

exit 0
