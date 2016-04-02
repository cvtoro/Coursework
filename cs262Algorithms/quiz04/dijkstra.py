#Cecilia Villatoro
#COSC 262 Algorithms
#implementation of dijstra's algorithm which finds shortest path 
#from one vertex to every other vertex in a graph

class Graph:

	
	def processString(self, graph_string):
		result = [None, None, None, None]
		
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
		self.numVertices = result[3]
		


#add the shortest path from s to some vertex. Will be guaranteed to be the shortest
def dijkstra(graph, start):
	gNumVertices = int(graph.numVertices)
	parentArray = [None] * gNumVertices

	distance = [None] * gNumVertices
	inTree = [None] * gNumVertices
	maxInt = float("inf")
	for i in range(gNumVertices):
		inTree[i] = False
		distance[i] = maxInt
	v = start	
	distance[start] = 0

	while(not inTree[v]):
		inTree[v] = True
	
		adjList = graph.adjacency_list[v]
		for tup in adjList:
			u = tup[0]
			weight = tup[1]
			#update if found a lesser distance from starting vertex to this vertex
			if distance[u] > (distance[v] + weight):
				distance[u] = distance[v] + weight
				parentArray[u] = v
		dist = float("inf")
		for i in range(gNumVertices):
			# find a new vertex to add to tree, smallest weight thats connected to current tree
			if inTree[i] == False and distance[i] < dist:
				dist = distance[i]
				v = i
	return (parentArray, distance)

#testing


graph_str = """\
D W 3
0 1 1
1 2 2
2 0 4
"""

print(dijkstra(Graph(graph_str), 0))
print(dijkstra(Graph(graph_str), 1))
print(dijkstra(Graph(graph_str), 2))

graph_str = """\
U W 7
0 1 5
0 2 7
0 3 12
1 2 9
2 3 4
1 4 7
2 4 4
2 5 3
3 5 7
4 5 2
4 6 5
5 6 2
"""

print(dijkstra(Graph(graph_str), 0))

