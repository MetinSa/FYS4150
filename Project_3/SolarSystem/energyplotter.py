import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.cm as mplcm
import matplotlib.colors as colors
from matplotlib2tikz import save as tikz_save

import sys



if len(sys.argv) < 2:
	print("Please provide filename in commandline")
	sys.exit()
else:
	if sys.argv[1].endswith(".txt"):
		filename = "output/" + sys.argv[1]
	else:
		filename = "output/" + sys.argv[1] + ".txt"


Ek, Ep = (np.loadtxt(filename, unpack=True))


plt.semilogy(Ek, color='blue', label='Total kinetic energy')
plt.plot(Ep, color='magenta', label='Total potential energy')
plt.grid()
plt.xlabel('Timestep')
plt.ylabel('Energy')
plt.axis("equal")
#tikz_save("Figures/figure.tex", figureheight='\\figureheight', figurewidth='\\figurewidth')
plt.show()
