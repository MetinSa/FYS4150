import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 

filename = str(sys.argv[1])
quantity_to_plot = str(sys.argv[2])

# Reading in expectation values
temperature, energy, energy_squared, energy_variance, specific_heat, magnetization, absolute_magnetization, susceptibility = np.loadtxt("../data/" + filename + ".dat", unpack = True)


# Plotting different quantities
if quantity_to_plot == "E":
	plt.plot(temperature, energy, label = r"$\langle E \rangle$", color = "royalblue")
	plt.ylabel("Expected Energy")

if quantity_to_plot == "M":
	plt.plot(temperature, magnetization, label = r"$\langle E \rangle$", color = "crimson")
	plt.ylabel("Expected magnetization")

if quantity_to_plot == "V":
	plt.plot(temperature, energy_variance, label = r"$\langle E \rangle$", color = "royalblue")
	plt.ylabel("Expected Energy Variance")

plt.legend()
plt.xlabel("Temperature")
plt.grid(linestyle = "--")
# plt.savefig("../figures/" + filename + "_" + quantity_to_plot + ".png")

plt.show()