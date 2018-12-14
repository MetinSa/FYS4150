import numpy as np 
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression as OLS
from matplotlib2tikz import save as tikz_save


# System information
path = "../data/"
# filename = sys.argv[1]

# Initial wealth
m_0 = 100

# Delta_m 
delta_m = 0.03	
	

alpha_list = [0, 0.5, 1, 1.5, 2]
color_list = ["royalblue", "darkorange", "mediumseagreen", "crimson", "violet"]
# Reading file
WealthDistribution = np.loadtxt(path + "lambda_0.dat", unpack = True)	

# Initial wealth
N = len(WealthDistribution)	

# Number of bins 
N_bins = (int(N*delta_m))

# Making the initial histogram
w_m, bins = np.histogram(WealthDistribution, N_bins, density=True)

# Finding the bin centers and converting to m array
m = 0.5*(bins[1:] + bins[:-1])	

m_fit = m[w_m > 0][:-2]
w_fit = w_m[w_m > 0][:-2]

model = OLS(fit_intercept = False)


# Fitting the wealth distirbution to a Gibbs distribution
model.fit(np.c_[np.ones_like(m_fit), m_fit], np.log(w_fit))
print(np.exp(model.coef_[0]), model.coef_[1])

m_ = np.linspace(min(m_fit), max(m_fit), 10)

print(np.sum(w_m*m))

# Plotting the wealth distribution
plt.semilogy(m_, 0.01*np.exp(-0.01*m_))
plt.semilogy(m,w_m, "bo")

plt.legend(["Ordinary Least squares", "Computed distribution"])
plt.grid(linestyle = "--")
plt.xlabel("Wealth $m$")
plt.ylabel("Distribution of wealth $w_m$")

tikz_save("../figures/5b.tex", figureheight='\\figureheight', figurewidth='\\figureheight')
plt.show()	

