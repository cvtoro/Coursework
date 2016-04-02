#Cecilia Villatoro
#COSC 262


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



def initializeSearch(g, processed, discovered, parent):
	for i in range(g.numVertices):
		processed.append(False)
		discovered.append(False)
		parent.append(None)



import queue
def bfs_tree(g, s, discovered, processed, parent):
	# set discovered, processed and parent array
	connected = []

	q = queue.Queue(maxsize = 0)
	# place starting vertex in queue
	q.put(s)
	discovered[s] = True
	connected.append(s)

	adjList = g.adjacency_list

	while(q.empty() == False):
		u = q.get()
		for tup in adjList[u]:
			
			v = tup[0]
			if discovered[v] == False:
				discovered[v] = True
				connected.append(v)
				parent[v] = u

				q.put(v)
		processed[u] = True
	
	return connected


def connected_components(g):
	processed = []
	discovered = []
	parent = []
	initializeSearch(g,processed,discovered,parent)
	connectedComponents = []
	numVertices = g.numVertices
	for v in range(numVertices):
		if discovered[v] == False:
			connectedComponent = bfs_tree(g, v, discovered, processed, parent)
			connectedComponents.append(connectedComponent)
	return connectedComponents

graph_string = """\
U 2
0 1
"""

print(sorted(sorted(c) for c in connected_components(Graph(graph_string))))


graph_string = """\
U 2
"""

print(sorted(sorted(c) for c in connected_components(Graph(graph_string))))

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

print(sorted(sorted(c) for c in connected_components(Graph(graph_string))))


