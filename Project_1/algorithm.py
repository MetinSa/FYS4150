import numpy as np 

def function(x):

	"""	
	The function f(x).

	"""

	return 100*np.exp(-10*x)


def analytical_sol(x):

	"""
	The closed-form solution to -u''(x) = f(x)

	"""

	return 1 - (1 - np.exp(-10))*x - np.exp(-10*x)



def matrix_slow(n):

	"""
	Making the specific 4x4 matrix the slow way.

	"""

	A = np.zeros((n,n))			#making an empty 4x4 matrix

	np.fill_diagonal(A,-2)		#filling the main diagonal with -2

	for i in range(n-1):		#filling the secondary diagonals with 1
		A[i,i+1] = 1
		A[i+1,i] = 1

	return A


def matrix_fast(n):	

	"""
	Making the specific vectors in the 4x4 matrix instead of creating the whole 
	matrix. 	

	"""

	#initializing the vectors and filling them 
	e = np.zeros(n);	e.fill(-1)
	d = np.zeros(n);	d.fill(2)

	return e, d



def algorithm(n):

	"""
	Making the algorithm which solves the differential equation u''(x) = f(x) 
	using linear algebra. 

	"""


	#boundary conditions
	x_0 = 0;	x_n = 1	

	#steplength
	h = (x_n - x_0)/n	

	#making the x array, where x_i  = x0 + i*h
	x = np.zeros(n+1)	

	for i in range(0,n+1):
		x[i] = x_0 + i*h	
	

	#initializing the b, b_tilde and u vectors
	b = np.zeros(n)
	b_tilde = np.zeros(n)
	u = np.zeros(n)

	#solving b_tilde = h^2 * f in addition to computing the analytic solution
	for i in range(1, n):
		b[i] = h**2 * function(x[i])
		u[i] = analytical_sol(x[i])


	#extracting the e and d diagonal matrix vectors
	e, d = matrix_fast(n)

	#making the gauselliminated new arrays for e and d
	e_tilde = np.zeros(n)
	d_tilde = np.zeros(n)

	#Forward Substition

	#starting by setting the initial conditions to avoid inf errors
	d_tilde[0] = d[0]
	b_tilde[0] = function(x[0])

	#computing equation (1) and (2) fromt the lecture notes
	for i in range(1,n):
		d_tilde[i] = d[i] - (e[i-1]**2)/d_tilde[i-1]
		b_tilde[i] = function(x[i]) - (b_tilde[i-1]*e[i-1])/d_tilde[i-1]





algorithm(10)





