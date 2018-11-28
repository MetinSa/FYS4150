import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 
from matplotlib import rc

# System information
path = "../data/"
filename = sys.argv[1]

# Reading file
agents = np.loadtxt(path + filename + ".dat", unpack = True)

# Plotting the histogram
plt.rc('text', usetex=True)
plt.rc('font', family='serif')

# Making the histogram using numpy
n, bins, patches = plt.hist(agents, 50, color = "royalblue", edgecolor = "black")

plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Distribution of wealth $w_m$")
plt.show()