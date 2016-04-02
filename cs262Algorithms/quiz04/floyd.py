#Cecilia Villatoro
#COSC 262 Algorithms
#implementation of floyds algorithm to find the shortest paths between all vertices

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
		
#adjacency matrix contains weights between vertices
class adjacencyMatrix:			
	def __init__(self, graph):
		maxInt = float("inf")
		numVertices = int(graph.numVertices)
		matrix = [None] * numVertices
		for i in range(numVertices):
			matrix[i] = [maxInt] * numVertices
			adjList = graph.adjacency_list[i]
			for tup in adjList:
				j = tup[0]
				weight = tup[1]
				matrix[i][j] = weight
			matrix[i][i] = 0
		self.matrix = matrix

def floyd(graph):
	adjMatrix = adjacencyMatrix(graph).matrix
	numVertices = int(graph.numVertices)
	
	for k in range(numVertices):
		for i in range(numVertices):
			for j in range(numVertices):
				currWeight = adjMatrix[i][j]
				through_k = adjMatrix[i][k] + adjMatrix[k][j]
				if through_k < currWeight:
					adjMatrix[i][j] = through_k
	return adjMatrix


#testing
graph_str = """\
D W 3
0 1 1
1 2 2
2 0 4
"""

print(floyd(Graph(graph_str)))

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

print(floyd(Graph(graph_str)))