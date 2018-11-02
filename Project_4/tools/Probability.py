import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 

filename = sys.argv[1]

N, T, E, M, C_V, Chi, absM, accepted_states = np.loadtxt("../data/" + filename + ".dat", unpack = True)

weights = np.ones_like(E)/float(len(E))

n, bins, rectangles = plt.hist(E, 100, weights=weights, color = "royalblue")
plt.grid(linestyle = "--")
plt.xlabel("Energy")
plt.ylabel("Probability")
plt.show()