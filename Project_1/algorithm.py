import numpy as np 


def matrix_slow():

	"""
	Making the specific 4x4 matrix the slow way.

	"""

	n = 4
	A = np.zeros((n,n))			#making an empty 4x4 matrix

	np.fill_diagonal(A,-2)		#filling the main diagonal with -2

	for i in range(n-1):		#filling the secondary diagonals with 1
		A[i,i+1] = 1
		A[i+1,i] = 1

	return A


def matrix_fast():

	"""
	Making the specific 4x4 matrix the fast way using vectors. 

	"""

	n = 4

	d = np.zeros(n)				#initializing the d-vector 
	e = np.zeros(n-1)			#initializing the e-vector 

	d.fill(2)
	e.fill(-1)

	return e

d = matrix_fast()
print (d)








