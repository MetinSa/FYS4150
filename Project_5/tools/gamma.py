import numpy as np
import sys as sys
import matplotlib.pyplot as plt
import os
from GammaDistribution import GammaDistribution


# System information
path = "../data/lambdas/"

filenames = []

for filename in os.listdir(path):
	if ".dat" in filename:

		filenames.append(filename)

filenames = sorted(filenames)


# Delta_m
delta_m = 0.03


lmbda_list = [0, 0.25, 0.5, 0.9]
color_list = ["royalblue", "darkorange", "mediumseagreen", "crimson", "violet"]
for i, files in enumerate(filenames):
    # Reading file
    WealthDistribution = np.loadtxt(path + files, unpack = True)

    # Initial wealth
    m_0 = np.average(WealthDistribution)

    # Number of bins
    N_bins = (int(N*delta_m))

    # Making the initial histogram
    w_m, bins = np.histogram(WealthDistribution, N_bins, density = True)

    # Finding the bin centers and converting to m array
    m = 0.5*(bins[1:] + bins[:-1])

    m_dist = np.linspace(np.min(WealthDistribution), np.max(WealthDistribution), 1000)

    # Plotting the wealth distribution
    #n, bins, patches = plt.hist(WealthDistribution, 50, color = "royalblue", edgecolor = "black", normed=True)
    plt.plot(m, w_m, "o", color = color_list[i], label = r"$\lambda =$ %.2f" %lmbda_list[i])
    plt.plot(m_dist, GammaDistribution(m_0, m_dist, lmbda_list[i])/100, color = color_list[i])

#plt.axis([np.min(WealthDistribution), np.max(WealthDistribution), 1e-3, 1])
plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Distribution of wealth $w_m$")
plt.legend()

plt.show()
