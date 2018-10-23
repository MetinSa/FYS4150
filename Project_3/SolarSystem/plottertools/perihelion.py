import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import find_peaks
import sys



if len(sys.argv) < 2:
	filename = "../output/" + "RelativisticMercury.txt"
else:
	if sys.argv[1].endswith(".txt"):
		filename = "../output/" + sys.argv[1]
	else:
		filename = "../output/" + sys.argv[1] + ".txt"

names = []
mass = []

with open(filename, "r") as file:
	for i in file.readline().split()[1:]:
		n, m = i.split("||")
		names.append(n)
		mass.append(float(m))

r = np.loadtxt(filename, skiprows = 1)
N = len(r)
n = len(names)

t = r[:,0]
r = r[:,1:]

# Reshape for better intuitive understanding of the positions. Axis: [planet, {x,y,z}, integration_step]
r = r.reshape((N,n,3)).swapaxes(0,1).swapaxes(1,2)

print("Read in %i lines" %(N))

dist = np.linalg.norm(r[1], axis = 0)
index = find_peaks(-dist, width=100, height = -0.307550)[0]

perang = np.degrees(np.arctan(r[1,1,index]/r[1,0,index]))*3600

test = True

c = 100

index[0] = 0

for i in range(len(index)):
	if t[index[i]] >= c:
		print((perang[i] - perang[0])*100/t[index[i]], "per century after %.2f years" %(t[index[i]]))
		c += 100

"""
plt.plot(t[index[0]], perang, "-o")

plt.grid()

plt.figure()
plt.plot(t, dist)
for i in index[0]:
	plt.plot(t[i], dist[i], "bo")
plt.grid()
plt.show()
"""
