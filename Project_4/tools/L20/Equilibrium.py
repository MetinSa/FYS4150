import numpy as np 
import sys as sys 
import os
import matplotlib.pyplot as plt 

filename = str(sys.argv[1])
quantity = str(sys.argv[2])

thermalize = False

if len(sys.argv) >= 4:
	equilibration = str(sys.argv[3])
	thermalize = True

# Path to directory containing files
path = "../../data/L20/"
savepath = "../../figures/L20/"

N, T, E, M, C_V, Chi, absM, accepted_states = np.loadtxt(path+filename+".dat", unpack = True)

expectation_list = [N, T, E, M, C_V, Chi, absM, accepted_states]


plt.figure(figsize=(10,5))
plt.subplots_adjust(left=0.08)

color = "royalblue"
# Plotting different quantities
if quantity == "E":
	plt.subplot(121)
	plt.plot(expectation_list[0], expectation_list[2], label = "T' = %.1f"%T[-1], color = color)
	plt.grid(linestyle = "--")
	plt.axvline(x = 0.1*N[-1], color = "black", linestyle = "--", alpha = 0.5, label = "Equilibrium border")
	plt.ylabel("Expected Energy", fontsize = 16)	
	plt.xlabel("MC Cycles", fontsize = 16)
	plt.legend(fontsize = 16)


	if thermalize == True:	
	# Discard pre equilibrium expectation values and scaling the accepted states
		N_max = N[-1]
		dN = N[10]-N[9]
		i_eq = int((0.1*N_max/dN))
		expectation_list[-1] -= expectation_list[-1][i_eq-1]		
		for i in range(len(expectation_list)):
			expectation_list[i] = expectation_list[i][i_eq:]
		plt.subplot(122)
		plt.plot(expectation_list[0], expectation_list[2], label = "T' = %.1f"%T[-1], color = color)
		plt.grid(linestyle = "--")
		plt.legend(fontsize = 16)


elif quantity == "M":
	plt.plot(expectation_list[0], expectation_list[3], label = "T' = %.1f"%T[-1], color = color)
	plt.grid(linestyle = "--")

	if thermalize == False:	 
		plt.axvline(x = 0.1*N[-1], color = "black", linestyle = "--", alpha = 0.5, label = "Equilibrium border")

	plt.legend()
	plt.ylabel(r"Expected Magnetization, $\langle M \rangle / $N$_\mathrm{spins}$  ")		

elif quantity == "absM":
	plt.plot(expectation_list[0], expectation_list[6], label = "T' = %.1f"%T[-1], color = color)
	plt.grid(linestyle = "--")

	if thermalize == False:	 
		plt.axvline(x = 0.1*N[-1], color = "black", linestyle = "--", alpha = 0.5, label = "Equilibrium border")

	plt.legend()
	plt.ylabel(r"$\langle \mid M \mid \rangle / $N$_\mathrm{spins}$  ")	

plt.xlabel("MC Cycles", fontsize = 16)
plt.savefig(savepath + "sub" + "Equilibrium" + quantity + ".pdf")
plt.show()