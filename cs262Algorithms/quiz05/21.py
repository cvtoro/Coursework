#Cecilia Villatoro
#COSC 262 Algorithms

#find all subsequences in a sequence which produces the number 21
def twentyone(seq):
	solutions = []
	sol = []
	backtrack_dfs(seq, 0, solutions, sol)
	return solutions

#each number in the sequence can either be added to running sum or not
def createCandidates():
	return [True, False]


#use depth first search to enumerate through all possible permutations
def backtrack_dfs(seq, k, solutions, sol):
	#check if valid solution
	if sum(sol) == 21:
		temp = [] + sol
		solutions.append(temp)
		return
	#check for non valid solution
	if k > len(seq) -1 or sum(sol) > 21:
		return
	else:
		for candidate in createCandidates():
			if candidate:
				sol.append(seq[k])
			backtrack_dfs(seq, k+1 ,solutions, sol)
			if candidate:
				del sol[-1]

#testing
seq = [5, 6, 7, 10, 11]
print(sorted(twentyone(seq)))


seq = [1, 5, 6, 7, 10, 2, 11]

print(sorted(twentyone(seq)))


seq = [] # no answer obviously
print(sorted(twentyone(seq)))

seq = [11, 11]
print(sorted(twentyone(seq)))

seq = [10] + [22]*50 + [11]
print(sorted(twentyone(seq)))	

seq = [12, 40, 9]
print(sorted(twentyone(seq)))
