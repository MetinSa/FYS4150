import numpy as np 



def f(x):

	"""	
	The function f(x).

	"""

	return 100*np.exp(-10*x)


def analytical_sol(x):

	"""
	The closed-form solution to -u''(x) = f(x)

	"""

	return 1 - (1 - np.exp(-10))*x - np.exp(-10*x)



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
	#number of mesh points
	n = 4	

	#boundary conditions
	x_0 = 0;	x_n = 1	

	#steplength
	h = (x_n - x_0)/n	

	#making the x array, where x_i  = x0 + i*h
	x = np.zeros(n+1)	

	for i in range(0,n+1):
		x[i] = x_0 + i*h	
	


	#initializing the vectors and filling them 
	a = np.zeros(n);	a.fill(-1)
	b = np.zeros(n);	b.fill(2)
	c = np.zeros(n);	c.fill(-1)

	u = np.zeros(n)	

	f_tilde = np.zeros(n)
	for i in range(n):
		f_tilde[i] = h**2 * f(x[i])

	print (f_tilde)


matrix_fast()


