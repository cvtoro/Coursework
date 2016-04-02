#Cecilia Villatoro
#COSC 262
#implementation of breadth first search of a graph
#output is a array containing the parent of each vertex in graph

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
def bfs_tree(g, s):
	# set discovered, processed and parent array
	processed = []
	discovered = []
	parent = []
	initializeSearch(g,processed,discovered,parent)

	q = queue.Queue(maxsize = 0)
	# place starting vertex in queue
	q.put(s)
	discovered[s] = True

	adjList = g.adjacency_list

	while(q.empty() == False):
		u = q.get()
		for tup in adjList[u]:
			v = tup[0]
			if discovered[v] == False:
				discovered[v] = True
				parent[v] = u

				q.put(v)
		processed[u] = True
	
	return parent
graph_string = """\
D 2
0 1
"""

print(bfs_tree(Graph(graph_string), 0))

graph_string = """\
D 2
0 1
1 0
"""

print(bfs_tree(Graph(graph_string), 1))



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

print(bfs_tree(Graph(graph_string), 1))







