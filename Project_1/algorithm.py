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
	a = np.zeros(n);	a.fill(-1)
	b = np.zeros(n);	b.fill(2)
	c = np.zeros(n);	c.fill(-1)

	return a, b, c



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
	

	#initializing the f_tilde and v vectors
	f_tilde = np.zeros(n)
	v = np.zeros(n)

	#solving f_tilde = h^2 * f in addition to computing the analytic solution
	for i in range(n):
		f_tilde[i] = h**2 * f(x[i])
		v[i] = analytical_sol(x[i])


	#forward substitution

	a, b, c = matrix_fast(n)

	#making the gauselliminated new values
	a_tilde = np.zeros(n)
	b_tilde = np.zeros(n)
	c_tilde = np.zeros(n)


	# computing equation (1) and (2).  b_tilde == d_tilde and f_tilde = b_tilde in lecture notes but not in the project text 
	for i in range(n):
		b_tilde[i] = b[i] - (a[i-1]*c[i-1])/b[i-1]
		f_tilde[i] = f(x[i]) - (f_tilde[i-1]*c[i-1])/b[i-1]

	print (b_tilde)

algorithm(4)





