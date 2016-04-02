#Cecilia Villatoro
#COSC 262 Algorithms

#program to produce all subsets of a set
#uses a bit mask to produce all permutaions of 0 and 1 of length s, where s is the length of the set

def subsets(s):
    solutions = []
    items = list(s)
    A = [None] * len(items)
    k = 0
    backtrack_dfs(A, k, items, solutions)
    return solutions


def backtrack_dfs(boolean_list, k, items, solutions):
    if k == len(items):
        process_solution(boolean_list, items, solutions)
    else:
        for c in make_candidates(boolean_list, items):
            boolean_list[k] = c
            backtrack_dfs(boolean_list, k+1, items, solutions)

            
def process_solution(boolean_vector, items, solutions):
    solution = set()
    for i, b in enumerate(boolean_vector):
        if b:
            solution.add(items[i])
    solutions.append(solution)

    
def make_candidates(boolean_list, items):
    return [False, True]
        
