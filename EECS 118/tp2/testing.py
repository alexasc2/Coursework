import functions
import networkx as nx
import sys

functions.init()
s = functions.read(sys.argv[1])
C = functions.print_menu()

#predicate results
p1 = functions.find_paths(s)
p2 = functions.compare_total_weights(s,s.size(weight='weight'))
p3 = functions.t_C_comparison(s.size(weight='weight'),float(C))

if p1 and p2 and p3:
	#Writes the graph into the result.csv file
	functions.write(s)

	#adjusts the csv header for the next graph header in the result.csv
	newpc = functions.get_pathcount()+1
	functions.set_pathcount(newpc)
	#ends the program with a report that the predicate is true
	print("find s where is_spanning_tree(s) and total_weight(s,t) and t > C = True")

else:
	#writes an empty csv result file when the predicate is false
	functions.write(nx.Graph())
	newpc = functions.get_pathcount()+1
	functions.set_pathcount(newpc)

	#lists the individual predicates stating their states
	#ends the program with a report that the predicate is false
	print("Predicate 1: is_spanning_tree = " + str(p1))
	print("Predicate 2: total_weights = " + str(p2))
	print("Predicate 3: t > C = " + str(p3))
	print("find s where is_spanning_tree(s) and total_weight(s,t) and t > C = False")
