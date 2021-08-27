*****************************************************************************
EECS 118 Term Project Part 2 README
Problem 65, Members: Alexander Choi, Andrew Le

Predicates: find s where is_spanning_tree(s) and total_weights(s,t) and t > C

Uses NetworkX library
https://networkx.github.io/documentation/networkx-1.10/install.html

Command Line Usage:
	python testing.py [test file name].csv

To use the attached test.csv file:
	python testing.py test.csv

The test.csv file has a total weight of 3.00, and is a minimum spanning tree.
The program cannot test for the case of two unconnected graphs in the same
csv file.  Please seperate both graphs into two csv files before testing the 
program.

The program is fully functional and returns a report whether the predicates
are true or false.

If the program predicate result is true, the edgelist is saved to result.csv.
Otherwise, the edgelist saves an empty edgelist to result.csv.

WARNING: result.csv is replaced upon every activation of the program.  Save
the file to a different directory or rename to keep the result.
*****************************************************************************