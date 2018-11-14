import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 
from matplotlib2tikz import save as tikz_save

filename = sys.argv[1]

thermalize = True

# Reading in expectation values
N, T, E, M, C_V, Chi, absM, accepted_states = np.loadtxt("../data/" + filename + ".dat", unpack = True)
expectation_list = [N, T, E, M, C_V, absM, accepted_states]

if thermalize == True:

	# Discard pre equilibrium expectation values and scaling the accepted states
	N_max = N[-1]
	dN = N[10]-N[9]
	i_eq = int((0.1*N_max/dN))
	expectation_list[-1] -= expectation_list[-1][i_eq-1]	

	for i in range(len(expectation_list)):
		expectation_list[i] = expectation_list[i][i_eq:]

weights = np.ones_like(expectation_list[2])/float(len(expectation_list[2]))
# print(E)
plt.figure(figsize=(5,5))
n, bins, patches = plt.hist(expectation_list[2],30 , weights = weights, color = "royalblue", edgecolor= "black", label = "$T' = $%.1f"%expectation_list[1][1])
plt.grid(linestyle = "--")
plt.xlabel("Energy per spin")
plt.ylabel("Probability")
plt.legend()
plt.subplots_adjust(left=0.15)

plt.savefig("../data/" + filename + ".pdf")

# tikz_save("../data/" + filename + ".tex", figureheight="\\figureheight", figurewidth="\\figureheight")
plt.show()
