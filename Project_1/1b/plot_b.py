import matplotlib.pyplot as plt 
import numpy as np 
import sys

#reading in the name of the file and opening it
name = str(sys.argv[1])
file = open(name, "r")

#extracting number of grid points
n = int(file.readline())

# defining x, y, v arrays
x = np.zeros(n+1)
u = np.zeros(n+1)
v = np.zeros(n+1)

#dummy index
j = 0

#iterating over the different lines in the file
for i, line in enumerate(file):

	#skipping the first line
	if i > 1:
		
		x[j] = line.split()[0]
		u[j] = line.split()[1]
		v[j] = line.split()[2]
		j += 1

# plotting
plt.plot(x, v, color = "black", label = "Analytic Solution")
plt.plot(x, u, color = "royalblue", label = "Numerical Solution")
plt.grid(linestyle = "--")
plt.legend()
plt.xlabel("$x$")
plt.ylabel("$u(x)$")
plt.title("Gridpoints: n = %g" %n)
plt.savefig("fig_"+str(n)+"_b.pdf")
plt.show()




