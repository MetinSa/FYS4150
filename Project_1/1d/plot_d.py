import matplotlib.pyplot as plt 
import numpy as np 
import sys
import scipy as scipy

#reading in the name of the file and opening it
name = str(sys.argv[1])
file = open(name, "r")

# defining h and eps arrays
length = 7
n = np.zeros(length)
eps = np.zeros(length)

#dummy index
j = 0

#iterating over the different lines in the file
for i, line in enumerate(file):

	#skipping the first line
	if i > 1:
		
		n[j] = line.split()[0]
		eps[j] = line.split()[1]
		j += 1

# plotting
plt.plot()
plt.loglog(n, 10**eps, color = "royalblue", label = "Best Fit")
plt.loglog(n, 10**eps, "x",markersize = 7, color = "black", label = "Data Points")
plt.grid(linestyle = "--")
plt.legend()
plt.xlabel("$n$")
plt.ylabel(r"$\epsilon(n)$")
plt.title("Maximum relative error for varying grid points")
plt.savefig("rel_error_plot.png")
plt.show()




