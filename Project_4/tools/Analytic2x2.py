import numpy as np 

"""
 Analytical calculations for the 2x2 Ising model with temperature T = 1

"""

#Number of spins
N_spin = 4

#Temperature
T = 1
#Partition function
Z = 4*np.cosh(8/T) + 12


#Energy per spin
E =(-(8*np.sinh(8/T))/(np.cosh(8/T) + 3))/N_spin

#Magnetization per spin 
M = ((1/Z)*(-4*np.exp(8/T) - 8 + 8 + 4*np.exp(8/T)))/N_spin

#Absolute Magnetization per spin
absM = (((2*np.exp(8/T) +4)/(np.cosh(8/T) +3)))/N_spin

#Heat Capacity per spin*boltzmann constant
C_V = (64/N_spin*T**2)*((1 + 3*np.cosh(8/T))/(( np.cosh(8/T) + 3 )**2))

#Susceptibility per spin*J
chi = ((8/T)*((np.exp(8/T) +1)/(np.cosh(8/T) +3)))/N_spin

print("="*20)
print("Expectation Values Analytic")
print("="*20)
print("E:	   M:	     C_V:      chi:       absM:")
print ("%.7f" %E, "%.7f" %M, "%.7f" %C_V, "%.7f" %chi, "%.7f"%absM)
