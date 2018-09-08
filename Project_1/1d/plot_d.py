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

#iterating over the different lines in the file
for i, line in enumerate(file):
		
		n[i] = line.split()[0]
		eps[i] = line.split()[1]

# plotting
plt.loglog(n, 10**eps, color = "royalblue", label = "Best Fit")
plt.loglog(n, 10**eps, "x",markersize = 7, color = "black", label = "Data Points")
plt.grid(linestyle = "--")
plt.legend()
plt.xlabel("$n$")
plt.ylabel(r"Max$[\epsilon(n)]$")
plt.title("Maximum Relative Error")
plt.savefig("rel_error_plot.pdf")
plt.show()




