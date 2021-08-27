import csv
import networkx as nx
import os
import os.path

def init():
	global s 
	global pathcount 

	s = nx.Graph()
	pathcount = 1

#CSV parse and graph construction function
def read(name):
	with open(name,'r') as csvfile:
		testfile = csv.reader(csvfile,delimiter=',')
		for row in testfile:
			s.add_node(int(row[0]))
			s.add_node(int(row[1]))
			s.add_edge(int(row[0]),int(row[1]),weight=float(row[2]),color=row[3])
	return s

#set_pathcount() and get_pathcount() are for increment access for the result.csv file
#i.e. path_1 to path_2 to path_3,etc.
def set_pathcount(new_pathcount):
	pathcount = new_pathcount

def get_pathcount():
	return pathcount

#saves the file in a s
def write(p):
	if os.path.isfile('result.csv'):
		os.remove('result.csv')
	pathnumber = 'path_'+str(pathcount)
	with open('result.csv','w',newline='') as csvfile:
		writefile = csv.writer(csvfile,delimiter=',')
		writefile.writerow([pathnumber])
		for row in p.edges():
			writefile.writerow(row)

#finds the edgelist of a minimum spanning graph using Kruskal's algorithm.
#See NetworkX documentation for details
#If the graph has a cycle, the function returns an edgelist of zero
#The graph should have the same number of edges as the edgelist if it is a spanning tree
#The find_paths() function is equivalent to the is_spanning_tree predicate and returns true/false
def find_paths(g):
	test = list(nx.minimum_spanning_edges(g,data=True,weight='weight'))
	return len(test) == g.size()

#compare_total_weights is equivalent to the total_weights predicate
#should always return true for this predicate case
def compare_total_weights(g,c):
	return g.size(weight='weight') == c

#compares the total weight of the graph with a user input C
#equivalent to predicate t > C and returns true or false
def t_C_comparison(t,C):
	return s.size(weight='weight') > C

#menu helper that asks for the user input
def print_menu():
	print("Our assigned predicate: 65. find s where is_spanning_tree(s) and total_weight(s,t) and t>C")
	C = input("Enter the input value, C: ")
	return C