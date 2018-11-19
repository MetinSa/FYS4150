import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 
import os

# Path to directory containing files
path = "../../data/L40+/"

filenames = []
for filename in os.listdir(path):
	if ".dat" in filename:
		filenames.append(filename)

# Critical temperature dictionaries
T_C_CV = {}
T_C_SUS = {}

for files in filenames:
	# Reading in expectation values
	temperature, energy, energy_squared, energy_variance, specific_heat, magnetization, absolute_magnetization, susceptibility, accepted_states = np.loadtxt(path + files, unpack = True)

	# Creating a best fit polynomial to the data
	fit_CV = np.polyfit(temperature,specific_heat,200)
	fit_SUS = np.polyfit(temperature,susceptibility,200)
	polynomial_CV = np.poly1d(fit_CV)
	polynomial_SUS = np.poly1d(fit_SUS)
	t_new = np.linspace(temperature[0],temperature[-1], len(temperature))
	bestfit_polynomial_CV = polynomial_CV(t_new)
	bestfit_polynomial_SUS = polynomial_SUS(t_new)

	# Appending values to dictionaries
	T_C_CV[files] = temperature[(np.argwhere(bestfit_polynomial_CV == np.amax(bestfit_polynomial_CV))[0][0])]
	T_C_SUS[files] = temperature[(np.argwhere(bestfit_polynomial_SUS == np.amax(bestfit_polynomial_SUS))[0][0])]

# Combing the two lists and connecting them to their respective lattice dimensions
# T_C_list = [T_C_CV, T_C_SUS]
T_C_L40 = 0;	T_C_L60 = 0;	T_C_L80 = 0;	T_C_L100 = 0

for Tc in [T_C_CV, T_C_SUS]:
	for key, value in Tc.items():
		if "40" in key:
			T_C_L40 += value

		elif "60" in key:
			T_C_L60 += value

		elif "80" in key:
			T_C_L80 += value

		else:
			T_C_L100 += value

# Creating a dictionary with the normalized critical temperature
T_C = {"40":T_C_L40/2, "60":T_C_L60/2, "80":T_C_L80/2, "100":T_C_L100/2}

# Prints the critical temperature for all given lattices
print("=="*17)
for key in T_C:
	print("T_C(L = %d) = %.7f" %(int(key),T_C[key]))
print("=="*17)

# setting nu = 1
nu = 1


def get_a(L1,L2):

	# Computes the constant a for two lattice sizes.
	return ((np.abs(T_C[str(L1)] - T_C[str(L2)]))/np.abs((L1**(-1/nu) - (L2**(-1/nu)))))


# Determining best value of constant a by checking all possible combinations of L1 and L2
a_list = []

for key_i in T_C:
	for key_j in T_C:
		if key_i != key_j:
			a = get_a(int(key_i),int(key_j))
			if a not in a_list:
				a_list.append(a)

a = np.average(a_list)

def get_T_C_infty(L):

	# Computes the critical temperature of an infinite system
	return T_C[str(L)] - a*L**(-1/nu)


# Computing T_C_infty for all lattice sizes L
T_C_infty_list = []
for key in T_C:
	T_C_infty_list.append(get_T_C_infty(int(key)))

#Finding the average T_C_infty
T_C_infty = np.average(T_C_infty_list)

print("T_C(L = infty) = %.7f" %T_C_infty)
print("=="*17)