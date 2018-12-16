import numpy as np
import sys as sys
import matplotlib.pyplot as plt
import os
from GammaDistribution import GammaDistribution
from matplotlib2tikz import save as tikz_save


savefile = None
if len(sys.argv) > 1:
	if sys.argv[1].endswith(".tex"):
		savefile = "../figures/" + sys.argv[1]
	else:
		savefile = "../figures/" + sys.argv[1] + ".tex"

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
    N = len(WealthDistribution)

    # Number of bins
    N_bins = (int(N*delta_m))

    # Making the initial histogram
    w_m, bins = np.histogram(WealthDistribution, N_bins, density = True)

    # Finding the bin centers and converting to m array
    m = 0.5*(bins[1:] + bins[:-1])

    m_dist = np.linspace(np.min(WealthDistribution)/10, np.max(WealthDistribution)*10, 1000)

    # Plotting the wealth distribution and parametrized solution
    plt.loglog(m, w_m, "o", color = color_list[i], markersize=3, label = r"$\lambda =$ %.2f" %lmbda_list[i])
    plt.loglog(m_dist, GammaDistribution(m_0, m_dist, lmbda_list[i])/100, color = color_list[i])

#plt.xlim([0,300])
plt.axis([1e1, 1.5e3, 1e-6, 1])
plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Distribution of wealth $w_m$")
plt.legend()
if savefile:
	tikz_save(savefile, figureheight="\\figureheight", figurewidth="\\figurewidth")
plt.show()




i = 0
# Reading file
WealthDistribution = np.loadtxt(path + filenames[i], unpack = True)

# Initial wealth
m_0 = np.average(WealthDistribution)
N = len(WealthDistribution)

# Number of bins
N_bins = (int(N*delta_m))

# Making the initial histogram
w_m, bins = np.histogram(WealthDistribution, N_bins, density = True)

# Finding the bin centers and converting to m array
m = 0.5*(bins[1:] + bins[:-1])

m_dist = np.linspace(np.min(WealthDistribution)/10, np.max(WealthDistribution)*10, 1000)

# Plotting the wealth distribution and parametrized solution
plt.loglog(m, w_m, 'o', color = color_list[0], markersize=3, label = '_nolegend_')
plt.loglog(m, 1.3e4*m**(-1-2), linestyle = '--', color = color_list[1], label=r'Pareto $w_m \propto m^{-3}$')
plt.loglog(m, 5e2*m**(-1-1.5), linestyle = '--', color = color_list[2], label=r'Pareto $w_m \propto m^{-2.5}$')

plt.axis([2e2, 7e2, 5e-5, 1e-3])
plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Distribution of wealth $w_m$")
plt.legend()
if savefile:
	tikz_save(savefile[:-3] + '_tail_0.tex', figureheight="\\figureheight", figurewidth="\\figurewidth")
plt.show()



i = 2
# Reading file
WealthDistribution = np.loadtxt(path + filenames[i], unpack = True)

# Initial wealth
m_0 = np.average(WealthDistribution)
N = len(WealthDistribution)

# Number of bins
N_bins = (int(N*delta_m))

# Making the initial histogram
w_m, bins = np.histogram(WealthDistribution, N_bins, density = True)

# Finding the bin centers and converting to m array
m = 0.5*(bins[1:] + bins[:-1])

m_dist = np.linspace(np.min(WealthDistribution)/10, np.max(WealthDistribution)*10, 1000)

# Plotting the wealth distribution and parametrized solution
plt.loglog(m, w_m, 'o', color = color_list[0], markersize=3, label = '_nolegend_')
plt.loglog(m, 4e3*m**(-1-2), linestyle = '--', color = color_list[1], label=r'Pareto, $w_m \propto m^{-3}$')
plt.loglog(m, 3e8*m**(-1-4), linestyle = '--', color = color_list[2], label=r'Power law, $w_m\propto m^{-5}$')

plt.axis([2e2, 3.5e2, 5e-5, 1e-3])
plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Distribution of wealth $w_m$")
plt.legend()
if savefile:
	tikz_save(savefile[:-4] + '_tail_0_5.tex', figureheight="\\figureheight", figurewidth="\\figurewidth")
plt.show()
