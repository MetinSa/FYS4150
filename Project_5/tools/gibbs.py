import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 
from matplotlib import rc
from GibbsDistribution import GibbsDistribution

# System information
path = "../data/"
filename = sys.argv[1]

# Reading file
WealthDistribution = np.loadtxt(path + filename + ".dat", unpack = True)

# Initial wealth
m_0 = 100
N = len(WealthDistribution)

# Delta_m 
delta_m = 0.05

# Number of bins 
N_bins = (int(N*delta_m))

# Making the initial histogram
w_m, bins = np.histogram(WealthDistribution, N_bins)

# Finding the bin centers and converting to m array
m = 0.5*(bins[1:] + bins[:-1])


# Plotting the wealth distribution
plt.rc('text', usetex=True)
plt.rc('font', family='serif')
plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Distribution of wealth $w_m$")
# print (len(m))
plt.plot(m,w_m/N, color = "royalblue")

# Gibbs comparison
m_gibbs = np.linspace(np.amin(WealthDistribution), np.amax(WealthDistribution),N)
w_gibbs = GibbsDistribution(m_0,m_gibbs)
plt.plot(m_gibbs,w_gibbs*10)
plt.show()

