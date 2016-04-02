#Cecilia Villatoro
#COSC 262
#using depth first search to check whether a graph has a cycle
#cycle found when reach a vertex that has been seen before

class Graph:
	

	def processString(self, graph_string):
		result = ["","","",""]
		graphRows = graph_string.splitlines()
		i = 0
		numVertices = 0
		adjacency_list = []

		for line in graphRows:
			line = line.split()
			if i == 0:
				directed = line[0]
				if directed == 'D':
					result[0] = True
				else: 
					result[0] = False
				head2 = line[1]
				if head2 == 'W':
					result[1] = True
					numVertices = line[2]
					result[3] = numVertices
				else:
					result[1] = False
					numVertices = head2
					result[3] = numVertices
				for n in range(int(numVertices)):
					adjacency_list.append([])

			else:
				#print(int(line[1]))
				# print adjacency_list
				weighted = None
				if result[1]:
					weighted = int(line[2])
				adjacency_list[int(line[0])].append((int(line[1]), weighted))
				if result[0] == False:
					weighted = None
					if result[1]:
						weighted = int(line[2])
					adjacency_list[int(line[1])].append((int(line[0]), weighted))


			i +=1
		result[2] = adjacency_list
		return result
	def __init__(self, graph_string):
		result = self.processString(graph_string)
		self.directed = result[0]
		self.weighted = result[1]
		self.adjacency_list = result[2]
		self.numVertices = int(result[3])


def process_edge(x, y, parent):

	if (parent[y] != x): #found a cycle
	#implies that y is an ancestor of x
		return True
	else:
		return False

def dfs_tree_aux(g, s, processed, discovered, parent, hasCycle = False):
	discovered[s] = True
	sAdjList = g.adjacency_list[s]
	
	for tup in sAdjList:
		v = tup[0]
		if discovered[v] == False:
			parent[v] = s
			dfs_tree_aux(g, v, processed, discovered, parent)
		else:
			
			hasCycle = process_edge(s, v, parent)

	processed[s] = True
	return hasCycle



def initializeSearch(g, processed, discovered, parent):
	for i in range(g.numVertices):
		processed.append(False)
		discovered.append(False)
		parent.append(None)


def dfs_tree(g, s):
	processed = []
	discovered = []
	parent = []
	initializeSearch(g, processed, discovered, parent)
	return dfs_tree_aux(g, s, processed, discovered, parent)

def has_cycle(g):
	s = 1
	return dfs_tree(g,s)

graph_string = """\
U 2
0 1
"""

print(has_cycle(Graph(graph_string)))

graph_string = """\
U 2
"""

print(has_cycle(Graph(graph_string)))


graph_string = """\
U 3
0 1
1 2
2 0
"""

print(has_cycle(Graph(graph_string)))

# graph from the textbook example
graph_string = """\
U 7
1 2
1 5
1 6
2 3
2 5
3 4
4 5
"""

print(has_cycle(Graph(graph_string)))






