import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.cm as mplcm
import matplotlib.colors as colors
from matplotlib2tikz import save as tikz_save

import sys



if len(sys.argv) < 2:
	print("Please provide filename in commandline")
	sys.exit()
else:
	if sys.argv[1].endswith(".txt"):
		filename = "output/" + sys.argv[1]
	else:
		filename = "output/" + sys.argv[1] + ".txt"

names = []
mass = []

with open(filename, "r") as file:
	for i in file.readline().split():
		n, m = i.split("||")
		names.append(n)
		mass.append(float(m))

r = np.loadtxt(filename, skiprows = 1)
N = len(r)
n = len(names)

# Reshape for better intuitive understanding of the positions. Axis: [planet, {x,y,z}, integration_step]
r = r.reshape((N,n,3)).swapaxes(0,1).swapaxes(1,2)



# Defining colors
colours = {"Sun":"gold", "Mercury":"silver", "Venus":"goldenrod", "Moon":"gray",
			"Earth":"royalblue", "Mars":"indianred", "Jupiter":"darkorange",
			"Saturn":"palegoldenrod", "Uranus":"powderblue", "Neptune":"deepskyblue",
			"Pluto":"chocolate"}


for i in range(n):
	plt.plot(r[i,0], r[i,1], color=colours[names[i]])
	plt.plot(r[i,0][-1], r[i,1][-1], 'o', color=colours[names[i]])
plt.grid()
plt.xlabel('x-position [AU]')
plt.ylabel('y-position [AU]')
plt.axis("equal")
tikz_save("Figures/figure.tex", figureheight='\\figureheight', figurewidth='\\figurewidth')
plt.show()
