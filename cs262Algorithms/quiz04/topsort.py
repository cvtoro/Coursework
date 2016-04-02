#Cecilia Villatoro
#COSC 262 Algorithms
#implementation of producing a topological sorting of a graph

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
		self.numVertices = result[3]

def recursive_step(graph, vertex, stack, discovered):
	discovered[vertex] = True
	childrenList = graph.adjacency_list[vertex]
	
	
	for tup in childrenList:
		child = tup[0]
		if not discovered[child]:
			# discovered[child] = True
			recursive_step(graph, child, stack, discovered)
	stack.append(vertex)
	# print (stack)

#add children before adding a parent node to stack
#reveresed stack is a topological ordering
def topsort(graph):
	
	discovered = [False] * int(graph.numVertices)
	
	stack = [] 
	while False in discovered:
		vertex = discovered.index(False)
		recursive_step(graph, vertex, stack, discovered)
	#reverse stack and return list
	stack.reverse()
	return stack

	
graph_str = """\
D 2
0 1
"""

print(topsort(Graph(graph_str)))

graph_str = """\
D 3
1 2
"""

print(topsort(Graph(graph_str)) in [[0, 1, 2],
                                    [1, 0, 2],
                                    [1, 2, 0]])

# example from the textbook - fig 5.15
graph_str = """\
D 7
6 0
6 5
0 1
0 2
1 2
1 3
2 4
2 5
4 3
5 4
"""
print(topsort(Graph(graph_str)))

	
