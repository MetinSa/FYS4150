import numpy as np 

"""
 Analytical calculations for the 2x2 Ising model with temperature T = 1

"""

# System specifics
N_spin = 4																	# Number of spins
T = 1																		# Temperature
Z = 4*np.cosh(8/T) + 12														# Partition function

# Expectation values
E =(-(8*np.sinh(8/T))/(np.cosh(8/T) + 3))/N_spin							# Energy per spin
M = ((1/Z)*(-4*np.exp(8/T) - 8 + 8 + 4*np.exp(8/T)))/N_spin					# Magnetization per spin 
absM = (((2*np.exp(8/T) +4)/(np.cosh(8/T) +3)))/N_spin						# Absolute Magnetization per spin
C_V = (64/N_spin*T**2)*((1 + 3*np.cosh(8/T))/(( np.cosh(8/T) + 3 )**2))		# Heat Capacity per spin*boltzmann constant
chi = ((8/T)*((np.exp(8/T) +1)/(np.cosh(8/T) +3)))/N_spin					# Susceptibility per spin*J

# Printing the results
print("="*20)
print("Expectation Values Analytic")
print("="*20)
print("E:	   M:	     C_V:      chi:       absM:")
print ("%.7f" %E, "%.7f" %M, "%.7f" %C_V, "%.7f" %chi, "%.7f"%absM)