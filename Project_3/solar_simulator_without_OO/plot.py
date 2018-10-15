import matplotlib.pyplot as plt
import numpy as np
import sys

# Reading in the name of the file and opening it
name = str(sys.argv[1])
file = open(name, "r")

t = []
x = []
y = []

#extracting number of grid points
expo = int(file.readline())

# Iterating over all the lines in the file
for i, line in enumerate(file):

	# Skipping the first line
    if i > 1:
        t.append(float(line.split()[0]))
        x.append(float(line.split()[1]))
        y.append(float(line.split()[2]))


# plotting
plt.plot(x, y, color = "turquoise", label = "Earth")
plt.plot(0,0, marker='o', markersize=10, color="orange", label="Sun", linestyle="None")
plt.grid()
plt.legend()
plt.xlabel("x [AU]")
plt.ylabel("y [AU]")
if name[12] == 'e':
	plt.title(r"Sun-Earth system using Euler's method ($N=10^{%d}$)" %expo)
if name[12] == 'v':
	plt.title(r"Sun-Earth system using the velocity Verlet method ($N=10^{%d}$)" %expo)
plt.show()
