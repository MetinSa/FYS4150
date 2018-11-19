import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 
import os
from cycler import cycler

#Reading in filename and the quantitiy one wishes to study
#filename = str(sys.argv[1])
quantity_to_plot = str(sys.argv[1])

plt.figure(figsize=(5,5))
default_cycler = (cycler(color=['mediumseagreen', 'orange','crimson', 'royalblue']))
plt.rc('axes', prop_cycle=default_cycler)
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

		plt.scatter(temperature, energy, label = label, alpha = 0.5, s = 10)
		#plt.plot(temperature,bestfit_polynomial, label = label + " best fit")
		plt.ylabel(r"Expected energy, $\langle E \rangle /(J $ N$_\mathrm{spin})$", fontsize=15)	

	if quantity_to_plot == "SH":
		plt.scatter(temperature, specific_heat, label = label, alpha = 0.5, s = 10)
		plt.ylabel(r"Specific Heat, $C_V / (k_B$ N$_\mathrm{spin}$)", fontsize=15)		

	if quantity_to_plot == "absM":
		plt.scatter(temperature, absolute_magnetization, label= label, alpha = 0.5, s = 10)
		plt.ylabel(r"Expected absolute magnetization, $\langle \mid M \mid \rangle / $ N$_\mathrm{spin})$ ", fontsize=15)	

	if quantity_to_plot == "SUS":
		plt.scatter(temperature, absSusceptibility, label= label, alpha=0.5, s = 10)
		plt.ylabel(r"Susceptibility, ($\chi$ $J$ )/ N$_\mathrm{spin}$", fontsize=15)	

	if quantity_to_plot == "AS":
		plt.plot(temperature, accepted_states)
		plt.ylabel("Accepted states", fontsize=15)	

plt.legend(fontsize = 13)
plt.xlabel("Temperature, $T'$", fontsize=15 )
plt.grid(linestyle = "--")
plt.savefig(savepath+quantity_to_plot + ".pdf")	

plt.show()