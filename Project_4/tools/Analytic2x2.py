import numpy as np 


T = 1

Z = 4*np.cosh(8/T) + 12


print(  (-(8*np.sinh(8/T))/(np.cosh(8/T) + 3))/4  )