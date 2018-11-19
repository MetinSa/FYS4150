import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 
import os
from cycler import cycler

#Reading in filename and the quantitiy one wishes to study
#filename = str(sys.argv[1])
quantity_to_plot = str(sys.argv[1])

plt.figure(figsize=(5,5))
color=['mediumseagreen', 'orange','crimson', 'royalblue']
# plt.rc('axes', prop_cycle=default_cycler)
plt.rc('text', usetex=True)
plt.rc('font', family='serif')
plt.subplots_adjust(left = 0.14)

# Path to directory containing files
path = "../../data/L40+/"
savepath = "../../figures/"

filenames = []

for filename in os.listdir(path):
	if ".dat" in filename:
		filenames.append(filename)

filenames = sorted(filenames)
filenames += [filenames.pop(0)]
idum = 0
for filename in filenames:
	# Reading in expectation values
	temperature, energy, energy_squared, energy_variance, specific_heat, magnetization, absolute_magnetization, susceptibility, accepted_states = np.loadtxt(path + filename, unpack = True)

	#Extracting number of spins
	if "40" in filename:
		nspins = 40**2	
		label = "L = 40"

	elif "60" in filename:
		nspins = 60**2	
		label = "L = 60"

	elif "80" in filename:
		nspins = 80**2	
		label = "L = 80"

	else:
		nspins = 100**2
		label = "L = 100"
	# Computing the absSusceptibility
	absSusceptibility = susceptibility + ((magnetization*magnetization)/(temperature*nspins)) - \
	(absolute_magnetization*absolute_magnetization/(temperature*nspins))	



	# Plotting different quantities
	if quantity_to_plot == "E":

		fit = np.polyfit(temperature,energy,200)
		polynomial = np.poly1d(fit)
		bestfit_polynomial = polynomial(temperature)
		plt.plot(temperature,bestfit_polynomial, label = label,color = color[idum])
		plt.ylabel(r"Expected energy, $\langle E \rangle /(J $ N$_\mathrm{spin})$", fontsize=15)	

	if quantity_to_plot == "SH":
		fit = np.polyfit(temperature,specific_heat,200)
		polynomial = np.poly1d(fit)
		bestfit_polynomial = polynomial(temperature)
		plt.plot(temperature[0::10],bestfit_polynomial, label = label,color = color[idum])
		plt.ylabel(r"Specific Heat, $C_V / (k_B$ N$_\mathrm{spin}$)", fontsize=15)	
		top = temperature[(np.argwhere(bestfit_polynomial == np.amax(bestfit_polynomial))[0][0])]
		plt.axvline(x = top,color = color[idum], linestyle = "--", alpha = 0.5)
	

	if quantity_to_plot == "absM":
		fit = np.polyfit(temperature,absolute_magnetization,120)
		polynomial = np.poly1d(fit)
		bestfit_polynomial = polynomial(temperature)
		plt.plot(temperature,bestfit_polynomial, label = label,color = color[idum])
		plt.ylabel(r"Expected absolute magnetization, $\langle \mid M \mid \rangle / $ N$_\mathrm{spin})$ ", fontsize=15)	

	if quantity_to_plot == "SUS":
		fit = np.polyfit(temperature,susceptibility,200)
		polynomial = np.poly1d(fit)
		bestfit_polynomial = polynomial(temperature)
		plt.plot(temperature,bestfit_polynomial, label = label,color = color[idum])
		plt.ylabel(r"Susceptibility, ($\chi$ $J$ )/ N$_\mathrm{spin}$", fontsize=15)
		top = temperature[(np.argwhere(bestfit_polynomial == np.amax(bestfit_polynomial))[0][0])]
		plt.axvline(x = top,color = color[idum], linestyle = "--", alpha = 0.5)	

	idum +=1

plt.legend(fontsize = 13, loc = "best")
plt.xlabel("Temperature, $T'$", fontsize=15 )
plt.grid(linestyle = "--")
# plt.savefig(savepath+quantity_to_plot + "best" +".pdf")	

plt.show()