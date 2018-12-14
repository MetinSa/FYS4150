import numpy as np
import sys as sys
import matplotlib.pyplot as plt
import os
from GammaDistribution import GammaDistribution
from matplotlib2tikz import save as tikz_save
from sklearn.linear_model import LinearRegression as OLS



savefile = None
if len(sys.argv) > 1:
	if sys.argv[1].endswith(".tex"):
		savefile = "../figures/" + sys.argv[1][:-4]
	else:
		savefile = "../figures/" + sys.argv[1]

# System information
path = "../data/"


# Delta_m
delta_m = 0.03


alpha = ["0.5", "1", "1.5", "2"]
color_list = ["red", "blue", "purple", "black"]

files = ["lambda_0_alpha_%s.dat" %i for i in alpha]

# For alpha = 1 and lambda = 0
for i, file in enumerate(files):
    # Reading file
    WealthDistribution = np.loadtxt(path + file, unpack = True)

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
    plt.loglog(m, w_m, "-", color = color_list[i], label = r"$\alpha =$ %.2f" %float(alpha[i]))

plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Distribution of wealth $w_m$")
plt.legend()
if savefile:
    tikz_save(savefile + 'distribution_NN.tex', figureheight="\\figureheight", figurewidth="\\figurewidth")

plt.figure()

for i, file in enumerate(files):
    # Reading file
    WealthDistribution = np.loadtxt(path + file, unpack = True)

    # Initial wealth
    m_0 = np.average(WealthDistribution)
    N = len(WealthDistribution)

    # Number of bins
    N_bins = (int(N*delta_m))

    # Making the initial histogram
    w_m, bins = np.histogram(WealthDistribution, N_bins, density = True)

    # Finding the bin centers and converting to m array
    m = 0.5*(bins[1:] + bins[:-1])
    w_m = w_m[m > 600]
    m = m[m>600]

    model = OLS(fit_intercept = True)
    model.fit(np.c_[m**(-1-float(alpha[i]))], w_m)

    m_ = np.linspace(min(m), max(m), 1000)

    # Plotting the wealth distribution and parametrized solution
    plt.loglog(m, w_m, "-", color = color_list[i], label = r"$\alpha =$ %.2f" %float(alpha[i]))
    plt.loglog(m_, model.predict(np.c_[m_**(-1-float(alpha[i]))]), "--", color = color_list[i])

plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Distribution of wealth $w_m$")
plt.ylim(bottom=1e-5)
plt.xlim(right=1400)
plt.legend()
if savefile:
	tikz_save(savefile + 'tail_distribution_NN.tex', figureheight="\\figureheight", figurewidth="\\figurewidth")


files = ["lambda_0.3_alpha_%s.dat" %i for i in alpha]

plt.figure()
# For alpha = 1 and lambda = 0
for i, file in enumerate(files):
    # Reading file
    WealthDistribution = np.loadtxt(path + file, unpack = True)

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
    plt.loglog(m, w_m, "-", color = color_list[i], label = r"$\alpha =$ %.2f" %float(alpha[i]))

plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Distribution of wealth $w_m$")
plt.legend()
if savefile:
    tikz_save(savefile + 'distribution_NN_lambda.tex', figureheight="\\figureheight", figurewidth="\\figurewidth")

plt.figure()


for i, file in enumerate(files):
    # Reading file
    WealthDistribution = np.loadtxt(path + file, unpack = True)

    # Initial wealth
    m_0 = np.average(WealthDistribution)
    N = len(WealthDistribution)

    # Number of bins
    N_bins = (int(N*delta_m))

    # Making the initial histogram
    w_m, bins = np.histogram(WealthDistribution, N_bins, density = True)

    # Finding the bin centers and converting to m array
    m = 0.5*(bins[1:] + bins[:-1])
    if float(alpha[i]) == 0.5:
        w_m = w_m[m > 400]
        m = m[m>400]
    else:
        w_m = w_m[m > 500]
        m = m[m>500]

    model = OLS(fit_intercept = True)
    model.fit(np.c_[m**(-1-float(alpha[i]))], w_m)

    m_ = np.linspace(min(m), max(m), 1000)

    # Plotting the wealth distribution and parametrized solution
    plt.loglog(m, w_m, "-", color = color_list[i], label = r"$\alpha =$ %.2f" %float(alpha[i]))
    plt.loglog(m_, model.predict(np.c_[m_**(-1-float(alpha[i]))]), "--", color = color_list[i])

plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Distribution of wealth $w_m$")
plt.ylim(bottom=1e-5)
plt.xlim(right=1400)
plt.legend()
if savefile:
    tikz_save(savefile + 'tail_distribution_NN_lambda.tex', figureheight="\\figureheight", figurewidth="\\figurewidth")

plt.show()
