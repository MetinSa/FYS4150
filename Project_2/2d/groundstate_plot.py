import numpy as np 
import matplotlib.pyplot as plt 
import sys 

# Reading in filename and opening it
name = str(sys.argv[1])
file = open(name, "r")

# Extracting number of grid points
n = int(file.readline())

# Reading in u
u = np.zeros(n)

u[:] = file.readlines()[1:]

# Definitions
rho = np.linspace(0,1,n)
u_squared = u**2

plt.plot(rho,u_squared, color = "royalblue")
plt.grid(ls="--")
plt.xlabel(r"$\rho$")
plt.ylabel(r"$\mid u \mid^2$")
plt.title("Electron in harmonic oscillator potential ")
plt.show()