#Cecilia Villatoro
#COSC262

def key_positions(seq, key, d):
	# keySeq =list(map(key,seq))
	keySeq = []
	for e in seq:
		keySeq.append(int(key(e, d)) )
	
	c = []
	maxKey =  int(max(keySeq))
	# print(keySeq)
	# zero out c
	for i in range(maxKey + 1):
		c.append(0)
	for key in keySeq:
		c[key] += 1
	sum = 0
	for i in range(len(c)):
		val = c[i]
		c[i] = sum
		sum += val
	return c


def sorted_array(seq, key, d, positions):
	b = [0] * len(seq)
	for e in seq:
		b[positions[int(key(e, d) )]] = e
		positions[int(key(e, d) )] += 1
	return b

def nDigit(number, d):
	
	for i in range(d):
		number = number / 10
	return number % 10 


def radix_sort(numbers, d):

	for i in range(d):
		numbers = sorted_array(numbers, nDigit , i, key_positions(numbers, nDigit, i ))
		
	return numbers

print (radix_sort([329, 457, 657, 839, 436, 720, 355], 3))


print(radix_sort([329, 457, 657, 839, 436, 720, 355], 1))

print(radix_sort([329, 457, 657, 839, 436, 720, 355], 2))

print(radix_sort([329, 457, 657, 839, 436, 720, 355], 3))

# print(sorted_array([3, 1, 2], lambda x: x, [0, 0, 1, 2]))

# print(sorted_array([3, 2, 2, 1, 2], lambda x: x, [0, 0, 1, 4]))
# print(sorted_array([100], lambda x: x, [0]*101))


# print(key_positions([0, 1, 2], lambda x: x))

# print(key_positions([2, 1, 0], lambda x: x))

# print(key_positions([1, 2, 3, 2], lambda x: x))

# print(key_positions([5], lambda x: x))

# print(key_positions(range(-3,3), lambda x: x**2))

# print(key_positions(range(1000), lambda x: 4))	

# print(key_positions([1] + [0] * 100, lambda x: x))