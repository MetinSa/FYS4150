import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 
import os

# Path to directory containing files
path = "../data/Phasetransition/"

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
T_C = [T_C_CV, T_C_SUS]
T_C_L40 = 0;	T_C_L60 = 0;	T_C_L80 = 0;	T_C_L100 = 0

for Tc in T_C:
	for key, value in Tc.items():
		if "40" in key:
			T_C_L40 += value

		elif "60" in key:
			T_C_L60 += value

		elif "80" in key:
			T_C_L80 += value

		else:
			T_C_L100 += value

# Normalizing the values
T_C_L40 /= 2;	T_C_L60 /= 2;	T_C_L80 /= 2;	T_C_L100 /= 2

print("L = 40:	T_C = %.7f" %T_C_L40)
print("L = 60:	T_C =  %.7f" %T_C_L60)
print("L = 80:	T_C =  %.7f" %T_C_L80)
print("L = 100:T_C =  %.7f" %T_C_L100)