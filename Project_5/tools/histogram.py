import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 

path = "../data/"
filename = sys.argv[1]

agents = np.loadtxt(path + filename + ".dat", unpack = True)

# weights = np.ones_like(agents)/len(agents)

n, bins, patches = plt.hist(agents,50, color = "royalblue", edgecolor = "black")
plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Number of agents with wealth $m$")
plt.show()