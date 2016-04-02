#Cecilia Villatoro
#COSC262
#fibonacci using divide and conquer

def multiplyMatrix(matrix1, matrix2):
	#print matrix1
	matrix3 = [0,0,0,0]
	matrix3[0] = (matrix1[0] * matrix2[0])  + (matrix1[1] * matrix2[2])
	matrix3[1] = (matrix1[0] * matrix2[1]) + (matrix1[1] * matrix2[3])
	matrix3[2] = (matrix1[2] * matrix2[0]) + (matrix1[3] * matrix2[2])
	matrix3[3] = (matrix1[2] * matrix2[1]) + (matrix1[3] * matrix2[3])
	return matrix3

def exp(matrix, n):
	if n == 0:
		return [1,0,0,1]
	else:
		#res = multiplyMatrix([1,1,1,0], exp(matrix, int(n/2)))
		res = exp(matrix, int(n/2))
		if n % 2 == 0:
			return multiplyMatrix(res ,res)
		else:
			return multiplyMatrix(multiplyMatrix(matrix, res), res)



def fib(n):
	matrix = exp([1,1,1,0], n)
	return matrix[1]

import math
print(math.floor(math.log10(fib(5*10**6))))	

	
