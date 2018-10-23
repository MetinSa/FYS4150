import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as mplcm
import matplotlib.colors as colors
from matplotlib2tikz import save as tikz_save
import sys



if len(sys.argv) < 2:
	print("Please provide filename and savefile in commandline")
	sys.exit()
else:
	if sys.argv[1].endswith(".bin"):
		filename = "../output/" + sys.argv[1]
	else:
		filename = "../output/" + sys.argv[1] + ".bin"


savefile = None
if len(sys.argv) > 2:
	if sys.argv[2].endswith(".tex"):
		savefile = "../Figures/" + sys.argv[2]
	else:
		savefile = "../Figures/" + sys.argv[2] + ".tex"

names = []
mass = []

with open(filename+".txt", "r") as file:
	for i in file.readline().split()[1:]:
		n, m = i.split("||")
		names.append(n.replace("_", " "))
		mass.append(float(m))

r = np.fromfile(filename)
nn = len(r)
n = len(names)
N = int(nn/(3*n+1))

r = r.reshape((N, 3*n+1))

t = r[:,0]
r = r[:,1:]

# Reshape for better intuitive understanding of the positions. Axis: [planet, {x,y,z}, integration_step]
r = r.reshape((N,n,3)).swapaxes(0,1).swapaxes(1,2)



# Defining colors
colours = {"Sun":"gold", "Mercury":"silver", "Venus":"goldenrod", "Moon":"gray",
			"Earth":"royalblue", "Mars":"indianred", "Jupiter":"darkorange",
			"Saturn":"palegoldenrod", "Uranus":"powderblue", "Neptune":"deepskyblue",
			"Pluto":"chocolate"}

k = 10

for i in range(n):
	plt.plot(r[i,0,::k], r[i,1,::k], color=colours[names[i]], label = names[i] )
	plt.plot(r[i,0][-1], r[i,1][-1], 'o', markeredgecolor="k" , color=colours[names[i]])
plt.grid()
plt.xlabel('x-position [AU]')
plt.ylabel('y-position [AU]')
plt.legend(loc = "upper right")
plt.axis("equal")
if savefile:
	tikz_save(savefile, figureheight="\\figureheight", figurewidth="\\figureheight")
plt.show()
