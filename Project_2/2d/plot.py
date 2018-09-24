import numpy as np 
import matplotlib.pyplot as plt 
import sys 

# Reading in filename and opening it
name = str(sys.argv[1])
file = open(name, "r")

# Reading in all lines
lines = file.readlines()

# Extracting number of grid points and rho_n
n = int(lines[0])
rho_n = float(lines[1])

# Making u (groundstate energy eigenvector) and rho_array
u = np.zeros(n)
rho_array = np.linspace(0,rho_n,n)

# Filling u
for i in range(n):
	u[i] = float(lines[i+3])

# Squaring and taking the absolute value of u
u = np.abs(u**2)

# # Plotting
plt.plot(rho_array,u, color = "royalblue")
plt.xlabel(r"$\rho$")
plt.ylabel(r"$\mid u(\rho) \mid^2$")
plt.title(r"Electron in harmonic oscillator potential, $V = \rho^2$")
plt.savefig(name.replace(".dat", ".pdf"))

plt.show()