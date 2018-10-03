import numpy as np 
import matplotlib.pyplot as plt 
import sys 

# Reading in filename and opening it
names = map(str, sys.argv[1:])


files = [open(i, "r") for i in names]


# Reading in all lines

lines = [i.readlines() for i in files]


# Closing files

N = len(files)
for i in range(N):
	files[i].close()


# Extracting number of grid points and rho_n
n = int(lines[0][0])
rho_n = float(lines[0][1])

omegas = [float(i[3]) for i in lines]

# Making u (groundstate energy eigenvector) and rho_array
u = [np.zeros(n) for i in range(N)]
rho_array = np.linspace(0,rho_n,n)

# Filling u
for j in range(N):
	for i in range(n):
		u[j][i] = float(lines[j][i+5])

	# Squaring and taking the absolute value of u
	u[j]= np.abs(u[j][::-1]**2)

colours = ["darkorchid", "mediumseagreen", "crimson", "royalblue", "hotpink", "lime", "olivedrab", "magenta"]

# # Plotting
for i in range(N):
	plt.plot(rho_array,u[i], color = colours[i], label = r"$\omega_r = %g$" %omegas[i])

plt.xlabel(r"$\rho$")
plt.ylabel(r"$\mid u(\rho) \mid^2$")
plt.legend()
plt.title(r"Interacting electrons in potential $V = \omega_r^2 \rho^2 + 1/\rho$")
plt.grid()
plt.savefig("interacting_%i_%i.pdf" %(n,rho_n))
#plt.show()