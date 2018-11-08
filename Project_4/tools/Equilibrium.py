import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 
from matplotlib2tikz import save as tikz_save

filename = str(sys.argv[1])
quantity = str(sys.argv[2])

thermalize = False

if len(sys.argv) >= 4:
	equilibration = str(sys.argv[3])
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

# Fixing title of plot
if "oriented" in filename:
	if "24" in filename:
		title = r"$20 \times 20$ oriented initial lattice with $T = 2.4$ K"
	else:
		title = r"$20 \times 20$ oriented initial lattice with $T = 1$ K"

if "random" in filename:
	if "24" in filename:
		title = r"$20 \times 20$ random initial lattice with $T = 2.4$ K"
	else:
		title = r"$20 \times 20$ random initial lattice with $T = 1$ K"

else:
	title = r"$20 \times 20$ random initial lattice"

# Plotting different quantities
if quantity == "E":
	plt.plot(expectation_list[0], expectation_list[2], label = r"Average Energy, $\langle E \rangle$", color = "mediumseagreen")
	plt.ylabel("Expected Energy")

elif quantity == "M":
	plt.plot(expectation_list[0], expectation_list[3], label = r"Average Magnetization, $\langle M \rangle$", color = "crimson")
	plt.ylabel("Expected Magnetization")

plt.title(title)
plt.axvline(x = 10000, color = "black", linestyle = "--", alpha = 0.5, label = "Equilibrium estimate")
plt.legend()
plt.xlabel("Monte-Carlo Cycles")
plt.grid(linestyle = "--")
# plt.savefig("../figures/" + filename + "_" + quantity + ".png")
tikz_save("equilibrium_estimate.tex", figureheight="\\figureheight", figurewidth="\\figureheight")

plt.show()