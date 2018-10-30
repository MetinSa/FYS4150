import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 

filename = sys.argv[1]

N, T, E, M, C_V, Chi, absM, accepted_states = np.loadtxt("../data/" + filename + ".dat", unpack = True)

plt.plot(N,M)
plt.show()