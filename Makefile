all:
	g++ -o backtrack src/bt.cpp
	g++ -o check	src/check.cpp

clean:
	rm backtrack check *~ *.o 2> /dev/null
