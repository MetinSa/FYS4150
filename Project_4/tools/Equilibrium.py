import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 

filename = sys.argv[1]
quantity = str(sys.argv[2])

N, T, E, M, C_V, Chi, absM, accepted_states = np.loadtxt("../data/" + filename + ".dat", unpack = True)

if "oriented" in filename:
	if "24" in filename:
		title = "20 x 20 oriented initial lattice with T = 2.4 K"
	else:
		title = "20 x 20 oriented initial lattice with T = 1 K"

else:
	if "24" in filename:
		title = "20 x 20 random initial lattice with T = 2.4 K"
	else:
		title = "20 x 20 random initial lattice with T = 1 K"

if quantity == "E":
	plt.plot(N, E, label = r"Average Energy, $\langle E \rangle$", color = "mediumseagreen")
	plt.ylabel("Expected Energy")

elif quantity == "M":
	plt.plot(N,absM, label = r"Average Magnetization, $\langle M \rangle$", color = "crimson")
	plt.ylabel("Expected Magnetization")

plt.title(title)
# plt.xlim(0,10000)
plt.legend()
plt.xlabel("Monte-Carlo Cycles")
plt.grid(linestyle = "--")
# plt.savefig("../figures/" + filename + "_" + quantity + ".png")
plt.show()