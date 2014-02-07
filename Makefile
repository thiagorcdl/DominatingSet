all:
	g++ -o backtrack src/q1_bt.cpp
	g++ -o check	src/q1_check.cpp

clean:
	rm backtrack check *~ *.o 2> /dev/null
