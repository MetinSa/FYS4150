import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 
import os 

filenames = []

for filename in os.listdir("../data/AcceptedStates/"):
	if ".dat" in filename:
		filenames.append(filename)

filenames = sorted(filenames)

for file in filenames:
	N, T, E, M, C_V, Chi, absM, accepted_states = np.loadtxt("../data/AcceptedStates/" + file, unpack = True)
	plt.plot(N,accepted_states, label = "T = %.1f K" %T[1])


plt.legend()
plt.ylabel("Accepted States")
plt.xlabel("Monte-Carlo Cycles")
plt.grid(linestyle = "--")
# plt.savefig("../figures/" + filename + "_" + quantity + ".png")
plt.show()