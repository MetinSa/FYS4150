
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


Ek, Ep, momentum = (np.loadtxt(filename, unpack=True))
E_tot = Ek + Ep

years = np.linspace(0,10,len(Ek))

# plt.figure()
plt.plot(years, Ek, color='blue', label='Kinetic energy')
plt.plot(years, Ep, color='magenta', label='Potential energy')
plt.plot(years, E_tot, color='teal', label=r'Total energy ($E_k + E_p$)')
plt.grid()
plt.xlabel('Time [years]')
plt.ylabel(r'Energy [$M_{sun} (AU/yr)^2$]')
plt.legend()
#tikz_save("Figures/energy_verlet.tex", figureheight='\\figureheight', figurewidth='\\figurewidth')

plt.figure()
plt.plot(years, abs(E_tot-E_tot[0]), color='teal')#, label=r'Total energy ($E_k + E_p$)')
plt.grid()
plt.xlabel('Time [years]')
plt.ylabel(r'|Total relative energy| [$M_{sun} (AU/yr)^2$]')
#tikz_save("Figures/relenergy_verlet.tex", figureheight='\\figureheight', figurewidth='\\figurewidth')
plt.show()

# plt.figure()
# plt.plot(years, abs(momentum-momentum[0]), color='blue')
# plt.grid()
# plt.xlabel('Time [years]')
# plt.ylabel(r'Total angular momentum per mass [$AU^2/yr$]')
# #tikz_save("Figures/figure.tex", figureheight='\\figureheight', figurewidth='\\figurewidth')
# plt.show()
