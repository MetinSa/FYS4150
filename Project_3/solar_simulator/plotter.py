import numpy as np
import matplotlib.pyplot as plt

file = "output/output.txt"

r = np.loadtxt(file, skiprows = 1)

print(r)

"""
G = 4*np.pi**2

N = 1000000

t, dt = np.linspace(0, 1, N, retstep = True)
r = np.zeros((N,3))
v = np.zeros((N,3))
m = 0.00001
M = 1

r[0] = (1,0,0)
v[0] = (0,2*np.pi,0)

for i in range(1, N):
	F = -r[i-1]*m*M*G/np.linalg.norm(r[i-1])**3
	v[i] = v[i-1] + dt*F/m
	r[i] = r[i-1] + v[i]*dt
"""

for i in range(10):
	plt.plot(r[:,0+3*i], r[:,1+3*i])


plt.axis("equal")
plt.show()