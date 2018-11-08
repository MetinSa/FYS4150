import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 
from matplotlib2tikz import save as tikz_save

filename1 = str(sys.argv[1])
filename2 = str(sys.argv[2])
quantity = str(sys.argv[3])

thermalize = False

if len(sys.argv) >= 5:
	equilibration = str(sys.argv[4])
	thermalize = True


# Reading in expectation values
N1, T1, E1, M1, C_V1, Chi1, absM1, accepted_states1 = np.loadtxt("../data/" + filename1 + ".dat", unpack = True)
expectation_list1 = [N1, T1, E1, M1, C_V1, absM1, accepted_states1]

N2, T2, E2, M2, C_V2, Chi2, absM2, accepted_states2 = np.loadtxt("../data/" + filename2 + ".dat", unpack = True)
expectation_list2 = [N2, T2, E2, M2, C_V2, absM2, accepted_states2]

if thermalize == True:

	# Discard pre equilibrium expectation values and scaling the accepted states
	N_max = N1[-1]
	dN = N1[10]-N1[9]
	i_eq = int((0.1*N_max/dN))
	expectation_list1[-1] -= expectation_list1[-1][i_eq-1]	
	expectation_list2[-1] -= expectation_list2[-1][i_eq-1]	

	for i in range(len(expectation_list)):
		expectation_list1[i] = expectation_list1[i][i_eq:]
		expectation_list2[i] = expectation_list2[i][i_eq:]

# Fixing title of plot

title = r"$20 \times 20$ random initial lattice"

# Plotting different quantities
if quantity == "E":
	plt.plot(expectation_list1[0], expectation_list1[2], label = "T = %.1f K" %T1[1], color = "mediumseagreen")
	plt.plot(expectation_list2[0], expectation_list2[2], label = "T = %.1f K" %T2[1], color = "darkgreen")
	plt.ylabel(r"Expected Energy $\langle E \rangle$")

elif quantity == "M":
	plt.plot(expectation_list1[0], expectation_list1[3], label = "T = %.1f K" %T1[1], color = "crimson")
	plt.plot(expectation_list2[0], expectation_list2[3], label = "T = %.1f K" %T2[1], color = "tomato")
	plt.ylabel(r"Expected Magnetization $\langle M \rangle$")

plt.title(title)
plt.legend()
plt.xlabel("Monte-Carlo Cycles")
plt.grid(linestyle = "--")
# plt.savefig("../figures/" + filename + "_" + quantity + ".png")
# tikz_save("equilibrium_estimate.tex", figureheight="\\figureheight", figurewidth="\\figureheight")

plt.show()