import numpy as np 
import matplotlib.pyplot as plt 
import sys 

# Reading in filename and opening it
name1 = str(sys.argv[1])
name2 = str(sys.argv[2])
name3 = str(sys.argv[3])
name4 = str(sys.argv[4])

file1 = open(name1, "r")
file2 = open(name2, "r")
file3 = open(name3, "r")
file4 = open(name4, "r")

# Reading in all lines
lines1 = file1.readlines()
lines2 = file2.readlines()
lines3 = file3.readlines()
lines4 = file4.readlines()

# Extracting number of grid points and rho_n
n = int(lines1[0])
rho_n = float(lines1[1])
omega1 = float(lines1[3])
omega2 = float(lines2[3])
omega3 = float(lines3[3])
omega4 = float(lines4[3])

# Making u (groundstate energy eigenvector) and rho_array
u1 = np.zeros(n)
u2 = np.zeros(n)
u3 = np.zeros(n)
u4 = np.zeros(n)
rho_array = np.linspace(0,rho_n,n)

# Filling u
for i in range(n):
	u1[i] = float(lines1[i+5])
	u2[i] = float(lines2[i+5])
	u3[i] = float(lines3[i+5])
	u4[i] = float(lines4[i+5])

# Squaring and taking the absolute value of u
u1 = np.abs(u1**2)
u2 = np.abs(u2**2)
u3 = np.abs(u3**2)
u4 = np.abs(u4**2)

# # Plotting
plt.plot(rho_array,u1, color = "darkorchid", label = r"$\omega_r = %g$" %omega1)
plt.plot(rho_array,u2, color = "mediumseagreen", label = r"$\omega_r = %g$" %omega2)
plt.plot(rho_array,u3, color = "crimson", label = r"$\omega_r = %g$" %omega3)
plt.plot(rho_array,u4, color = "royalblue", label = r"$\omega_r = %g$" %omega4)
plt.xlabel(r"$\rho$")
plt.ylabel(r"$\mid u(\rho) \mid^2$")
plt.legend()
plt.title(r"Interacting electrons in potential $V = \omega_r^2 \rho^2 + 1/\rho$")
plt.savefig("interacting.pdf")

plt.show()