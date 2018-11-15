import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 

filename = str(sys.argv[1])
quantity_to_plot = str(sys.argv[2])

# Reading in expectation values
temperature, energy, energy_squared, energy_variance, specific_heat, magnetization, absolute_magnetization, susceptibility, accepted_states = np.loadtxt("../data/" + filename + ".dat", unpack = True)


# Plotting different quantities
if quantity_to_plot == "E":
	plt.plot(temperature, energy, label = r"$\langle E \rangle$", color = "royalblue")
	plt.ylabel("Expected energy")

if quantity_to_plot == "EE":
	plt.plot(temperature, energy_squared, label = r"$\langle E^2 \rangle$", color = "royalblue")
	plt.ylabel("Expected energy squared")

if quantity_to_plot == "EV":
	plt.plot(temperature, energy_variance, label = r"$\sigma_E^2$", color = "royalblue")
	plt.ylabel("Energy variance")

if quantity_to_plot == "SH":
	plt.plot(temperature, specific_heat, label = r"$C_V$", color = "royalblue")
	plt.ylabel("Specific Heat")

if quantity_to_plot == "M":
	plt.plot(temperature, magnetization, label = r"$\langle M \rangle$", color = "royalblue")
	plt.ylabel("Expected magnetization")

if quantity_to_plot == "absM":
	plt.plot(temperature, absolute_magnetization, label = r"$\langle M \rangle$", color = "royalblue")
	plt.ylabel("Expected absolute magnetization")

if quantity_to_plot == "SUS":
	plt.plot(temperature, susceptibility, label = r"$\chi $", color = "royalblue")
	plt.ylabel("susceptibility")

if quantity_to_plot == "AS":
	plt.plot(temperature, accepted_states, color = "royalblue")
	plt.ylabel("Accepted states")

plt.legend()
plt.xlabel("Temperature")
plt.grid(linestyle = "--")
# plt.savefig("../figures/" + filename + "_" + quantity_to_plot + ".png")

plt.show()