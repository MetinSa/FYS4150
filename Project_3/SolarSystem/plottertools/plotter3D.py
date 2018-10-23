import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
from matplotlib2tikz import save as tikz_save
import sys


if len(sys.argv) < 2:
	print("Please provide filename in commandline")
	sys.exit()
else:
	if sys.argv[1].endswith(".txt"):
		filename = "../output/" + sys.argv[1]
	else:
		filename = "../output/" + sys.argv[1] + ".txt"

savefile = None
if len(sys.argv) > 2:
	if sys.argv[2].endswith(".tex"):
		savefile = "../Figures/" + sys.argv[2].replace(".tex", "3D.tex")
	else:
		savefile = "../Figures/" + sys.argv[2] + "3D.tex"

names = []
mass = []

with open(filename, "r") as file:
	for i in file.readline().split()[1:]:
		n, m = i.split("||")
		names.append(n.replace("_", " "))
		mass.append(float(m))

r = np.loadtxt(filename, skiprows = 1)
N = len(r)
n = len(names)

t = r[:,0]
r = r[:,1:]

# Reshape for better intuitive understanding of the positions. Axis: [planet, {x,y,z}, integration_step]
r = r.reshape((N,n,3)).swapaxes(0,1).swapaxes(1,2)

colours = {"Sun":"gold", "Mercury":"silver", "Venus":"goldenrod", "Moon":"gray",
			"Earth":"royalblue", "Mars":"indianred", "Jupiter":"darkorange", 
			"Saturn":"palegoldenrod", "Uranus":"powderblue", "Neptune":"deepskyblue",
			"Pluto":"chocolate"}

# Using distinct colours for objects not predefined
num_col = len([i for i in names if i not in colours.keys()])
k = len([i for i in names if i in colours.keys()])


def colourpicker(i):
	if names[i] in colours.keys():
		return colours[names[i]]
	else:
		return plt.cm.rainbow((i-k)/(num_col))


centreofmass = np.average(r, weights=mass, axis=0)
normed_cm = np.linalg.norm(centreofmass, axis=0)

print("Maximum deviation of centre of mass: %.2e Au" %(max(normed_cm)))

m = np.max(np.abs(r))
#m = 27
fig = plt.figure()
ax = p3.Axes3D(fig)

lines = []
dots = []

k = 100

for i in range(n):
	line, = ax.plot(r[i,0,::k], r[i,1,::k], r[i,2,::k], color=colourpicker(i))
	dot,  = ax.plot([r[i,0,0]], [r[i,1,0]], [r[i,2,0]], "o", markeredgecolor="k", color=colourpicker(i))
	lines.append(line)
	dots.append(dot)



fig.legend(dots, names,loc = "upper left")

ax.grid()
ax.set_xlabel('x-position [AU]')
ax.set_ylabel('y-position [AU]')
ax.set_zlabel('z-position [AU]')
ax.set_xlim(-m,m)
ax.set_ylim(-m,m)
ax.set_zlim(-m,m)
ax.set_aspect("equal")
# ax.view_init(90)
if savefile:
	tikz_save(savefile, figureheight="\\figureheight", figurewidth="\\figureheight")

plt.show()
