import networkx as nx

def max_degree(s, num, graph):
	count = 0
	temp = list(graph.edges())
	for edge in s: #checking if edge set is on graph
		left = edge[0]
		right = edge[1]
		new_edge = (edge[1], edge[0])
		if (edge not in temp and (new_edge not in temp)):
			print("Set is not in the graph...")
			return False

	node_list = [] #used for checking node degree in the graph
	while count < len(s): #checks for duplicate nodes and makes sure not to add them
		if(s[count][0] not in node_list):
			node_list.append(s[count][0])
		if(s[count][1] not in node_list):
			node_list.append(s[count][1])
		count += 1

	print("node_list =", node_list)
	for node in node_list:
		print("node =", node, "node degree =", graph.degree[node])
		if (graph.degree[node] == num):
			continue
		else:
			print("Failed max_degree check...")
			return False
	print("Passed max_degree check...")
	return True

# def is_path(node_list, graph):
# 	count = 1
# 	first = node_list[count-1]
# 	second = node_list[count]
# 	temp = [first, second]
# 	length = len(graph.nodes())
# 	while (count < length):
# 		test = nx.is_simple_path(graph, temp)
# 		count += 1
# 		if test is False:
# 			node_list.remove(first)
# 			node_list.remove(second)
# 	return node_list

def is_path(graph, node1, node2):
	nodes = [node1, node2]
	if (nx.has_path(graph, node1, node2) is True):
		return True
	else:
		return False





		


