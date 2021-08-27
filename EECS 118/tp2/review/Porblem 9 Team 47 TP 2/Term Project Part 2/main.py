import sys
import csv
import time
import networkx as nx
from functions import max_degree
from functions import is_path

class Line:
  def __init__(self, node1, node2, weight, color):
    self.node1 = node1
    self.node2 = node2
    self.weight = weight
    self.color = color


# graph = []

arguments = len(sys.argv)
if (arguments != 2):
  print("Incorrect amount of arguments")

G = nx.Graph()

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

print("All lines were saved...")
time.sleep(.4)

node_list = list(G.nodes)
print("node_list:", node_list)

num = int(input("Input max_degree #:"))

final_list = []

path_count = 0
for n1 in node_list:
  node1 = node_list[node_list.index(n1)]
  for n2 in node_list:
    if (node_list.index(n2) < len(node_list)):
      node2 = node_list[node_list.index(n2)]
      if (is_path(G, node1, node2) == True and node1 != node2):
        print("Inputs are a path...")
        paths = list(nx.all_simple_paths(G, node1, node2))
        p = 0
        path_count = 0
        edge_list = []
        path_list = []
        for path in paths:
          print("path", path)
          path_list.append(path)
          path_count += 1
          edge_list.append([])
          for node in path:
            if (path.index(node) < len(path) - 1):
              edge_list[p].append((path[path.index(node)], path[path.index(node) + 1]))
          p += 1
        s = edge_list
        print("s =", s)
        print("Checking max_degree...")
        p = 0
        for edge in edge_list:
          if (max_degree(s[p], num, G) == True):
            if (p < path_count):
              final_list.append(path_list[p])
            p += 1
          else:
            print("Max_degree test failed")
            p += 1
        print("path list", path_list)


print("final_list", final_list)
print("length of final_list=", len(final_list))
path_count = 1
for path in final_list:
  p = 0
  print("Path "+str(path_count))
  path_count += 1
  for node in path:
    if (path.index(node) < len(path) - 1):
      print(path[path.index(node)], path[path.index(node) + 1])
    p += 1

path_count = 1
with open("output.csv", 'w', newline='') as file:
  writer = csv.writer(file)
  for path in final_list:
    p = 0
    writer.writerow(["path_" + str(path_count)])
    path_count += 1
    for node in path:
      if (path.index(node) < len(path) - 1):
        writer.writerow([path[path.index(node)], path[path.index(node)+ 1]])
      p += 1







