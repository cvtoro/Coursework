#Cecilia Villatoro
#COSC62

#divide recursively
def recursive_divide(x,y):
	if (x-y) < 0 :
		return 0
	else:
		return 1 + recursive_divide((x - y), y)

print("recursive_divide testing:")
print(recursive_divide(8, 3))
print(recursive_divide(9, 3))
print(recursive_divide(5, 10))
print(recursive_divide(0, 2))

cycleLengthDict = dict()


def cycle_length(n):
	if n in cycleLengthDict:
		return cycleLengthDict[n]
	elif n == 1:
		return 1
	else:
		if(n % 2 == 0):
			cycleLength = 1 + cycle_length((n/2))
			cycleLengthDict[n] = cycleLength
			return cycleLength
		else:
			cycleLength = 1 + cycle_length(3*n + 1) 
			cycleLengthDict[n] = cycleLength
			return cycleLength

print("cycle_length testing:")
print(cycle_length(22))
print(cycle_length(1))
for n in range(1,11):
    print(cycle_length(n))


def max_length(i, j):
	maxNumber = i
	maxLength = 0
	for k in range(i, j+1):
		currCycleLength = cycle_length(k)
		if currCycleLength ==  maxLength and k < maxNumber:
			maxNumber = k
		if currCycleLength > maxLength:
			maxLength = currCycleLength
			maxNumber = k
	return (maxNumber, maxLength)
print("testing max_length:")
print(max_length(1, 100))
print(max_length(101, 200))
print(max_length(201, 300))
print(max_length(301, 400))
print(max_length(401, 500))
print(max_length(1, 10**6))

			
