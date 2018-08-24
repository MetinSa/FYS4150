import numpy as np 


def matrix_slow():

	n = 4
	A = np.zeros((n,n))			#making an empty 4x4 matrix

	np.fill_diagonal(A,-2)		#filling the main diagonal with -2

	for i in range(n-1):		#filling the secondary diagonals with 1
		A[i,i+1] = 1
		A[i+1,i] = 1

	return A


def matrix_by_vectors():

	n = 4