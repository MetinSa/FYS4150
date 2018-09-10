import numpy as np

with open("time_.dat", "r") as fil:
	a = fil.read()

print("%.5e" % np.average(list(map(float,a.split()))))