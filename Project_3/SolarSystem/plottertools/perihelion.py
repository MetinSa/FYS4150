import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import find_peaks
import sys
from sklearn import linear_model



if len(sys.argv) < 2:
	filename = "../output/" + "RelativisticMercury.bin"
else:
	if sys.argv[1].endswith(".bin"):
		filename = "../output/" + sys.argv[1]
	else:
		filename = "../output/" + sys.argv[1] + ".bin"

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

print("Read in %i lines" %(N))

dist = np.linalg.norm(r[1], axis = 0)
index = find_peaks(-dist, width=100, height = -0.307550)[0]

perang = -np.degrees(np.arctan(r[1,1,index]/r[1,0,index]))*3600

"""
c = 100

for i in range(len(index)):
	if t[index[i]] >= c:
		print((perang[i] - perang[0])*100/t[index[i]], "per century after %.2f years" %(t[index[i]]))
		c += 100
"""

lm = linear_model.LinearRegression()
X = np.c_[np.ones((len(index))), t[index]]
model = lm.fit(X,perang)

print(model.coef_)

plt.plot(t[index], perang)
plt.grid()
plt.show()

