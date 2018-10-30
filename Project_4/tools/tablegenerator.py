import numpy as np 
import sys as sys 

filename = sys.argv[1]

# N, T, E, M, C_V, Chi, absM, accepted_states = np.loadtxt("../data/" + filename + ".dat", unpack = True)
A = np.loadtxt("../data/" + filename + ".dat", unpack = True)

np.savetxt("../data/" + filename + ".csv", A)