import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 
import os 
from cycler import cycler

plt.figure(figsize=(5,5))
default_cycler = (cycler(color=['mediumseagreen', 'orange','crimson', 'royalblue']))
plt.rc('axes', prop_cycle=default_cycler)

filenames = []

for filename in os.listdir("../../data/L20/"):
	if ".dat" in filename:
		filenames.append(filename)

filenames = sorted(filenames)

for file in filenames:
	N, T, E, M, C_V, Chi, absM, accepted_states = np.loadtxt("../../data/L20/" + file, unpack = True)
	if "oriented" in file:
		label = "Oriented, T' = %.1f K" %T[1]
	else:
		label = "Random, T' = %.1f K" %T[1]
	plt.scatter(N,accepted_states, label = label, alpha = 0.5)

plt.legend()
plt.yscale("log")
plt.xscale("log")
plt.ylabel("Accepted States")
plt.xlabel("Monte Carlo Cycles")
plt.grid(linestyle = "--")
plt.savefig("../../figures/L20/AcceptedStates.pdf")
plt.show()