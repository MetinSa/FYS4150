import numpy as np 
import sys as sys 
import os
import matplotlib.pyplot as plt 

orientation = str(sys.argv[1])
quantity = str(sys.argv[2])

thermalize = False

if len(sys.argv) >= 4:
	equilibration = str(sys.argv[3])
	thermalize = True

# Path to directory containing files
path = "../../data/L20/"
savepath = "../../figures/L20/"

files = []

for filename in os.listdir(path):
	if orientation == "random":
		if "random" in filename :
			files.append(filename)

	else:
		if "oriented" in filename:
			files.append(filename)

dummy_index = 211
color = "royalblue"
plt.figure(figsize=(6,5))
plt.subplots_adjust(left=0.14)

# Reading in expectation values
for file in files:
	N, T, E, M, C_V, Chi, absM, accepted_states = np.loadtxt(path+file, unpack = True)
	expectation_list = [N, T, E, M, C_V, Chi, absM, accepted_states]

	if thermalize == True:	

		# Discard pre equilibrium expectation values and scaling the accepted states
		N_max = N[-1]
		dN = N[10]-N[9]
		i_eq = int((0.1*N_max/dN))
		expectation_list[-1] -= expectation_list[-1][i_eq-1]		

		for i in range(len(expectation_list)):
			expectation_list[i] = expectation_list[i][i_eq:]	

	# Plotting different quantities
	if quantity == "E":
		plt.subplot(dummy_index)
		plt.plot(expectation_list[0], expectation_list[2], label = "T' = %.1f"%T[-1], color = color)
		plt.grid(linestyle = "--")
		plt.legend()
		if dummy_index == 211:
			plt.ylabel(r"$\langle E \rangle / (J\cdot $N$_\mathrm{spins})$  ")	


	elif quantity == "M":
		plt.subplot(dummy_index)
		plt.plot(expectation_list[0], expectation_list[3], label = "T' = %.1f"%T[-1], color = color)
		plt.grid(linestyle = "--")
		plt.legend()
		if dummy_index == 211:
			plt.ylabel(r"$\langle M \rangle / $N$_\mathrm{spins}$  ")		

	elif quantity == "absM":
		plt.subplot(dummy_index)
		plt.plot(expectation_list[0], expectation_list[6], label = "T' = %.1f"%T[-1], color = color)
		plt.grid(linestyle = "--")
		plt.legend()
		if dummy_index == 211:
			plt.ylabel(r"$\langle \mid M \mid \rangle / $N$_\mathrm{spins}$  ")	
		# else:
		# 	plt.ylim(0.99925,0.9998)


	dummy_index +=1

plt.xlabel("Number of MC Cycles")
plt.savefig(savepath + orientation+ quantity + ".pdf")
plt.show()