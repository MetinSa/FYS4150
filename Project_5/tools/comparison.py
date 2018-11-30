import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 
from matplotlib import rc
import os
# System information
path = "../data/alpha/"
# filename = sys.argv[1]

filenames = []

for filename in os.listdir(path):
	if ".dat" in filename:

		filenames.append(filename)

filenames = sorted(filenames)

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

# Initial wealth
m_0 = 100

# Delta_m 
delta_m = 0.03	
	

alpha_list = [0, 0.5, 1, 1.5, 2]
color_list = ["royalblue", "darkorange", "mediumseagreen", "crimson", "violet"]
for i, files in enumerate(filenames):

	# Reading file
	WealthDistribution = np.loadtxt(path + files, unpack = True)	

	# Initial wealth
	N = len(WealthDistribution)	

	# Number of bins 
	N_bins = (int(N*delta_m))

	# Making the initial histogram
	w_m, bins = np.histogram(WealthDistribution, N_bins)	

	# Finding the bin centers and converting to m array
	m = 0.5*(bins[1:] + bins[:-1])	
	

	# Plotting the wealth distribution
	plt.loglog(m,w_m/N, "o", color = color_list[i], label = r"$\alpha =$ %.1f"%alpha_list[i])	

plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Distribution of wealth $w_m$")
plt.legend()

plt.show()	

