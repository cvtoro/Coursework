#Cecilia Villatoro
#COSC262
#returns a path from one vertex to another by checking parent array

def tree_path_aux(parents, start, end, result):
	if start == end or end == None:
		result.append(start)
	else:
		tree_path_aux(parents, start, parents[end],result)
		result.append(end)

def tree_path(parents,start,end):
	result = []
	tree_path_aux(parents, start, end, result)
	return result

print(tree_path([None, 0], 0, 1))
print(tree_path([None, 2, 3, None, 3, 4], 3, 5))
print(tree_path([None, 0, 1, 2, 3], 0, 4))
print(tree_path([5, 2, None, 1, 1, 4], 2, 0))