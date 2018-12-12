import numpy as np
import sys as sys
import matplotlib.pyplot as plt
import os
from GammaDistribution import GammaDistribution
from matplotlib2tikz import save as tikz_save


savefile = None
if len(sys.argv) > 1:
	if sys.argv[1].endswith(".tex"):
		savefile = "../figures/" + sys.argv[1][:-4]
	else:
		savefile = "../figures/" + sys.argv[1]

# System information
path = "../data/former_transactions/"

filenames = []

for filename in os.listdir(path):
	if ".dat" in filename:

		filenames.append(filename)

filenames = sorted(filenames)
filenames_with_saving = filenames[:10]
filenames_without_saving = filenames[10:]


# Delta_m
delta_m = 0.03


gamma_list = [0, 1, 2, 3, 4]
color_list = ["royalblue", "darkorange", "mediumseagreen", "crimson", "violet"]


plt.figure()
# For alpha = 1 and lambda = 0

for i, files in enumerate(filenames_without_saving[:5]):
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


    # Plotting the wealth distribution and parametrized solution
    plt.plot(m, w_m, "-", color = color_list[i], label = r"$\gamma =$ %.2f" %gamma_list[i])
    plt.title(r'$\alpha = 1, \lambda = 0$')

plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Distribution of wealth $w_m$")
plt.legend()
if savefile:
	tikz_save(savefile + '1.tex', figureheight="\\figureheight", figurewidth="0.45\\linewidth")



plt.figure()
# For alpha = 2 and lambda = 0

for i, files in enumerate(filenames_without_saving[5:]):
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

    # Plotting the wealth distribution and parametrized solution
    plt.plot(m, w_m, "-", color = color_list[i], label = r"$\gamma =$ %.2f" %gamma_list[i])
    plt.title(r'$\alpha = 2, \lambda = 0$')

plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Distribution of wealth $w_m$")
plt.legend()
if savefile:
	tikz_save(savefile + '2.tex', figureheight="\\figureheight", figurewidth="0.45\\linewidth")





plt.figure()
# For alpha = 1 and lambda = 0.3

for i, files in enumerate(filenames_with_saving[:5]):
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

    # Plotting the wealth distribution and parametrized solution
    plt.plot(m, w_m, "-", color = color_list[i], label = r"$\gamma =$ %.2f" %gamma_list[i])
    plt.title(r'$\alpha = 1, \lambda = 0.3$')

plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Distribution of wealth $w_m$")
plt.legend()
if savefile:
	tikz_save(savefile + "1_with_saving.tex", figureheight="\\figureheight", figurewidth="0.45\\linewidth")


plt.figure()
# For alpha = 2 and lambda = 0

for i, files in enumerate(filenames_with_saving[5:]):
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

    # Plotting the wealth distribution and parametrized solution
    plt.plot(m, w_m, "-", color = color_list[i], label = r"$\gamma =$ %.2f" %gamma_list[i])
    plt.title(r'$\alpha = 2, \lambda = 0.3$')

plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Distribution of wealth $w_m$")
plt.legend()
if savefile:
	tikz_save(savefile + "2_with_saving.tex", figureheight="\\figureheight", figurewidth="0.45\\linewidth")
plt.show()
