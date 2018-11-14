import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 

filename = str(sys.argv[1])
quantity = str(sys.argv[2])



# Reading in expectation values
T, E, M, C_V, Chi, absM = np.loadtxt("../data/" + filename + ".dat", unpack = True)
expectation_list = [T, E, M, C_V, absM]


# Plotting different quantities
if quantity == "E":
	plt.plot(expectation_list[0], expectation_list[1], label = r"Average Energy, $\langle E \rangle$", color = "royalblue")
	plt.ylabel("Expected Energy")

elif quantity == "M":
	plt.plot(expectation_list[0], expectation_list[2], label = r"Average Magnetization, $\langle M \rangle$", color = "crimson")
	plt.ylabel("Expected Magnetization")

plt.legend()
plt.xlabel("Temperature")
plt.grid(linestyle = "--")
# plt.savefig("../figures/" + filename + "_" + quantity + ".png")

plt.show()