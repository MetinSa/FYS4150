import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
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
		names.append(n.replace("_", " "))
		mass.append(float(m))

r = np.loadtxt(filename, skiprows = 1)
N = len(r)
n = len(names)

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

if len(sys.argv) > 2:
	plt.plot(centreofmass[:,0], centreofmass[:,1])
	for i in range(n):
		plt.plot(r[i,0], r[i,1])
	plt.grid()
	plt.axis("equal")
	plt.show()


m = np.max(np.abs(r))

fig = plt.figure()
ax = p3.Axes3D(fig)

lines = []
dots = []

for i in range(n):
	line, = ax.plot(r[i,0], r[i,1], r[i,2], color=colourpicker(i))
	dot,  = ax.plot([r[i,0,0]], [r[i,1,0]], [r[i,2,0]], "o", markeredgecolor="k", color=colourpicker(i))
	lines.append(line)
	dots.append(dot)



fig.legend(dots, names)

ax.grid()
ax.set_xlim(-m,m)
ax.set_ylim(-m,m)
ax.set_zlim(-m,m)
ax.set_aspect("equal")
ax.view_init(90)

k = 1


plt.show()
