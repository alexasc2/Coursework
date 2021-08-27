import sys
import csv
from functions import max_degree
from functions import is_path
import networkx as nx

arguments = len(sys.argv)
if (arguments != 2):
  print("Incorrect amount of arguments")

G = nx.Graph()
edge_list =[]

filename = str(sys.argv[1])
with open (filename, mode='r') as csv_file:
  csv_reader = csv.reader(csv_file, delimiter=',')
  for row in csv_reader:
    if (row[0] == "Node1"):
      continue
    else:
      print(row[0], row[1], row[2], row[3])
      # temp = Line(row[0], row[1], row[2], row[3])
      # graph.append(temp)
      G.add_node(row[0])
      G.add_node(row[1])
      G.add_edge(row[0], row[1])

print("G.edges()", G.edges())
print("Choosing possible path...\n")
node1 = input("Choose source node: ")
node2 = input("Choose target node: ")
if (is_path(G, node1, node2) == True):
	print("Inputs are a path...")
	paths = list(nx.all_simple_paths(G, node1, node2))
	print("paths = ", paths)
	p = 0
	for path in paths:
		print("path", path)
		edge_list.append([])
		for node in path:
			if (path.index(node) < len(path) - 1):
				edge_list[p].append((path[path.index(node)], path[path.index(node) + 1]))
		p += 1
	
	s = edge_list
	print("s =", s)
	print("Checking max_degree...")
	num = int(input("Input max_degree #:"))
	p = 0
	for edge in edge_list:
		if (max_degree(s[p], num, G) == True):

			p += 1
		else:
			print("Max_degree test failed")
			p += 1


else:
	print("Inputs are not a path...")

