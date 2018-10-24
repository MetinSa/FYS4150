import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
# from matplotlib2tikz import save as tikz_save
import sys


if len(sys.argv) < 2:
	print("Please provide filename in commandline")
	sys.exit()
else:
	if sys.argv[1].endswith(".bin"):
		filename = "../output/" + sys.argv[1]
	else:
		filename = "../output/" + sys.argv[1] + ".bin"

savefile = None
if len(sys.argv) > 2:
	if sys.argv[2].endswith(".tex"):
		savefile = "../Figures/" + sys.argv[2].replace(".tex", "3D.tex")
	else:
		savefile = "../Figures/" + sys.argv[2] + "3D.tex"

	if sys.argv[2].endswith(".pdf"):
		savefile = "../Figures/" + sys.argv[2].replace(".pdf", "3D.pdf")
	else:
		savefile = "../Figures/" + sys.argv[2] + "3D.pdf"

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
# m = 30
fig = plt.figure()
ax = p3.Axes3D(fig)

lines = []
dots = []

j = 1
print (np.shape(r))

for i in range(n):
	line, = ax.plot(r[i,0,::j], r[i,1,::j], r[i,2,::j], color=colourpicker(i))
	dot,  = ax.plot([r[i,0,0]], [r[i,1,0]], [r[i,2,0]], "o", markeredgecolor="k", color=colourpicker(i))
	lines.append(line)
	dots.append(dot)

# Jovian System spesifics
# x = r[1,0,0]
# y = r[1,1,0]
# z = r[1,2,0]
# a = 0.005
# ax.set_xlim(x-a,x+a)
# ax.set_ylim(y-a,y+a)
# ax.set_zlim(z-a,z+3*a)


fig.legend(dots, names,loc = "upper left")

ax.grid()
ax.set_xlabel('x-position [AU]')
ax.set_ylabel('y-position [AU]')
ax.set_zlabel('z-position [AU]')
ax.set_xlim(-m,m)
ax.set_ylim(-m,m)
ax.set_zlim(-m,m)
ax.set_aspect("equal")
# ax.view_init(18,140)
if savefile:
	plt.savefig(savefile)
	# tikz_save(savefile, figureheight="\\figureheight", figurewidth="\\figureheight")

plt.show()
