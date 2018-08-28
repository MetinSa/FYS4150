import numpy as np 
import matplotlib.pyplot as plt 

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
	e = np.zeros(n+2);	e.fill(-1)
	d = np.zeros(n+2);	d.fill(2)

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
	x = np.zeros(n+2)	

	for i in range(0,n+2):
		x[i] = x_0 + i*h	
	
	#initializing the b, b_tilde and u vectors
	b = np.zeros(n+2)
	b_tilde = np.zeros(n+2)
	solution = np.zeros(n+2)

	#solving b_tilde = h^2 * f in addition to computing the analytic solution
	for i in range(1, n+1):
		b[i] = h**2 * function(x[i])
		solution[i] = analytical_sol(x[i])


	#extracting the e and d diagonal matrix vectors
	e, d = matrix_fast(n)

	#making the gauselliminated new arrays for e and d
	e_tilde = np.zeros(n+2)
	d_tilde = np.zeros(n+2)


	"""
	Forward Substitution

	"""


	#starting by setting the initial conditions to avoid inf errors
	d_tilde[1] = d[1]
	b_tilde[1] = b[1]

	#computing equation (1) and (2) from the lecture notes
	for i in range(2,n+1):
		d_tilde[i] = d[i] - ((e[i-1]**2)/d_tilde[i-1])
		b_tilde[i] = b[i] - ((b_tilde[i-1]*e[i-1])/d_tilde[i-1])


	"""
	Backward Substitution

	"""


	#setting initial conditions (boundary)
	u = np.zeros(n+2)
	u[n] = b_tilde[n]/d_tilde[n]

	#computing equation (3) using a reversed for loop going from i = 8 to i = 0
	for i in range(n-1,0,-1):
		u[i] = (b_tilde[i] - e[i]*u[i+1])/d_tilde[i]


	return x, u, solution



def plot(n):

	"""
	Quick and dirty plot.

	"""

	#extracting the x, u and the analytic solution 
	x, u, solution = algorithm(n)

	#plotting
	plt.plot(x, solution, color = "black", label = "Exact Solution")
	plt.plot(x, u, color = "royalblue", label = "Computed")
	plt.grid(linestyle = "--")
	plt.legend()
	plt.xlabel("x")
	plt.ylabel("u(x)")
	plt.title("Numerically computed vs exact analytic solution")
	plt.savefig("pythonab.jpg")
	plt.show()


plot(10000)

