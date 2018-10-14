from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt

file = "output/output.txt"

r = np.loadtxt(file, skiprows = 1)

plt.axes(projection='3d')
for i in range(10):
	plt.plot(r[:,0+3*i], r[:,1+3*i], r[:,2+3*i])
	plt.plot([r[-1,0+3*i]], [r[-1,1+3*i]], [r[-1,2+3*i]], "o")


plt.axis("equal")
plt.show()