#Cecilia Villatoro
#COSC262

#implementation of merge sort algorithm
def merge_sort(list):
	if len(list) < 2:
		return list
	else:
		middle = len(list) / 2 
		left = merge_sort(list[:middle])
		right = merge_sort(list[middle:])
		return merge(left, right)

def merge(left, right):
	
	result = []
	lenLeft = len(left) 

	lenRight = len(right) 
	j = 0
	k = 0
	while j < lenLeft and k < lenRight:

		if left[j] <= right[k]:
			result.append(left[j])
			j+=1
		else:
			result.append(right[k])
			k+=1
		
	while(j < lenLeft):
		result.append(left[j])
		j+=1
		
	while(k < lenRight):
		result.append(right[k])
		k+=1
	

	return result





#recursive max helper function
def findMax(list):
	if len(list) < 2:
		return list[0]
	middle = int( len(list) / 2)

	max1 = findMax(list[:middle])
	max2 = findMax(list[middle:])
	if max1 >= max2:
		return max1
	else:
		return max2

#find max of an array using divide and conquer
def recursive_max(seq, key = None):
	if key == None:
			return findMax(seq)
	else:
		keyList = list(map(key, seq))
		max = findMax(keyList)
		return seq[keyList.index(max)]

#testing
print(recursive_max(range(-5, 5 + 1)))


print(recursive_max(range(-5, 5 + 1), lambda x: x * x))

class PoliticalDivision:
    def __init__(self, name, area):
        self.name = name
        self.area = area

divisions = [
    PoliticalDivision("Brazil", 8.5),
    PoliticalDivision("China", 9.5),
    PoliticalDivision("New Zealand", 0.27),
    PoliticalDivision("Russia", 17),
    PoliticalDivision("UK", 0.24),
    PoliticalDivision("US", 9.5),
]
             
print(recursive_max(divisions, lambda division: division.area).name)

#helper function for find_pit
def findMin(right, middle, left):
	if middle < right and middle < left:
		return middle
	elif right <= middle and right <= left:
		return right
	else: return left

def find_pit(seq):
	middle = len(seq) / 2 
	right = middle + 1
	left = middle - 1
	#left side and right side exist
	
	if len(seq) == 1:
		return 
	if right <= len(seq) - 1 and left >= 0:
			print(middle)
			minimum = min(seq[right], seq[middle], seq[left])
			if minimum  == seq[middle]:
				return middle
			elif (minimum  == seq[right]):

				find_pit(seq[middle+1:])
			else:
				find_pit(seq[:middle])
	#first edge case
	if middle == 0:
		print(seq[right]) 
		if seq[middle] < seq[right]:
			return middle
		else: 
			return find_pit(seq[middle+1:]) 
	#second edge case
	if middle == len(seq) - 1:
		print(middle)
		if seq[middle] < seq[left]:
			return middle
		else:
			return find_pit(seq[:middle])

# print(find_pit([5, 4, 5]))
# print(find_pit([10]))
# print(find_pit([10, 7, 5, 4]))	








		












