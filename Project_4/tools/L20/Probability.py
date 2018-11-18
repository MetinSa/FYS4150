import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 
from matplotlib2tikz import save as tikz_save

filename = sys.argv[1]

thermalize = True
#plt.rcParams["xtick.labelsize"] = 8


# Reading in expectation values
N, T, E, M, C_V, Chi, absM, accepted_states = np.loadtxt("../../data/Probability/" + filename + ".dat", unpack = True)
expectation_list = [N, T, E, M, C_V, absM, accepted_states]

if thermalize == True:

	# Discard pre equilibrium expectation values and scaling the accepted states
	N_max = N[-1]
	dN = N[10]-N[9]
	i_eq = int((0.1*N_max/dN))
	expectation_list[-1] -= expectation_list[-1][i_eq-1]	

	for i in range(len(expectation_list)):
		expectation_list[i] = expectation_list[i][i_eq:]

varE = ((expectation_list[4])*T[-1]**2)
print(varE[-1])
print(np.sqrt(varE[-1]))
#print(np.sqrt(varE[-1]))

print(np.std(expectation_list[2]))
weights = np.ones_like(expectation_list[2])/float(len(expectation_list[2]))
# print(E)
plt.figure(figsize=(5,5))
n, bins, patches = plt.hist(expectation_list[2],30 , weights = weights, color = "royalblue", edgecolor= "black", label = "$T' = $%.1f"%expectation_list[1][1])
plt.grid(linestyle = "--")
plt.xlabel(r"Energy, $ \langle E \rangle / J$ N$_\mathrm{spin}$")
plt.ylabel("Probability")
#plt.xlim(-1.9972,-1.997)
plt.legend()
plt.subplots_adjust(left=0.15)



# plt.savefig("../../figures/L20" + filename + ".pdf")

# tikz_save("../data/" + filename + ".tex", figureheight="\\figureheight", figurewidth="\\figureheight")
plt.show()
