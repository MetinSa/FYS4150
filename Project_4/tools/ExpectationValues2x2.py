import numpy as np 
import sys as sys 
import matplotlib.pyplot as plt 
import os

# List of interesting quantities
N_list = []
E_list = []
M_list = []
C_V_list = []
Chi_list = []
absM_list = []

# filenames
filenames = []

for filename in os.listdir("../data/2x2/"):
	filenames.append(filename)

filenames = sorted(filenames)

for file in filenames:

	N, T, E, M, C_V, Chi, absM, accepted_states = np.loadtxt("../data/2x2/" + file, unpack = True)
	N_list.append(N)
	E_list.append(E)
	M_list.append(M)
	C_V_list.append(C_V)
	Chi_list.append(Chi)
	absM_list.append(absM)

N_files = len(E_list)
N_samples = len(E_list[0][:])

E_expectation = np.zeros(N_files)
M_expectation = np.zeros(N_files)
C_V_expectation = np.zeros(N_files)
Chi_expectation = np.zeros(N_files)
absM_expectation = np.zeros(N_files)

# Find the average expectation value over all samples
for i in range(N_files):

	E_expectation[i] = np.sum(E_list[i][:])/N_samples
	M_expectation[i] = np.sum(M_list[i][:])/N_samples
	C_V_expectation[i] = np.sum(C_V_list[i][:])/N_samples
	Chi_expectation[i] = np.sum(Chi_list[i][:])/N_samples
	absM_expectation[i] = np.sum(absM_list[i][:])/N_samples


# Print the expectation values for every sample set
print("="*20)
print("Expectation Values")
print("="*20)
print("N:	E:	   M:	     C_V:      Chi:      absM:")
for i, (E, M, C_V, Chi, absM) in enumerate(zip(E_expectation, M_expectation, C_V_expectation, Chi_expectation, absM_expectation)):
	print ("%.E: " %(10**(i+1)), "%.7f" %E, "%.7f" %M, "%.7f" %C_V, "%.7f" %Chi, "%.7f"%absM)









	

