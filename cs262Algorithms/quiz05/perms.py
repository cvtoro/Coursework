#Cecilia Villatoro
#COSC 262 Algorithms
#find all permutations of a set s using 

def perms(s):
	solutions = []
	sol = []
	backtrack_dfs(s, 0, solutions, sol)
	return solutions

def createCandidates(s, sol):
	# remove all elents in the set which are in the solution space, s - sol
	return [item for item in s if item not in sol]


#use depth first search to enumerate through all possible permutations
def backtrack_dfs(s, k,  solutions, sol):
	if k == len(s) :
		if(len(sol) == len(s)):
			tup = ()
			lengthSol =len(sol)
			for i in range(lengthSol):
				tup += (sol.pop(),)
			solutions.append(tup)
		return
	else:
	
		for candidate in createCandidates(s, sol):
			sol.append(candidate)
			backtrack_dfs(s, k+1, solutions, sol)
			# sol.remove(candidate)
		


print(sorted(perms({1,2})))
print(sorted(perms({'a'})))

permutations = perms(set())
print(len(permutations) == 0 or list(permutations) == [()])

print(len(list(perms(set('abc')))))
print(perms(set('abc')))

print(set('abc'))
    

        