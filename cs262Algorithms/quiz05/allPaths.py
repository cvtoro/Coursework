#Cecilia Villatoro
#COSC 262 Algorithms
#find allpaths from a source to a destination using backsearching

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

def allpaths(graph, source, destination):
	solutions = []
	sol = [source] 
	backtrack_dfs(graph, source, destination, 1, solutions, sol)
	return solutions

#return adjacent vertices
def createCandidates(graph, source, sol):

	res = []
	for tup in graph.adjacency_list[source]:
		res.append(tup[0])
	return res


#use depth first search to enumerate through all possible permutations
def backtrack_dfs(graph, source, destination, k,  solutions, sol):
	#invalid solution, found a cycle or seen all vertices
	#cycle is found if duplicated elements in sol
	if sol[-1] in sol[0:(len(sol) - 1)]: 
		return
	#found a valid solution
	if source == destination:
		temp = [] + sol
		solutions.append(temp)
		return
	else:
		for candidate in createCandidates(graph, source, sol):
			#add a candidate to temporary solution
			sol.append(candidate)
			backtrack_dfs(graph, candidate, destination, k+1, solutions, sol)
			#remove candidate from temp solution
			del sol[k]

#testing:

# triangle graph
graph_str = """\
U 3
0 1
1 2
2 0
"""

print(sorted(allpaths(Graph(graph_str), 0, 2)))

graph_str = """\
U 5
0 2
1 2
3 2
4 2
1 4
"""

print(sorted(allpaths(Graph(graph_str), 0, 1)))


from pprint import pprint

# graph in fig 5.15 of text book
# vertices 0 to 6 correspond to A to G
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

pprint(sorted(allpaths(Graph(graph_str), 6, 3)))

    