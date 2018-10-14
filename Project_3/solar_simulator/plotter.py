import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import mpl_toolkits.mplot3d.axes3d as p3

filename = "output/output.txt"

with open(filename, "r") as file:
	names = file.readline().split()

r = np.loadtxt(filename, skiprows = 1)
N = len(r)
n = len(names)

colours = ["gold", "silver", "goldenrod", "gray", "royalblue", "indianred", "darkorange", "palegoldenrod", "powderblue", "deepskyblue", "chocolate"]
mass = [1, 1.66012e-7, 2.44781e-6, 3.6943e-8, 3.003467e-6, 3.22713e-7, 9.5458e-4, 2.85812e-4, 4.36576e-5, 5.15028e-5, 6.583e-9]

centreofmass = np.zeros((N, 3))
for i in range(n):
	centreofmass += r[:, 0+3*i:3+3*i]*mass[i]
centreofmass /= np.sum(mass)

plt.plot(centreofmass[:,0], centreofmass[:,1])
for i in range(n):
	plt.plot(r[:,0+3*i], r[:,1+3*i])
plt.grid()
plt.axis("equal")
plt.show()



m = np.max(np.abs(r[:,:3*n-1]))

fig = plt.figure()
ax = p3.Axes3D(fig)

lines = []
dots = []

for i in range(n):
	line, = ax.plot(r[:,0+3*i], r[:,1+3*i], r[:,2+3*i], color=colours[i])
	dot,  = ax.plot([r[0,0+3*i]], [r[0,1+3*i]], [r[0,2+3*i]], "o", color=colours[i])
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

def run(i):
    i *= k
    # update the data
    #x, y, z = r[i, 9:12]
    #a = 0.005
    #ax.set_xlim(x-a,x+a)
    #ax.set_ylim(y-a,y+a)
    #ax.set_zlim(z-a,z+a)
    for j in range(n):
	    lines[j].set_data(r[:i+1,0+3*j], r[:i+1,1+3*j])
	    lines[j].set_3d_properties(r[:i+1, 2+3*j])
	    dots[j].set_data(r[i,0+3*j], r[i,1+3*j])
	    dots[j].set_3d_properties(r[i, 2+3*j])



ani = animation.FuncAnimation(fig, run, int(N/k), blit=False, interval=1)
plt.show()
